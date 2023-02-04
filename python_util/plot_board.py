import matplotlib.pyplot as plt
import numpy as np
import matplotlib.colors


def plot_state(fen):
    size = 8
    board = np.ones((size, size))
    board[1::2, 0::2] = 0
    board[0::2, 1::2] = 0
    col_labels = ['A', 'B', 'C', 'D', 'E', 'F', 'G', 'H']
    row_labels = [8, 7, 6, 5, 4, 3, 2, 1]
    cmap = matplotlib.colors.ListedColormap(['gray', 'white'])
    plt.imshow(board, cmap=cmap, interpolation='none')
    plt.xticks(range(size), col_labels)
    plt.yticks(range(size), row_labels)
    counter = 0
    for char in fen:
        y = counter // 8
        x = counter % 8
        if char.isdigit():
            counter += int(char)
        elif char == 'k':
            plt.text(x, y, '⛃', fontsize=35, ha='center', va='center')  # db
            counter += 1
        elif char == 'K':
            plt.text(x, y, '⛁', fontsize=35, ha='center', va='center')  # dw
            counter += 1
        elif char == 'q':
            plt.text(x, y, '♛', fontsize=35, ha='center', va='center')  # mb
            counter += 1
        elif char == 'Q':
            plt.text(x, y, '♕', fontsize=35, ha='center', va='center')  # mw
            counter += 1
        elif char == 'b':
            plt.text(x, y, '⛂', fontsize=35, ha='center', va='center')  # sb
            counter += 1
        elif char == 'B':
            plt.text(x, y, '⛀', fontsize=35, ha='center', va='center')  # sw
            counter += 1
        elif char == ' ':
            break
        else:
            continue

    plt.show()


if __name__ == '__main__':
    plot_state('8/1b1kbk2/2k5/2Bb1b2/6K1/1B6/3Kb3/2b1B3 w - - 0 28')
