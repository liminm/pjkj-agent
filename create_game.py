import sys
from servercom import create_game
import json
import random
import string


def random_string(length=8):
    letters = string.ascii_letters
    return ''.join(random.choice(letters) for i in range(length))


def make_game(tf_1, tf_2):
    try:
        with open(tf_1) as json_file:
            try:
                data = json.load(json_file)
            except ValueError as e:
                print(e)
                exit()
    except EnvironmentError as e:
        print(e)
        exit()
    else:
        player1_id = data['team']['playerId']
        player1_token = data['team']['playerToken']

    try:
        with open(tf_2) as json_file:
            try:
                data = json.load(json_file)
            except ValueError as e:
                print(e)
                exit()
    except EnvironmentError as e:
        print(e)
        exit()
    else:
        player2_id = data['team']['playerId']
        player2_token = data['team']['playerToken']

    g_name = random_string()
    game_id = create_game(g_name, "jumpSturdy", player1_id, player2_id)

    return game_id, player1_token, player2_token


if __name__ == '__main__':
    t2_name = None
    t1_name = None
    t2_isisName = None
    t1_isisName = None

    if len(sys.argv) != 3:
        print("usage: <teamfile1> <teamfile2>")
        exit()

    teamfile1 = sys.argv[1]
    teamfile2 = sys.argv[2]

    make_game(teamfile1, teamfile2)
