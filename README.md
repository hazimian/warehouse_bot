//WAREHOUSE ROBOT PROBLEM
//The robot's current map provided over `stdin` in the following format:
//
//```
//X X X X X
//X . & . X
//O . . . X
//X . . ~ X
//X X X O X
//```
//
//Legend:
//
//-   `&`: The robot's current position
//-   `X`: A blocked cell, cannot be traversed
//-   `.`: A free cell, can be traversed
//-   `~`: A slippery cell, can only be traversed at 1/3 normal speed.
//-   `O`: Unknown cells, these represent where the robot may want to explore next.
//
//Each cell is 1 m wide. The has a nominal speed of 1 m/s, and can only travel along 4 cardinal directions (Manhattan style).
//
//The program outputs over `stdout`:
//
//-   (`x,y`) of 'Unknown' cells
//-   Time required to reach each unknown cell ordered from shortest to longest travel duration.
//

//## Guidelines:
//
//Solutions in C++ are strongly preferred, and please let us know if that poses a problem.
//
//We may test your solution with pathological datasets not provided in `input`.
//
//Don't go overboard, a solution shouldn't take more than a few hours to implement. Feel free to note any omitted features in a README.
//
//Please provide instructions on how to compile and/or run your program in Linux. For example:
//
