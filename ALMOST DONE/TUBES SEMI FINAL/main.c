#include <unistd.h> // For usleep function
#include "TicTacToe.h"
#include "player.h"
#include "bot.h"
#include "boolean.h"
#include "fileSystem.h"

int main()  
{
    char choice;
    int score = 0;
    TreeScore *root = NULL;
    TreeTime *rootTime = NULL;
    time_t start_time; 
    time_t end_time;   
    double elapsed_time; 

    do
    {
        printMainMenu();
        scanf(" %c", &choice);

        switch (choice)
        {
            case '1':
            {
                clearScreen();
                printAsciiArt();
                printf("\033[1;33m"); // Set color to yellow
                printf("You chose to play against the Bot.\n");
                printf("Preparing the game ");
                loadingAnimation();
                printf("Let's start the game!\n");
                

                start_time = time(NULL); // Start time of the game
                
                char board[3][3];
                char *player1Name = (char *)malloc(20 * sizeof(char));
                
                if (player1Name == NULL ) {
                    printf("Memory allocation failed\n");
                    return 1;
                }
                
                clearScreen();
                printf("Enter player 1's name: ");
                getchar();
                fgets(player1Name, 20, stdin);
                
                size_t len = strlen(player1Name);
                if (len > 0 && player1Name[len - 1] == '\n') {
                    player1Name[len - 1] = '\0';
                }
                
                initialize_board(board);

                char current_player = PLAYER;

                while (!is_game_over(board))
            {
            	clearScreen();
            	printDecorativeLine();
                printf("\t\t\t      P L A Y  W I T H  B O T\n");
                printDecorativeLine();
                printf("Current board:\n");
                printf("Score: %d\n", score);
                printf("Use Arrow key to select the row or columns\n");
                print_boardToMakeMove(board,0,0);
                printf("%s turns",player1Name );

                if (current_player == PLAYER)
                {
                	
                    entryMove(board,PLAYER, player1Name, score, true);
                    score += generateScore(board);
                    system("cls");
                }
                else
                {
                    printf("Bot's turn...\n");
                    bot_make_move(board, BOT);
                    system("cls");
                }
                current_player = (current_player == BOT) ? PLAYER : BOT;
            }


                printf("Final board:\n");
                print_board(board);

                char winner = check_winner(board);

                end_time = time(NULL); 
                elapsed_time = difftime(end_time, start_time); 
                printf("Elapsed time: %.2f seconds\n", elapsed_time);
 			if (winner == BOT)
            {
                printf("BOT wins!\n");
                rootTime = insertTime(rootTime, "Bot", elapsed_time);
                playSoundEffect("lose.wav");
            }
            else if (winner == PLAYER)
            {
                root = insertScore(root, player1Name, score);
                printf("Name: %s            Score: %d\n",player1Name, score);
                printf("%s wins!\n", player1Name);
                rootTime = insertTime(rootTime, player1Name, elapsed_time);
                playSoundEffect("win.wav");
            }
            else
            {
            	root = insertScore(root, player1Name, score);
                rootTime = insertTime(rootTime, player1Name, elapsed_time);   
                printf("It's a draw!\n");
                playSoundEffect("draw.wav");
            }
            saveBinaryTree(root, "scoreFile.txt");
            saveBinaryTreeTime(rootTime, "timeFile.txt");
            system("pause");

                break;
            }

            case '2':
            {
                clearScreen();
                printAsciiArt();
                printf("\033[1;33m"); // Set color to yellow
                printf("You chose to play with a Friend.\n");
                printf("Please wait ");
                loadingAnimation();
                printf("Get ready for some fun!\n");

                char board[3][3];
                initialize_board(board);
                char *player1Name = (char *)malloc(20 * sizeof(char));
                char *player2Name = (char *)malloc(20 * sizeof(char));
                int player1_score = 0;
                int player2_score = 0;
                
                if (player1Name == NULL || player2Name == NULL) {
                    printf("Memory allocation failed\n");
                    return 1;
                }
                
                clearScreen();
                printDecorativeLine();
                printf("\t\t\t     P L A Y  W I T H  F R I E N D S\n");
                printDecorativeLine();
                printf("Enter player 1's name: ");
                getchar();
                fgets(player1Name, 20, stdin);
                
                printf("Enter player 2's name: ");
                fgets(player2Name, 20, stdin);
                
                start_time = time(NULL); // Start time of the game
                
                // Remove newline characters from names if present
                size_t len = strlen(player1Name);
                if (len > 0 && player1Name[len - 1] == '\n') {
                    player1Name[len - 1] = '\0';
                }
                
                len = strlen(player2Name);
                if (len > 0 && player2Name[len - 1] == '\n') {
                    player2Name[len - 1] = '\0';
                }
                

                char current_player = PLAYER;

                while (!is_game_over(board))
                {
                    clearScreen();
                    printDecorativeLine();
	                printf("\t\t\t     P L A Y  W I T H  F R I E N D S\n");
	                printDecorativeLine();
                    printf("Current board:\n");
                    printf("%s score: %d \t\t %s score: %d", player1Name,player1_score, player2Name,player2_score );
                    print_board(board);
                    entryMove(board, current_player, current_player == PLAYER? player1Name:player2Name, current_player == PLAYER? player1_score:player2_score, false);
                    (current_player == PLAYER) ? player1_score += generateScore(board) : player2_score += generateScorePlayer2(board);
                    current_player = (current_player == PLAYER) ? BOT : PLAYER;
                }

                printf("Final board:\n");
                print_board(board);
				end_time = time(NULL);
				elapsed_time = difftime(end_time, start_time); 
                char winner = check_winner(board);
                if (winner == BOT)
            {
            	playSoundEffect("win.wav");
            	root = insertScore(root, player2Name, player2_score);
            	
                printf("%s  wins!\n", player2Name);
            }
            else if (winner == PLAYER)
            {
            	playSoundEffect("win.wav");
            	root = insertScore(root, player1Name, player1_score);
                printf("%s wins!\n", player1Name);
            }
            else
            {
                printf("It's a draw!\n");
                playSoundEffect("draw.wav");
            }
            break;
            saveBinaryTree(root, "scoreFile.txt");
            saveBinaryTreeTime(rootTime, "timeFile.txt");
            system("pause");

                break;
            }

            case '3':
            {
                int i,j = 1;
                clearScreen();
                do
                {
                    printAsciiArt();
                    printDecorativeLine();
	                printf("\t\t    S C O R E  B O A R D S\n");
	                printDecorativeLine();
                    printf("\033[1;33m"); // Set color to yellow
                    printf("===========================\n");
                    printf("|        	 	  |\n");
                    printf("| 1. Board based on score |\n");
                    printf("| 2. Board based on time  |\n");
                    printf("| 3. Exit                 |\n");
                    printf("|        	 	  |\n");
                    printf("===========================\n");
                    printf("Enter your choice: ");
                    scanf(" %c", &choice);

                    switch (choice)
                    {
                        case '1':
                            root = loadBinaryTree("scoreFile.txt");
                            clearScreen();
                            printDecorativeLine();
			                printf("\t\t    S C O R E  B O A R D  B A S E D  O N  S C O R E\n");
			                printDecorativeLine();
                            printf("=========================================================================\n");
                            printf("|             Player Name             |               Score             |\n");
                            printf("=========================================================================\n");
                            print_inorder(root);
                            printf("=========================================================================\n");
                            system("pause");
                            printf("\033[0m"); // Reset color
                            break;

                        case '2':
                            rootTime = loadBinaryTreeTime("timeFile.txt");
                            clearScreen();
                            printDecorativeLine();
                            printf("\t\t    S C O R E  B O A R D  B A S E D  O N  T I M E\n");
                            printDecorativeLine();
                            printf("=========================================================================\n");
                            printf("|             Player Name             |            Time Lapsed          |\n");
                            printf("=========================================================================\n");
                            print_inorderTime(rootTime);
                            printf("=========================================================================\n");
                            system("pause");
                            printf("\033[0m"); // Reset color
                            break;
                    }
                } while (choice != '3');
                break;
            }

            case '4':
            {
                printf("Exiting the game. Goodbye!\n");
                break;
            }

            default:
            {
                clearScreen();
                printf("\033[1;31m"); // Set color to red
                printf("Invalid choice. Please enter a number between 1 and 4.\n");
                printf("\033[0m"); // Reset color
                system("pause");
                break;
            }
        }
    } while (choice != '4');

    return 0;
}
