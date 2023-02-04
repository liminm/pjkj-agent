import json
import sys

from servercom import create_team, create_player

def make_team(t_name, i_name, p_name, f_name):
    t_token, t_id = create_team(t_name, isisName=i_name)
    p_token, p_id = create_player(t_token, p_name)

    data = {'team': {
        'name': t_name,
        'isisName': i_name,
        'teamToken': t_token,
        'teamId': t_id,
        'playerToken': p_token,
        'playerId': p_id,
        'playerName': p_name,
    }
    }

    with open(f_name, 'w') as outfile:
        json.dump(data, outfile, indent=4)


if __name__ == '__main__':
    if len(sys.argv) != 5:
        print("usage: create_team.py <teamName> <isisName> <playerName> <filename>")
        exit()

    teamName = sys.argv[1]
    isisName = sys.argv[2]
    playerName = sys.argv[3]
    filename = sys.argv[4]

    make_team(teamName, isisName, playerName, filename)
