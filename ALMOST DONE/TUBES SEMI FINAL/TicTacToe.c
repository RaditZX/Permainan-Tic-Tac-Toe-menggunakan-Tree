#include "TicTacToe.h"

void initialize_board(char board[3][3])
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            board[i][j] = EMPTY_CELL;
        }
    }
}

// Function to print the Tic Tac Toe board
void print_board(char board[3][3]) {
    printf("\n");

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (board[i][j] == PLAYER) {
                setColor(BLUE);
            } else if (board[i][j] == BOT) {
                setColor(RED);
            } else {
                setColor(WHITE);
            }

            printf("   %c   ", board[i][j]);
            setColor(RESET);  // Reset color after each cell

            if (j < 2) {
                printf("|");
            }
        }
        printf("\n");
        if (i < 2) {
        	printf("\n");
            printf("-------|-------|-------\n");
        }
    }
    
    printf("\n");
}

void print_boardToMakeMove(char board[3][3], int col, int row) {
    printf("\n");

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (board[i][j] == PLAYER) {
                setColor(BLUE);
            } else if (board[i][j] == BOT) {
                setColor(RED);
            } else {
                setColor(WHITE);
            }
            
            if(j == col && i == row){
            	 printf("-> %c   ", board[i][j]);
            setColor(RESET);  // Reset color after each cell
			}else{
				 printf("   %c   ", board[i][j]);
            setColor(RESET);  // Reset color after each cell
			}

            if (j < 2) {
                printf("|");
            }
        }
        printf("\n");
        if (i < 2) {
        	printf("\n");
            printf("-------|-------|-------\n");
        }
    }
    
    printf("\n");
}

// Function to check if the game is over
bool is_game_over(char board[3][3])
{
    if (check_winner(board) != EMPTY_CELL)
        return true;

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (board[i][j] == EMPTY_CELL)
            {
                return false;
            }
        }
    }

    return true;
}

char check_winner(char board[3][3])
{
    for (int i = 0; i < 3; i++)
    {
        if (board[i][0] != EMPTY_CELL && board[i][0] == board[i][1] && board[i][1] == board[i][2])
            return board[i][0]; 
        if (board[0][i] != EMPTY_CELL && board[0][i] == board[1][i] && board[1][i] == board[2][i])
            return board[0][i]; 
    }

    if (board[0][0] != EMPTY_CELL && board[0][0] == board[1][1] && board[1][1] == board[2][2])
        return board[0][0];
    if (board[0][2] != EMPTY_CELL && board[0][2] == board[1][1] && board[1][1] == board[2][0])
        return board[0][2]; 

    return EMPTY_CELL; 
}


int generateScore(char board[3][3]){
	
	for (int i = 0; i < 3; i++)
    {
        if (board[i][0] != EMPTY_CELL && board[i][0] == board[i][1] && board[i][1] == board[i][2])
            return 100; 
        if (board[0][i] != EMPTY_CELL && board[0][i] == board[1][i] && board[1][i] == board[2][i])
            return 100; 
    }

    if (board[0][0] != EMPTY_CELL && board[0][0] == board[1][1] && board[1][1] == board[2][2])
        return 100; 
    if (board[0][2] != EMPTY_CELL && board[0][2] == board[1][1] && board[1][1] == board[2][0])
        return 100; 
        
    for (int i = 0; i < 3; i++) {
        if ((board[i][0] == BOT && board[i][1] == BOT && board[i][2] == PLAYER) ||
            (board[i][0] == BOT && board[i][2] == BOT && board[i][1] == PLAYER) ||
            (board[i][1] == BOT && board[i][2] == BOT && board[i][0] == PLAYER)) {
            return 50;
        }
         if ((board[0][i] == BOT && board[1][i] == BOT && board[2][i] == PLAYER) ||
            (board[0][i] == BOT && board[2][i] == BOT && board[1][i] == PLAYER) ||
            (board[1][i] == BOT && board[2][i] == BOT && board[0][i] == PLAYER)) {
            return 50;
        }
    }
    

    // Check diagonals
    if ((board[0][0] == BOT && board[1][1] == BOT && board[2][2] == PLAYER) ||
        (board[0][0] == BOT && board[2][2] == BOT && board[1][1] == PLAYER) ||
        (board[1][1] == BOT && board[2][2] == BOT && board[0][0] == PLAYER) ||
        (board[0][2] == BOT && board[1][1] == BOT && board[2][0] == PLAYER) ||
        (board[0][2] == BOT && board[2][0] == BOT && board[1][1] == PLAYER) ||
        (board[1][1] == BOT && board[2][0] == BOT && board[0][2] == PLAYER)) {
        return 50;
    }

    return 10; 
	
}

