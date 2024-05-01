#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <cstring>
#include <float.h> 
#include <math.h>

#define fmax(a, b)  ((a) > (b) ? (a) : (b))
#define fmin(a, b)  ((a) < (b) ? (a) : (b))
#define PLAYER_X 'X'
#define PLAYER_O 'O'
#define EMPTY_CELL ' '


// Structure for a Tic Tac Toe board and its children
typedef struct TreeNode {
  char board[3][3];
  struct TreeNode* children[9]; // Maximum 9 possible moves
  int num_children;
} TreeNode;

// Function to create a new node in the tree
TreeNode* createNode(char board[3][3]) {
  TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
  if (newNode == NULL) {
    printf("Memory allocation failed!\n");
    exit(1);
  }
  // Copy board state to new node
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      newNode->board[i][j] = board[i][j];
    }
  }
  newNode->num_children = 0; // Initially no children
  return newNode;
}

// Function to check if the game is over
bool is_game_over(char board[3][3]) {
  // Check rows
  for (int i = 0; i < 3; i++) {
    if (board[i][0] != EMPTY_CELL && board[i][0] == board[i][1] && board[i][1] == board[i][2]) {
      return true;
    }
  }

  // Check columns
  for (int j = 0; j < 3; j++) {
    if (board[0][j] != EMPTY_CELL && board[0][j] == board[1][j] && board[1][j] == board[2][j]) {
      return true;
    }
  }

  // Check diagonals
  if (board[0][0] != EMPTY_CELL && board[0][0] == board[1][1] && board[1][1] == board[2][2]) {
    return true;
  }
  if (board[0][2] != EMPTY_CELL && board[0][2] == board[1][1] && board[1][1] == board[2][0]) {
    return true;
  }

  // Check for a draw (all cells filled)
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      if (board[i][j] == EMPTY_CELL) {
        return false;
      }
    }
  }

  return true;
}

// Function to add a child node with a new board state
void add_child(TreeNode* parent, char board[3][3]) {
  TreeNode* child = createNode(board);
  parent->children[parent->num_children++] = child;
}

// Function to generate all possible moves for a given board
void generate_moves(TreeNode* node, char player) {
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      if (node->board[i][j] == EMPTY_CELL) {
        char new_board[3][3];
        for (int k = 0; k < 3; k++) {
          for (int l = 0; l < 3; l++) {
            new_board[k][l] = node->board[k][l];
          }
        }
        new_board[i][j] = player;
        add_child(node, new_board);
      }
    }
  }
}

char check_winner(char board[3][3]) {
    // Check rows
    for (int i = 0; i < 3; i++) {
        if (board[i][0] != EMPTY_CELL && board[i][0] == board[i][1] && board[i][1] == board[i][2]) {
            return board[i][0];
        }
    }

    // Check columns
    for (int j = 0; j < 3; j++) {
        if (board[0][j] != EMPTY_CELL && board[0][j] == board[1][j] && board[1][j] == board[2][j]) {
            return board[0][j];
        }
    }

    // Check diagonals
    if (board[0][0] != EMPTY_CELL && board[0][0] == board[1][1] && board[1][1] == board[2][2]) {
        return board[0][0];
    }
    if (board[0][2] != EMPTY_CELL && board[0][2] == board[1][1] && board[1][1] == board[2][0]) {
        return board[0][2];
    }

    // Check for a draw (all cells filled)
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == EMPTY_CELL) {
                return ' '; // Game not over yet
            }
        }
    }

    return EMPTY_CELL; // Draw
}


int evaluate_line(int x_count, int o_count) {
  if (x_count == 3) {
    return 5; // Strong potential for X to win this line
  } else if (o_count == 3) {
    return -5; // Strong potential for O to win this line
  } else if (x_count == 2 && o_count == 0) {
    return 2; // X has a potential winning line
  } else if (x_count == 0 && o_count == 2) {
    return -2; // O has a potential winning line
  } else {
    return 0; // No significant threat or opportunity on this line
  }
}

int evaluate_board(char board[3][3]) {
  // Check for winner and assign scores accordingly
  if (check_winner(board) == PLAYER_X) {
    return 10; // Player X wins, high positive score
  } else if (check_winner(board) == PLAYER_O) {
    return -10; // Player O wins, high negative score
  } else {
    // No winner yet, evaluate based on potential threats and opportunities
    int score = 0;

    // Count potential winning lines for X and O
    int x_count = 0;
    int o_count = 0;
    for (int i = 0; i < 3; i++) {
      // Check rows
      x_count = (board[i][0] == PLAYER_X) + (board[i][1] == PLAYER_X) + (board[i][2] == PLAYER_X);
      o_count = (board[i][0] == PLAYER_O) + (board[i][1] == PLAYER_O) + (board[i][2] == PLAYER_O);
      score += evaluate_line(x_count, o_count);

      // Check columns (similar logic)
      x_count = (board[0][i] == PLAYER_X) + (board[1][i] == PLAYER_X) + (board[2][i] == PLAYER_X);
      o_count = (board[0][i] == PLAYER_O) + (board[1][i] == PLAYER_O) + (board[2][i] == PLAYER_O);
      score += evaluate_line(x_count, o_count);
    }

    // Check diagonals
    x_count = (board[0][0] == PLAYER_X) + (board[1][1] == PLAYER_X) + (board[2][2] == PLAYER_X);
    o_count = (board[0][0] == PLAYER_O) + (board[1][1] == PLAYER_O) + (board[2][2] == PLAYER_O);
    score += evaluate_line(x_count, o_count);

    x_count = (board[0][2] == PLAYER_X) + (board[1][1] == PLAYER_X) + (board[2][0] == PLAYER_X);
    o_count = (board[0][2] == PLAYER_O) + (board[1][1] == PLAYER_O) + (board[2][0] == PLAYER_O);
    score += evaluate_line(x_count, o_count);

    // Add a bonus for blocking the opponent's winning move
    if (check_winner(board) == PLAYER_O) {
      score += 5; // Bonus for blocking player O from winning
    }

    return score;
  }
}

