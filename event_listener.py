import json


def get_message(stream, q):
    for msg in stream:
        try:
            data = json.loads(msg.data)
        except ValueError:
            continue
        q.put(data)
        q.join()


def find_new_message(q):
    if q.empty():
        return None
    msg = q.get(block=False)
    q.task_done()
    return msg
