#ifndef FILESYSTEM_H
#define FILESYSTEM_H
#include "TicTacToe.h"

void saveTreeToFile(TreeScore *root, FILE *file);
void saveBinaryTree(TreeScore *root, const char *filename);
TreeScore* readTreeFromFile(FILE *file);
TreeScore* loadBinaryTree(const char *filename);
void saveTreeTimeToFile(TreeTime *root, FILE *file);
void saveBinaryTreeTime(TreeTime *root, const char *filename);
TreeTime* readTreeTimeFromFile(FILE *file);
TreeTime* loadBinaryTreeTime(const char *filename);


#endif
