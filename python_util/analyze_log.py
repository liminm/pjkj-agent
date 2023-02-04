import numpy as np


def parse_log_r_b(logfile):
    with open(logfile, 'r') as f:
        f = f.readlines()

    moves_bot = []
    bot = None
    ran = None
    moves_ran = []
    states = []
    time = []
    winner = None
    reason = None

    for line in f:
        if line.startswith('INFO:root:BOT'):
            if line.startswith('INFO:root:BOT w'):
                bot = 'w'
            else:
                bot = 'b'
            if '{' not in line:
                index = line.find(": ")
                if line[index+2] == 'B':
                    if "WON" in line:
                        winner = bot
                    elif "LOST" in line:
                        reason = line[line.find("REASON ")+7:-1]
                else:
                    moves_bot.append(line[index + 2:-1])
            else:
                sp_lines = line.split(',')
                for sp in sp_lines:
                    index_time = sp.find("'time': ")
                    if index_time != -1:
                        time.append(sp[index_time + 8:-1])

        elif line.startswith('INFO:root:RANDOM'):
            if line.startswith('INFO:root:RANDOM w'):
                ran = 'w'
            else:
                ran = 'b'
            if '{' not in line:
                index = line.find(": ")
                if line[index + 2] == 'B':
                    if "WON" in line:
                        winner = ran
                    elif "LOST" in line:
                        reason = line[line.find("REASON ") + 7:-1]
                else:
                    moves_ran.append(line[index + 2:-1])
            else:
                sp_lines = line.split(',')
                for sp in sp_lines:
                    index_pf = sp.find("'postFEN': ")
                    if index_pf != -1:
                        states.append(sp[index_pf + 13:-1])

    if bot == 'w':
        time_bot = time[1::2]
        time_ran = time[0::2]
    else:
        time_bot = time[0::2]
        time_ran = time[1::2]
    print(moves_bot)
    print(moves_ran)
    print(states)
    print(time_bot)
    print(time_ran)
    print(winner)
    print(reason)


if __name__ == '__main__':
    parse_log_r_b('../Server.log')
