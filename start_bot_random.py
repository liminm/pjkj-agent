import sys
from queue import Queue
from threading import Thread
import logging
from sseclient import SSEClient

from event_listener import get_message, find_new_message
from servercom import get_game_full_path, send_event_full_path
from move import random_move

next_player = {
    "playerA": "playerB",
    "playerB": "playerA"
}

if __name__ == '__main__':

    if len(sys.argv) != 4:
        quit()

    game_path = sys.argv[1]
    w_b_player = sys.argv[2]
    token = sys.argv[3]

    game = get_game_full_path(game_path)

    player_type = None
    if w_b_player == 'w':
        player_type = "playerA"
    else:
        player_type = "playerB"

    turn = "playerA"

    log_prefix = "RANDOM " + w_b_player + " : "

    messages = SSEClient(game_path + '/events')
    queue = Queue(maxsize=0)
    worker = Thread(target=get_message, args=(messages, queue))
    worker.setDaemon(True)
    worker.start()

    board = game["settings"]["initialFEN"]

    while 1:
        m_data = find_new_message(queue)
        if m_data is not None:
            logging.info(log_prefix + str(m_data))
            if m_data["type"] == "gameEnd":
                if m_data["details"]["winner"] == player_type:
                    logging.info(log_prefix + "BOT WON")
                elif m_data["details"]["winner"] == "draw":
                    logging.info(log_prefix + "DRAW")
                else:
                    logging.info(log_prefix + "BOT LOST" + ' REASON ' + m_data['details']['type'])
                break
            elif m_data["type"] == "serverMessage":
                print(m_data["messageText"])
            elif m_data["type"] == "move":
                try:
                    board = m_data["details"]["postFEN"]
                except KeyError as e:
                    continue
                turn = next_player[m_data["player"]]
            else:
                print("Error")

        if turn == player_type:
            move = random_move(board, w_b_player)
            if move is not None:
                logging.info(log_prefix + move)
                print(player_type, ": ", move)
            valid, reason = send_event_full_path(game_path + '/events', token, "move", move)
            while not valid or move is None:
                print("NOT A VALID MOVE")
                move = random_move(board, w_b_player)
                if move is not None:
                    logging.info(log_prefix + move)
                    print(player_type, ": ", move)
                valid, reason = send_event_full_path(game_path + '/events', token, "move", move)
                if reason == 'error':
                    break

        else:
            continue
        turn = next_player[turn]
