# N Puzzle Solver

A simple N Puzzle Solver using an A star algorithm (no SMA, no IDA, just A star).

To generate random map, use the generator :
```
python generator.py n
```
n being the size of the board (for an 8-puzzle, n = 3)

To compile, you need to install the SFML and pkg-config, then make.

To launch the program:

```
./n_puzzle <heuristic> <initial state> <goal state>
```

You can choose three heuristics among {manhattan, hamming, euclidean}.
If the argument typed is not in this list, the heuristic is trivial and a simple Dijkstra is used.

If a fourth argument is added, only the heuristic will be taken into consideration.

Example:
```
./n_puzzle manhattan init3 goal3
./n_puzzle manhattan init4 goal4
./n_puzzle manhattan init4 goal4 greed
```



For 8-Puzzle (n = 3) and 15-Puzzle (n = 4), press enter to see the next move or backspace to go to the previous move.

