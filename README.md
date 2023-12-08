# connect-4
A recreation of the connect-4 game so I can learn some basic Qt

To build the project:
Get dependencies (probably qmake, QT dev, build-essentials), then run:
 - cd connect-4
 - qmake
 - make
 - ./connect-4

# Features
## Finished
 - Restart game without exiting.
 - Play as either red or yellow.
 - Play against computer.
 - - Computer "AI" just makes random moves.

## Unfinished
 - 2-player mode.
 - Play-piece dropping animation
 - Game status displayed as text (your move, you win, computer wins, player one's move, etc.)
 - Refactor to use more classes - currently only uses a MainWindow and Widget derives class.
 - - Could maybe use Player class, PlayPiece class
