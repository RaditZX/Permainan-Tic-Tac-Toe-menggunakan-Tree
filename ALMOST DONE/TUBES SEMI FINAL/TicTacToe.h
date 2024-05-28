#ifndef TICTACTOE_H
#define TICTACTOE_H

#include <stdio.h>
#include <stdlib.h>
//#include <stdbooleanean.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <unistd.h>
#include <windows.h>
#include <mmsystem.h>
#include <time.h>

#define BOT 'o'
#define PLAYER 'x'
#define EMPTY_CELL '_'
#define BLUE 9
#define RED 12
#define WHITE 15
#define RESET 7

//typedef struct tScoreBoard *address;
//typedef struct tScoreBoard{
//	int info;
//	address left, right;
//}ScoreBoard;

typedef struct TreeScore
{
    char player[20];
    int score;
    struct TreeScore *left;
    struct TreeScore *right;
} TreeScore;

typedef struct TreeTime
{
    char player[20];
    time_t start_time;
    time_t end_time;
    struct TreeTime *left;
    struct TreeTime *right;
    double elapsed_time;
} TreeTime;

void setColor(int color);
bool is_game_over(char board[3][3]);
char check_winner(char board[3][3]);
void print_board(char board[3][3]);
void initialize_board(char board[3][3]);
int generateScore(char board[3][3]);
int generateScorePlayer2(char board[3][3]);
TreeScore *insertScore(TreeScore *root, char player[], int score);
void print_inorder(TreeScore* root);
void print_inorderTime(TreeTime* root);
TreeTime *insertTime(TreeTime *root, char player[], double elapsed_time);
void playSoundEffect(const char *soundName);
void print_boardToMakeMove(char board[3][3], int col, int row);
void loadingAnimation();
void printMainMenu();
void printDecorativeLine();
void printAsciiArt();
void clearScreen();





#endif

