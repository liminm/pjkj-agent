#!/usr/bin/env python

import subprocess
from random import random

import numpy as np
import sys
from create_team import make_team
from create_game import make_game
team_name1 = "team1"
team_name2 = "team2"
isis_name1 = "isis1"
isis_name2 = "isis2"
player_name1 = "player1"
player_name2 = "player2"

url = 'http://127.0.0.1:5000/'

if __name__ == '__main__':
    games = 1

    make_team(team_name1, isis_name1, player_name1, "team1.json")
    make_team(team_name2, isis_name2, player_name2, "team2.json")

    game_list = []
    bot_player = []
    rand_player = []

    player1_token = None
    player2_token = None
    for i in range(games):
        bot_pl = None
        rand_pl = None

        if random() >= 0.5:
            bot_pl = 'w'
            rand_pl = 'b'
        else:
            bot_pl = 'b'
            rand_pl = 'w'

        if bot_player == 'w':
            game_id, player1_token, player2_token = make_game("team1.json", "team2.json")
        else:
            game_id, player1_token, player2_token = make_game("team2.json", "team1.json")
        game_list.append(game_id)
        bot_player.append(bot_pl)
        rand_player.append(rand_pl)

    game_array = np.asarray(game_list)
    print(game_array)
    for j in range(games):
        print("BOT PLAYER: " + bot_player[j])
        print("RANDOM PLAYER: " + rand_player[j])
        if bot_player[j] == 'w':
            p1 = subprocess.Popen(
                [sys.executable, "start_bot.py", url+'game/'+str(game_array[j]), bot_player[j], player1_token])
            p2 = subprocess.Popen(
                [sys.executable, "start_bot_random.py", url + 'game/' + str(game_array[j]), rand_player[j], player2_token])

            p1.wait()
            p2.wait()
        else:
            p1 = subprocess.Popen(
                [sys.executable, "start_bot.py", url + 'game/' + str(game_array[j]), bot_player[j], player2_token])
            p2 = subprocess.Popen(
                [sys.executable, "start_bot_random.py", url + 'game/' + str(game_array[j]), rand_player[j], player1_token])

            p1.wait()
            p2.wait()
