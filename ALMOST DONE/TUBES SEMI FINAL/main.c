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
    	system("cls");
        printf("\nTic Tac Tactics\n");
        printf("made by Daffa and Daiva\n");
        printf("==========================\n");
        printf("|        		 |\n");
        printf("| 1. Play against Bot    |\n");
        printf("| 2. Play with a Friend  |\n");
        printf("| 3. Show Leaderboard    |\n");
        printf("| 3. Exit                |\n");
        printf("|      		   	 |\n");
        printf("==========================\n");
        printf("Enter your choice: ");
        scanf(" %c", &choice);

        switch (choice)
        {
        case '1':
        {
        	score = 0;
            start_time = time(NULL); // Start time of the game
            char board[3][3];
            char *player1Name;
		   
		
		    player1Name = (char *)malloc(20 * sizeof(char));
		
		    if (player1Name == NULL ) {
		        printf("Memory allocation failed\n");
		        return 1;
		    }
			system("cls");
		    printf("Masukkan nama player 1 : ");
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
                printf("Current board:\n");
                printf("Score: %d\n", score);
                printf("Use Arrow key to select the row or columns\n");
                print_boardToMakeMove(board,0,0);
                printf("%s turns",player1Name );

                if (current_player == PLAYER)
                {
                	
                    entryMove(board,PLAYER, player1Name, score);
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
                printf("Player wins!\n");
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
            char board[3][3];
		    initialize_board(board);
		    char current_player = PLAYER;
		    char *player1Name;
		    char *player2Name;
		    int player1_score = 0;
		    int player2_score = 0;
		
		    player1Name = (char *)malloc(20 * sizeof(char));
		    player2Name = (char *)malloc(20 * sizeof(char));
		
		    if (player1Name == NULL || player2Name == NULL) {
		        printf("Memory allocation failed\n");
		        return 1;
		    }
		    
			system("cls");
		    printf("Masukkan nama player 1 : ");
		    getchar();
		    fgets(player1Name, 20, stdin);
		
		    printf("Masukkan nama player 2 : ");
		    fgets(player2Name, 20, stdin);
		
		    // Remove newline characters from names if present
		    size_t len = strlen(player1Name);
		    if (len > 0 && player1Name[len - 1] == '\n') {
		        player1Name[len - 1] = '\0';
		    }
		    
		    len = strlen(player2Name);
		    if (len > 0 && player2Name[len - 1] == '\n') {
		        player2Name[len - 1] = '\0';
		    }

            while (!is_game_over(board))
            {
                printf("Current board:\n");
                printf("%s score: %d \t\t %s score: %d", player1Name,player1_score, player2Name,player2_score );
                print_board(board);
                entryMove(board, current_player, current_player == PLAYER? player1Name:player2Name, player1_score);
				(current_player == PLAYER) ? player1_score = player1_score + generateScore(board) : player2_score = player2_score + generateScorePlayer2(board);
                current_player = (current_player == PLAYER) ? BOT : PLAYER;
            }

            printf("Final board:\n");
            print_board(board);

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
        }
        case '3':
        {
        	int i,j = 1;
        	system("cls");
            do
            {
            	
                printf("\nTic Tac Tactics\n");
                printf("made by Daffa and Daiva\n");
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
                    printf("\nScore Board Based on Score\n");
                    printf("===========================\n");
                    printf("| Player Name |   Score   |\n");
                    printf("===========================\n");
                    print_inorder(root);
                    printf("===========================\n");
                    system("pause");
                    system("cls");
                    break;
                case '2':
                	rootTime = loadBinaryTreeTime("timeFile.txt");
                    printf("\nScore Board Based on Time\n");
                    printf("==================================\n");
                    printf("| Player Name |   Time Lapsed    |\n");
                    printf("=================================\n");
                    print_inorderTime(rootTime);
                    printf("==================================\n");
                    system("pause");
                    system("cls");
                    break;
                }
            } while (choice != '3');
            break;
        }
        case '4':
            printf("Exiting the game. Goodbye!\n");
            break;
        default:
            printf("Invalid choice. Please enter 1, 2, 3, or 4.\n");
        }
    } while (choice != '4');

    return 0;
}
