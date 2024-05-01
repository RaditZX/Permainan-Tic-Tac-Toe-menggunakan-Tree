#ifndef "TicTacToe.h"
#define "TicTacToe.h"

#define EMPTY_CELL ' '

typedef struct
{
    char board[3][3];
    struct TreeNode *children[9];
    int num_children;
} TicTacToe;

TicTacToe createBoard();
bool isGameOver();
void mainMenu();
void generateBoardAppearance();
char check_winner(char board[3][3]);
void resetGame();

#endif