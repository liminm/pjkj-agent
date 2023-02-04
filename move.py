import subprocess
from random import randint

TIME_OUT_FLAG = 2
ERROR_CODE_FLAG = 1

# c_prog = './cmake-build-debug/main.exe'
c_prog = './main'
r_prog = './random'


def best_move(f_fen, player, depth: str, t_out):
    try:
        result = subprocess.run([c_prog, f_fen, player, depth], capture_output=True, text=True, timeout=t_out)
    except subprocess.TimeoutExpired:
        return None, TIME_OUT_FLAG

    if result.returncode != 0:
        return None, ERROR_CODE_FLAG
    else:
        return result.stdout, 0


def random_move(f_fen, player):
    rnd_num = randint(0, 100)
    try:
        result = subprocess.run([r_prog, f_fen, player, str(rnd_num)], capture_output=True, text=True, timeout=1)
    except subprocess.TimeoutExpired:
        return None,

    if result.returncode != 0:
        return None
    else:
        return result.stdout


if __name__ == '__main__':
    fen = '1bbbbbb1/1bbbbbb1/8/8/8/3B4/1BB1BBB1/1BBBBBB1 b - - 1 1'
    move = best_move(fen, 'b', '8', 5)
    if move is not None:
        print(move)
