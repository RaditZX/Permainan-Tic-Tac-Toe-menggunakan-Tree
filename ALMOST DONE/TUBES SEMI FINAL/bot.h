#ifndef BOT_H
#define BOT_H

#include <stdio.h>
#include <stdlib.h>
//#include <stdbooleanean.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include "boolean.h"

#define BOT 'o'
#define PLAYER 'x'
#define EMPTY_CELL '_'

typedef struct TreeNode
{
    char board[3][3];
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;



TreeNode *create_node(char board[3][3]);
void delete_tree(TreeNode *root);
boolean isMovesLeft(char board[3][3]);
void bot_make_move(char board[3][3], char player);
int evaluate(char b[3][3]);
int minimax(TreeNode *root, int depth, int alpha, int beta, boolean isMax);

#endif
