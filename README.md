# Corners3x4_MFC_game
Ugolki(Corners) 3x4 MFC C++ game interface with Monte Carlo computer player algorithm

Both players start off with square arrangements of 16 game pieces in opposing corners of the gameboard. Each player's goal is to move all their pieces from the starting corner to the corner occupied by the opponent at the start of the game.

Players take turns moving one game piece. A piece may move only away from the starting location into a destination that is empty, provided either of the following conditions are met:

the destination square is adjacent to the starting square
the destination square can be reached by consecutive "jumps" over other game pieces belonging to either player.
The game ends when both players have no available moves left. Game pieces are counted within the square bounds of the final formation, and the player with more pieces wins.

