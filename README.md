To launch the program, execute make and launch the /chess executable

To pass a file game.txt to the program, it is necessary to execute the command "cat game.txt | ./echecs" by paying attention that all the lines are moves in correct notation.
 
This program checks the basic conditions, manages the obstacles, the captures, the pawn moves (en passant, two squares moves), detects the checks, accepts castling.
Mate and Pat are implemented, but do not always work. Promotion is not implemented yet.

The program uses 4 main classes: Square, Piece (and all inheriting classes) Chessboard and Game.

Error messages are not always accurate (condititions are to be reviewed)