int minimax(TreeNode* node, bool isMaximizingPlayer, int depth, int alpha, int beta) {
  // Base cases (terminal states or maximum depth reached)
  if (is_game_over(node->board) || depth == 0) {
    return evaluate_board(node->board);
  }

  // Recursive minimax logic
  if (isMaximizingPlayer) {
    int best_score = -INFINITY;
    for (int i = 0; i < node->num_children; i++) {
      int score = minimax(node->children[i], false, depth - 1, alpha, beta);
      best_score = fmax(best_score, score); // Find the maximum score for Max
      alpha = fmax(alpha, best_score); // Update alpha
      if (beta <= alpha) {
        break; // Prune the search if beta <= alpha (maximizer won't choose)
      }
    }
    return best_score;
  } else { // Minimizing player
    int best_score = INFINITY;
    for (int i = 0; i < node->num_children; i++) {
      int score = minimax(node->children[i], true, depth - 1, alpha, beta);
      best_score = fmin(best_score, score); // Find the minimum score for Min
      beta = fmin(beta, best_score); // Update beta
      if (beta <= alpha) {
        break; // Prune the search if beta <= alpha (minimizer won't choose)
      }
    }
    return best_score;
  }
}



// Define the free_tree function to deallocate memory used by the tree nodes
void free_tree(TreeNode* node) {
    if (node == NULL)
        return;
    for (int i = 0; i < node->num_children; i++) {
        free_tree(node->children[i]);
    }
    free(node);
}

void initialize_board(char board[3][3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            board[i][j] = EMPTY_CELL;
        }
    }
}

void print_board(char board[3][3]) {
    printf("\n");
    printf(" %c | %c | %c \n", board[0][0], board[0][1], board[0][2]);
    printf("---|---|---\n");
    printf(" %c | %c | %c \n", board[1][0], board[1][1], board[1][2]);
    printf("---|---|---\n");
    printf(" %c | %c | %c \n", board[2][0], board[2][1], board[2][2]);
    printf("\n");
}

int best_score = INT_MIN;
   
// Function prototypes (assuming they're defined elsewhere)
TreeNode* createNode(char board[3][3]);
void add_child(TreeNode* parent, char board[3][3]);
void generate_moves(TreeNode* node, char player);
bool is_game_over(char board[3][3]);
int evaluate_board(char board[3][3]);
int minimax(TreeNode* node, bool isMaximizingPlayer, int depth, int alpha, int beta);
void free_tree(TreeNode* node); // Memory deallocation function (important!)

int main() {
    char choice;
    do {
        printf("\nTic Tac Tactics\n");
		printf("made by Daffa and Daiva\n");
		printf("-----------------\n");
		printf("|		|\n");
		printf("| 1. Play	|\n");
		printf("| 2. Exit	|\n");
		printf("|		|\n");
		printf("-----------------\n");
        printf("Enter your choice: ");
        scanf(" %c", &choice);

        switch(choice) {
            case '1': {
                // Initialize empty board
                char board[3][3];
                initialize_board(board);

                char current_player = PLAYER_X; // X starts the game

                while (!is_game_over(board)) {
                    // Print the current board
                    printf("Current board:\n");
                    print_board(board);

                    // Player's turn
                    if (current_player == PLAYER_X) {
                        printf("Player X's turn (row col): ");
                        int row, col;
                        scanf("%d %d", &row, &col);

                        // Validate user input
                        while (row < 0 || row > 2 || col < 0 || col > 2 || board[row][col] != EMPTY_CELL) {
                            printf("Invalid move. Try again (row col): ");
                            scanf("%d %d", &row, &col);
                        }

                        board[row][col] = PLAYER_X;
                    } else { // AI's turn (Minimax)
                        printf("Thinking...\n");

                        // Create the root node of the minimax tree
                        TreeNode* root = createNode(board);
                        generate_moves(root, current_player); // Generate possible moves for AI

                        // Use minimax algorithm to find the best move
                        int best_move_score = minimax(root, false, 1, -INFINITY, INFINITY);

                        // Find the child node corresponding to the best move
                        TreeNode* best_move_node = NULL;
                        for (int i = 0; i < root->num_children; i++) {
                            if (evaluate_board(root->children[i]->board) == best_move_score) {
                                best_move_node = root->children[i];
                                break;
                            }
                        }

                        // Apply the best move to the board
                        memcpy(board, best_move_node->board, sizeof(board)); // Copy the board state
                        free_tree(root); // Deallocate memory used by the tree (important!)
                    }

                    // Switch player for the next turn
                    current_player = (current_player == PLAYER_X) ? PLAYER_O : PLAYER_X;
                }

                // Print the final board
                printf("Final board:\n");
                print_board(board);

                // Announce the winner or draw
                if (check_winner(board) == PLAYER_X) {
                    printf("Player X wins!\n");
                } else if (check_winner(board) == PLAYER_O) {
                    printf("Player O wins!\n");
                } else {
                    printf("It's a draw!\n");
                }
                break;
            }
            case '2':
                printf("Exiting the game. Goodbye!\n");
                break;
            default:
                printf("Invalid choice. Please enter 1 or 2.\n");
        }
    } while (choice != '2');

    return 0;
}
