AI project game agent
======================

Welcome to the repository for Group B's agent in the 2020 AI tournament at TU Berlin AOT! Our agent is designed to play the game "Jump Sturdy."

The agent communicates with the game server and receives updates on the current state of the game board. Based on this information, it calculates and returns the best possible move for our player.

The performance of the agent is influenced by the search time set on the game server, which determines how deep the agent can search into the search space and calculate moves in advance.

The agent uses various classical AI techniques, such as the Minimax algorithm, to simulate all possible sensible moves for both the player and adversary, and to reduce the search space accordingly. This approach allows the agent to make informed decisions and to maximize its chances of winning.

# Software architecture

The project is split into two parts: communication with the server in Python found in the [home directory](https://github.com/liminm/pjkj-agent) and move generation and algorithmic elements in C for improved performance found [here](https://github.com/liminm/pjkj-agent/tree/main/src/AI).

The agent is containerized using Docker for server communication. 

