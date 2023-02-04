import logging
import requests

DEFAULT_POST = 201
DEFAULT_GET = 200
LOGLEVEL = 2
LOGGER = True
STDOUT = True

URL = 'http://localhost:5000/'
ISIS_NAME = 'Jump Sturdy B'
GAME_TYPE = 'jumpSturdy'

logging.basicConfig(filename='Server.log', level=logging.INFO)


def print_custom(line: str, prefix=None):
    if LOGGER:
        if prefix is not None:
            logging.info(prefix + line)
        else:
            logging.info(line)
    if STDOUT:
        print(line)


def get_request(r_url, r_token=None):
    if LOGLEVEL == 2:
        print_custom(f"SENDING GET TO: {r_url}")
    if r_token is None:
        r = requests.get(r_url)
    else:
        r = requests.get(r_url, headers={'Authorization': 'Basic ' + r_token})
    if r.status_code != DEFAULT_GET:
        if LOGLEVEL >= 1:
            print_custom(f"ERROR {r.status_code}: {r.reason}")
        return None, r.reason
    data = r.json()
    if LOGLEVEL == 2:
        print_custom(f"RECEIVED: {data}")
    return data, None


def post_request(r_url, r_pload, r_token=None):
    if LOGLEVEL == 2:
        print_custom(f'SENDING POST TO: {r_url} with payload: {r_pload}')
    if r_token is None:
        r = requests.post(r_url, json=r_pload)
    else:
        r = requests.post(r_url, json=r_pload, headers={'Authorization': 'Basic ' + r_token})
    if r.status_code != DEFAULT_POST:
        if LOGLEVEL >= 1:
            print_custom(f"ERROR {r.status_code}: {r.reason}")
        return None, r.reason
    data = r.json()
    if LOGLEVEL == 2:
        print_custom(f"RECEIVED: {data}")
    return data, None


def create_team(name, url=URL, isisName=ISIS_NAME, gameType=GAME_TYPE):
    pload = {'name': name, 'isisName': isisName, 'type': gameType}
    data, _ = post_request(url + "teams", pload)
    t_token = data["token"]
    t_id = data["id"]
    return t_token, t_id


def test_team_token(t_token, url=URL):
    data, _ = get_request(url + 'teamlogin', r_token=t_token)
    return data["valid"]


def list_teams(url=URL):
    data = get_request(url + 'teams?count=<count>&start=<start>')
    return data


def get_team(t_id, url=URL):
    data = get_request(url + 'team/' + t_id)
    return data


def create_player(t_token, p_name, url=URL):
    pload = {"name": p_name}
    data, _ = post_request(url + 'players', r_pload=pload, r_token=t_token)
    p_id = data["id"]
    p_token = data["token"]
    return p_token, p_id


def test_player_token(p_token, url=URL):
    data, _ = get_request(url + 'playerlogin', r_token=p_token)
    if data["valid"]:
        return data["id"]
    return None


def list_players(url=URL):
    data, _ = get_request(url + 'players?count=<count>&start=<start>')
    return data


def get_player(p_id, url=URL):
    data, _ = get_request(url + 'player/' + p_id)
    t_id = data["team"]
    p_name = data["name"]
    return p_name, t_id


def create_game(g_name, g_type, p1_id, p2_id,
                p1_timeout=30000, p1_initial_timebudget=120000, p2_timeout=30000, p2_initial_timebudget=120000,
                start_board=None, url=URL):
    pload = {
        "name": g_name,
        "type": g_type,
        "players": {
            "playerA": {
                "id": p1_id,
                "timeout": p1_timeout,
                "initialTimeBudget": p1_initial_timebudget
            },
            "playerB": {
                "id": p2_id,
                "timeout": p2_timeout,
                "initialTimeBudget": p2_initial_timebudget
            }
        },
        "settings": {
            "initialFEN": start_board
        }
    }

    data, _ = post_request(url + 'games', r_pload=pload)
    return data["id"]


def list_games(state='planned', url=URL):
    data, _ = get_request(url + 'games?count=<count>&start=<start>&state=' + state)
    return data


def get_game(g_id, url=URL):
    data, _ = get_request(url + 'game/' + g_id)
    return data


def get_game_full_path(url):
    data, _ = get_request(url)
    return data


def send_event(g_id, p_token, m_type, move, url=URL):
    pload = {"type": m_type,
             "details": {
                 "move": move}
             }
    data, _ = post_request(url + 'game/' + g_id + '/events', r_token=p_token, r_pload=pload)
    return data["valid"], data["reason"]


def send_event_full_path(url, p_token, m_type, move):
    pload = {"type": m_type,
             "details": {
                 "move": move}
             }
    data, reason = post_request(url, r_token=p_token, r_pload=pload)
    if reason is not None:
        if str(reason).lower() == 'conflict':
            return False, "error"
        return False, "other"

    if data is None:
        return False, "not valid"
    return data["valid"], data["reason"]
