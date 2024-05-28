#ifndef PLAYER_H
#define PLAYER_H

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <limits.h>
#include <math.h>


#define BOT 'o'
#define PLAYER 'x'
#define EMPTY_CELL '_'

void entryMove(char board[3][3], char current_player, char *playerName, int score, bool withBot);
bool is_valid_move(char board[3][3], int row, int col);

#endif
