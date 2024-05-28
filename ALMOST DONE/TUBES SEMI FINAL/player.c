#include "player.h"
#include "TicTacToe.h"

void entryMove(char board[3][3], char current_player, char *playerName, int score, bool withBot)
{

   int col = 0,row = 0;
   int ch;
   while ((ch = getch()) != 13) { // ASCII value of Enter key is 13
        if (ch == 0 || ch == 0xE0) { // Extended key
            ch = getch(); // Get the actual key code
            switch (ch) {
                case 72: // Up arrow
                system("cls");
                 printDecorativeLine();
                if(withBot){
                	printf("\t\t\t      P L A Y  W I T H  B O T\n");
				}else{
					printf("\t\t\t     P L A Y  W I T H  F R I E N D S\n");
				}
                printDecorativeLine();
                printf("Current board:\n");
                printf("Score: %d\n", score);
                printf("Use Arrow key to select the row or columns\n");
                    row--;
                    if(row < 0){
                    	row = 2;
					}
                    print_boardToMakeMove(board, col, row);
                    printf("%s turns",playerName );
                    break;
                case 80: // Down arrow
	                system("cls");
	                 printDecorativeLine();
	                 if(withBot){
	                	printf("\t\t\t      P L A Y  W I T H  B O T\n");
					}else{
						printf("\t\t\t     P L A Y  W I T H  F R I E N D S\n");
					}
	                printDecorativeLine();
	                printf("Current board:\n");
	                printf("Score: %d\n", score);
	                printf("Use Arrow key to select the row or columns\n");
                    row++;
                    if(row > 2){
                    	row = 0;
					}
                    print_boardToMakeMove(board, col, row);
                    printf("%s turns",playerName );
                    break;
                case 75: // Left arrow
	                system("cls");
	                printDecorativeLine();
	                if(withBot){
	                	printf("\t\t\t      P L A Y  W I T H  B O T\n");
					}else{
						printf("\t\t\t     P L A Y  W I T H  F R I E N D S\n");
					}
                	printDecorativeLine();
	                printf("Current board:\n");
	                printf("Score: %d\n", score);
	                printf("Use Arrow key to select the row or columns\n");
	                col--;
                    if(col < 0){
                    	col = 2;
					}
                    print_boardToMakeMove(board, col, row);
                    printf("%s turns",playerName );
                    
                    break;
                case 77: // Right arrow
                	system("cls");
      			 	printDecorativeLine();
	                 if(withBot){
                		printf("\t\t\t      P L A Y  W I T H  B O T\n");
					}else{
						printf("\t\t\t     P L A Y  W I T H  F R I E N D S\n");
					}
	                printDecorativeLine();
                    printf("Current board:\n");
                    printf("Score: %d\n", score);
                    printf("Use Arrow key to select the row or columns\n");
                    col++;
                    if(col > 2){
                    	col = 0;
					}
                    print_boardToMakeMove(board, col, row);
                    printf("%s turns",playerName );
                    break;
                default:
                    break;
            }
        }
    }


	if(board[row][col] != EMPTY_CELL){
		playSoundEffect("tetot.wav");
		entryMove(board, current_player, playerName, score, withBot);
	}else{
		playSoundEffect("player1Sound.wav");
		board[row][col] = current_player;
		
	}
    
}
bool is_valid_move(char board[3][3], int row, int col)
{
    boolean valid_row = (row >= 0 && row < 3);
    boolean valid_col = (col >= 0 && col < 3);
    boolean empty_cell = (board[row][col] == EMPTY_CELL);

    return (valid_row && valid_col && empty_cell);
}
