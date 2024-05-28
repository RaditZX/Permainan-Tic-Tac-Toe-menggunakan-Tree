#include "bot.h"

TreeNode *create_node(char board[3][3])
{
    TreeNode *new_node = (TreeNode *)malloc(sizeof(TreeNode));
    if (new_node)
    {
        memcpy(new_node->board, board, sizeof(char) * 3 * 3);
        new_node->left = NULL;
        new_node->right = NULL;
    }
    return new_node;
}

// Function to deallocate memory used by the tree nodes
void delete_tree(TreeNode *root)
{
    if (root)
    {
        delete_tree(root->left);
        delete_tree(root->right);
        free(root);
    }
}

boolean isMovesLeft(char board[3][3])
{
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (board[i][j] == '_')
                return true;
    return false;
}



int evaluate(char b[3][3])
{
    for (int row = 0; row < 3; row++)
    {
        if (b[row][0] == b[row][1] &&
            b[row][1] == b[row][2])
        {
            if (b[row][0] == BOT)
                return +10;
            else if (b[row][0] == PLAYER)
                return -10;
        }
    }

    for (int col = 0; col < 3; col++)
    {
        if (b[0][col] == b[1][col] &&
            b[1][col] == b[2][col])
        {
            if (b[0][col] == BOT)
                return +10;

            else if (b[0][col] == PLAYER)
                return -10;
        }
    }

    if (b[0][0] == b[1][1] && b[1][1] == b[2][2])
    {
        if (b[0][0] == BOT)
            return +10;
        else if (b[0][0] == PLAYER)
            return -10;
    }

    if (b[0][2] == b[1][1] && b[1][1] == b[2][0])
    {
        if (b[0][2] == BOT)
            return +10;
        else if (b[0][2] == PLAYER)
            return -10;
    }

    int emptyCells = 0;
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            if (b[i][j] == EMPTY_CELL)
                ++emptyCells;
        }
    }

    return emptyCells;
}

int minimax(TreeNode *root, int depth, int alpha, int beta, boolean isMax)
{
    char board[3][3];
    memcpy(board, root->board, sizeof(char) * 3 * 3);

    int score = evaluate(board);

    if (score == 10)
        return score - depth;


    if (score == -10)
        return score + depth;


    if (!isMovesLeft(board))
        return 0;

    if (isMax)
    {
        int best = INT_MIN; 


        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                // Periksa jika sel kosong
                if (board[i][j] == EMPTY_CELL)
                {
                    // Lakukan langkah untuk pemain maksimal (X)
                    board[i][j] = BOT;

                    // Buat node anak baru
                    TreeNode *child = create_node(board);

                    // Panggil rekursif minimax untuk mencari nilai terbaik
                    int val = minimax(child, depth + 1, alpha, beta, !isMax);

                    // Batalkan langkah
                    board[i][j] = EMPTY_CELL;

                    // Update nilai alpha
                    alpha = fmax(alpha, val);

                    // Lakukan pemangkasan alpha-beta
                    if (beta <= alpha)
                    {
                        delete_tree(child); // Hapus node anak yang tidak dibutuhkan
                        break;              // Pemangkasan
                    }

                    // Update nilai terbaik
                    best = fmax(best, val);

                    // Atur anak ke node saat ini
                    root->left = child;
                }
            }
        }
        return best;
    }
    else // Jika giliran pemain minimal
    {
        int best = INT_MAX; // Inisialisasi nilai terbaik untuk pemain minimal

        // Traverse semua sel pada papan
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                // Periksa jika sel kosong
                if (board[i][j] == EMPTY_CELL)
                {
                    // Lakukan langkah untuk pemain minimal (O)
                    board[i][j] = PLAYER;

                    // Buat node anak baru
                    TreeNode *child = create_node(board);

                    // Panggil rekursif minimax untuk mencari nilai terbaik
                    int val = minimax(child, depth + 1, alpha, beta, !isMax);

                    // Batalkan langkah
                    board[i][j] = EMPTY_CELL;

                    // Update nilai beta
                    beta = fmin(beta, val);

                    // Lakukan pemangkasan alpha-beta
                    if (beta <= alpha)
                    {
                        delete_tree(child); // Hapus node anak yang tidak dibutuhkan
                        break;              // Pemangkasan
                    }

                    // Update nilai terbaik
                    best = fmin(best, val);

                    // Atur anak ke node saat ini
                    root->right = child;
                }
            }
        }
        return best;
    }
}

void bot_make_move(char board[3][3], char player)
{
    int bestVal = -1000;

    int row = -1;
    int col = -1;

    TreeNode *root = create_node(board);

    // Traverse all cells, evaluate minimax function for
    // all empty cells. And return the cell with optimal
    // value.
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            // Check if cell is empty
            if (board[i][j] == EMPTY_CELL)
            {
                // Make the move
                board[i][j] = player;
                // Create a new node for the move
                TreeNode *child = create_node(board);

                // Compute evaluation function for this move.
                int moveVal = minimax(child, 0, INT_MIN, INT_MAX, false);
                // Undo the move
                board[i][j] = EMPTY_CELL;

                // If the value of the current move is more than the best value, then update best
                if (moveVal > bestVal)
                {
                    row = i;
                    col = j;
                    bestVal = moveVal;
                }
            }
        }
    }

    // Make the best move
    board[row][col] = player;

    // Delete the tree
    delete_tree(root);
}
