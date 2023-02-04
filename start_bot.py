import sys
import time
from queue import Queue
from threading import Thread
from sseclient import SSEClient

from event_listener import get_message, find_new_message
from servercom import get_game_full_path, send_event_full_path, print_custom
from move import best_move
from move import random_move
from move import TIME_OUT_FLAG
from move import ERROR_CODE_FLAG

next_player = {
    "playerA": "playerB",
    "playerB": "playerA"
}

avg_moves = 30  # only one player


def get_remaining_moves(n_moves, f_fen):
    # TODO: calculate remaining turns dynamically depending on board
    return max(avg_moves - n_moves, 5)


def eval_time(t_budget, t_out, m_time, n_moves, f_fen):
    remaining_time = t_budget - m_time
    remaining_moves = get_remaining_moves(n_moves, f_fen)
    turn_time = remaining_time / remaining_moves

    if turn_time * 1.5 < t_out:
        return turn_time
    else:
        return t_out / 1.5


if __name__ == '__main__':

    if len(sys.argv) != 4:
        quit()

    game_path = sys.argv[1]
    w_b_player = sys.argv[2]
    token = sys.argv[3]
    print_custom(f'We are Player {w_b_player}')
    game = get_game_full_path(game_path)

    player_type = None
    if w_b_player == 'w':
        player_type = "playerA"
    else:
        player_type = "playerB"

    turn = "playerA"
    print_custom(f'Our Player Type is: {player_type}')

    log_prefix = "BOT " + w_b_player + " : "

    messages = SSEClient(game_path + '/events')
    queue = Queue(maxsize=0)
    worker = Thread(target=get_message, args=(messages, queue))
    worker.setDaemon(True)
    worker.start()

    board = game["settings"]["initialFEN"]
    timeout = int(game["players"][player_type]["timeout"])
    timeBudget = int(game["players"][player_type]["timeBudget"])
    print_custom(f'Initial Board: {board}')
    print_custom(f'Timeout: {timeout}')
    print_custom(f'Time Budget: {timeBudget}')

    move_time = 0
    move_num = 0
    while 1:
        m_data = find_new_message(queue)
        if m_data is not None:
            if m_data["type"] == "gameEnd":
                if m_data["details"]["winner"] == player_type:
                    print_custom(f'BOT WON', log_prefix)
                elif m_data["details"]["winner"] == "draw":
                    print_custom(f'DRAW', log_prefix)
                else:
                    print_custom(f'BOT LOST REASON {m_data["details"]["type"]}', log_prefix)
                break
            elif m_data["type"] == "serverMessage":
                print_custom(m_data["messageText"], log_prefix)
            elif m_data["type"] == "move":
                try:
                    board = m_data["details"]["postFEN"]
                    if m_data["player"] == player_type:
                        move_time += int(m_data["details"]["time"])
                        print_custom(f'time taken: {move_time}', log_prefix)
                except KeyError as e:
                    continue
                turn = next_player[m_data["player"]]
            else:
                print_custom("Error")

        if turn == player_type:
            time_to_move = eval_time(timeBudget, timeout, move_time, move_num, board) / 1000
            depth = 3
            move_list = []
            time_left = time_to_move
            start_time = time.time()
            valid = False
            move = None
            m_depth = None
            while time_left > 2:
                m, code = best_move(board, w_b_player, str(depth), round(time_left - 2, 2))
                if code == TIME_OUT_FLAG:
                    break
                move_list.append((m, depth))
                depth += 1
                time_left = time_to_move - (time.time() - start_time)
                print_custom(f'depth: {depth-1} done | time left: {time_left:.2f}', log_prefix)

            for (m, d) in reversed(move_list):
                if m is None:
                    continue
                else:
                    move = m
                    m_depth = d
                    break

            if move is not None:
                valid, reason = send_event_full_path(game_path + '/events', token, "move", move)
                print_custom(f'{player_type} : {move} | depth: {m_depth}', log_prefix)

            depth = 2

            while move is None or not valid:

                if depth <= 0:
                    print_custom("NO Depth worked, trying random move", log_prefix)
                    move = random_move(board, w_b_player)
                else:
                    move, _ = best_move(board, w_b_player, str(depth), 1)

                if move is None:
                    print_custom(f'NONE move for depth: {depth}', log_prefix)
                    depth -= 1
                    continue

                print_custom(f'{player_type} : {move} | depth: {depth}', log_prefix)
                depth -= 1
                valid, reason = send_event_full_path(game_path + '/events', token, "move", move)
                if reason == 'error':
                    break
            move_num += 1
        else:
            continue
        turn = next_player[turn]