int generateScorePlayer2(char board[3][3]){
	
	for (int i = 0; i < 3; i++)
    {
        if (board[i][0] != EMPTY_CELL && board[i][0] == board[i][1] && board[i][1] == board[i][2])
            return 100; 
        if (board[0][i] != EMPTY_CELL && board[0][i] == board[1][i] && board[1][i] == board[2][i])
            return 100; 
    }

    if (board[0][0] != EMPTY_CELL && board[0][0] == board[1][1] && board[1][1] == board[2][2])
        return 100; 
    if (board[0][2] != EMPTY_CELL && board[0][2] == board[1][1] && board[1][1] == board[2][0])
        return 100; 
        
    for (int i = 0; i < 3; i++) {
        if ((board[i][0] == PLAYER && board[i][1] == PLAYER && board[i][2] == BOT) ||
            (board[i][0] == PLAYER && board[i][2] == PLAYER && board[i][1] == BOT) ||
            (board[i][1] == PLAYER && board[i][2] == PLAYER && board[i][0] == BOT)) {
            return 50;
        }
         if ((board[0][i] == PLAYER && board[1][i] == PLAYER && board[2][i] == BOT) ||
            (board[0][i] == PLAYER && board[2][i] == PLAYER && board[1][i] == BOT) ||
            (board[1][i] == PLAYER && board[2][i] == PLAYER && board[0][i] == BOT)) {
            return 50;
        }
    }
    

    // Check diagonals
    if ((board[0][0] == PLAYER && board[1][1] == PLAYER && board[2][2] == BOT) ||
        (board[0][0] == PLAYER && board[2][2] == PLAYER && board[1][1] == BOT) ||
        (board[1][1] == PLAYER && board[2][2] == PLAYER && board[0][0] == BOT) ||
        (board[0][2] == PLAYER && board[1][1] == PLAYER && board[2][0] == BOT) ||
        (board[0][2] == PLAYER && board[2][0] == PLAYER && board[1][1] == BOT) ||
        (board[1][1] == PLAYER && board[2][0] == PLAYER && board[0][2] == BOT)) {
        return 50;
    }

    return 10; 
	
}


TreeScore *create_node(char player[], int score)
{
    TreeScore *new_node = (TreeScore *)malloc(sizeof(TreeScore));
    if (new_node)
    {
        strcpy(new_node->player, player);
        new_node->score = score;
        new_node->left = NULL;
        new_node->right = NULL;
    }
    return new_node;
}

TreeTime *create_node2(char player[], double elapsed_time)
{
    TreeTime *new_node = (TreeTime *)malloc(sizeof(TreeTime));
    if (new_node)
    {
        strcpy(new_node->player, player);
        new_node->elapsed_time = elapsed_time;
        new_node->left = NULL;
        new_node->right = NULL;
    }
    return new_node;
}

TreeTime *insertTime(TreeTime *root, char player[], double elapsed_time)
{
    if (root == NULL)
    {
        return create_node2(player, elapsed_time);
    }
    if (elapsed_time >= root->elapsed_time)
    {
        root->right = insertTime(root->right, player, elapsed_time);
    }
    else
    {
        root->left = insertTime(root->left, player, elapsed_time);
    }
    return root;
}

TreeScore *insertScore(TreeScore *root, char player[], int score)
{
    if (root == NULL)
    {
        return create_node(player, score);
    }
    if (score <= root->score)
    {
        root->right = insertScore(root->right, player, score);
    }
    else
    {
        root->left = insertScore(root->left, player, score);
    }
    return root;
}

void print_inorder(TreeScore* root) {
    if(root !=NULL){
    	print_inorder(root->left);
    	printf("| %s\t      |\t  %d\t  | \n",root->player, root->score);
    	print_inorder(root->right);
	}
}

void print_inorderTime(TreeTime* root) {
    if(root !=NULL){
    	print_inorderTime(root->left);
        // Calculate elapsed time in seconds
        double elapsed_time = difftime(root->end_time, root->start_time);
        elapsed_time = elapsed_time * -1;
        printf("| %s\t      |\t %.2f seconds\t |\n", root->player, root->elapsed_time); // Display elapsed time
        print_inorderTime(root->right);
	}
}

void playSoundEffect(const char *soundName){
	const char *soundFile = soundName;

    // Play the sound file
    PlaySound(TEXT(soundFile), NULL, SND_FILENAME | SND_ASYNC);
    
    	Sleep(2000);

}

void setColor(int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}




