AI project game agent
======================

This is the agent of group B for the game "Jump Sturdy" for the 2020 AI tournament at the TU Berlin AOT.
The agent communicates with the game server and gets as input the current state of the board and returns the best possible move found.
The performance of the agent depends on the search time set on the server side allowing the agent to search deeper into the search space and calculate more moves in advance.
The agent works by simulating all possible sensible moves for both player and adversary and by reducing the search space through various classical AI techniques such as the Minimax algorithm.

# Software architechture

The project is divided into a python part dealing with the server communication and a C part dealing with everything concerning the move generation and all algorithmic aspects.

