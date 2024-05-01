#ifndef "bot.h"
#define "bot.h"

#define BOT 'O'

int minimax(TicTacToe *node, bool isMaximizingPlayer, int depth, int alpha, int beta);
void bot_make_move(char board[3][3], char player);
bool is_valid_move(char board[3][3], int row, int col);
bool check_win(char board[3][3], char player);
bool find_empty_corner(char board[3][3], int *row, int *col);
bool find_empty_side(char board[3][3], int *row, int *col);
bool win_strategy(char board[3][3], char player);
bool block_strategy(char board[3][3], char player);
bool fork_strategy(char board[3][3], char player);
bool block_fork_strategy(char board[3][3], char player);
bool center_strategy(char board[3][3], char player);
bool opposite_corner_strategy(char board[3][3], char player);
bool empty_corner_strategy(char board[3][3], char player);
bool empty_side_strategy(char board[3][3], char player);
void bot_make_move(char board[3][3], char player);
bool is_valid_move(char board[3][3], int row, int col);

#endif