Each folder contains multiple chessboards, grouped together depending on the number of chess pieces remaining (less than 10, less than 20 or more than 20).

Each board is represented as follow, and separated by the next one by an empty line:
- RES is the result of the game (1/2-1/2 = pat, 1-0 = white wins, 0-1 = black wins)
- CHECKMATE is a boolean stating if the current board states a checkmate
- FEN is the fen representation of the board
- The next 8 lines represents the board in a more visual way, using fen notation for pieces
