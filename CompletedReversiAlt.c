//
// Author: Tahiya Taaha
//

#include "reversi.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

char changeLetter(int x)
{
    char letters[26] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
    return letters[x];
}

///////////////////////////////////////////////////////////////////////////////////////////

void printBoard(char board[][26], int n)
{
    //////////////////// PRINTING BOARD AND LETTER POSITION ////////////////////////
    printf("  ");
    for (int m = 0; m < n; m++)
    {
        printf("%c", changeLetter(m));
    }
    printf("\n");

    for (int x = 0; x < n; x++)
    {
        printf("%c ", changeLetter(x));
        for (int y = 0; y < n; y++)
        {
            printf("%c", board[x][y]);
        }
        printf("\n");
    }
}
///////////////////////////////////////////////////////////////////////////////////

bool positionInBounds(int n, int row, int col)
{
    if ((row >= 0) && (row < n) && (col >= 0) && (col < n))
    {
        return true;
    }
    else
    {
        return false;
    }
}

///////////////////////////////////////////////////////////////////////////////////////////

bool checkLegalInDirection(char board[][26], int n, int row, int col,
                           char colour, int deltaRow, int deltaCol)
{
    char opp;
    /////////////// DEFINING CURRENT COLOUR AND OPPOSITE COLOUR
    if (colour == 'W')
    {
        opp = 'B';
    }
    else
    {
        opp = 'W';
    }

    int m = 1;
    int currRow = row + (deltaRow * m);
    int currCol = col + (deltaCol * m);

    if ((positionInBounds(n, (currRow), (currCol))) && ((board[currRow][currCol] == 'U') || (board[currRow][currCol] == colour)))
    {
        return false;
    }

    while (positionInBounds(n, (row + deltaRow * m), (col + deltaCol * m)))
    {

        m++;
        currRow = row + (deltaRow * m);
        currCol = col + (deltaCol * m);

        ////////////////// IN CASE OF 'OPP COLOUR' ////////////////////////
        if (positionInBounds(n, currRow, currCol) && board[currRow][currCol] == colour)
        {
            return true;
        }
        else if (positionInBounds(n, currRow, currCol) && board[currRow][currCol] == 'U')
        {
            return false;
        }
        else if (positionInBounds(n, currRow, currCol) && board[currRow][currCol] == opp)
        {
            continue;
        }
        else if (!positionInBounds(n, currRow, currCol))
        {
            return false;
        }
    }

    return false;
}

//////////////////////////////////////////////////////////////

void doMove(char board[][26], int n, char colour, int row, int col)
{
    bool validity = false;
    if (positionInBounds(n, row, col) && board[row][col] == 'U')
    {
        for (int delx = -1; delx < 2; delx++)
        {
            for (int dely = -1; dely < 2; dely++)
            {

                if ((delx == 0) && (dely == 0))
                {
                    continue;
                }
                else if (!checkLegalInDirection(board, n, row, col, colour, delx, dely))
                {
                    continue;
                }
                else if (checkLegalInDirection(board, n, row, col, colour, delx, dely))
                {
                    validity = true;
                    board[row][col] = colour;

                    ////////////////// MAKING THE MOVES ////////////////////////
                    int m = 1;
                    int curX = row + (delx * m), curY = col + (dely * m);

                    while (board[curX][curY] != colour)
                    {
                        board[curX][curY] = colour;
                        m++;
                        curX = row + (delx * m);
                        curY = col + (dely * m);
                    }

                    continue;

                    ////////////////////////////////////////////////////////////
                }
            }
        }
    }

    return;
}

/////////////////////////////// SELF CREATED FUNCTION ///////////////////////

bool possibleMoves(char board[][26], int n, char colour, int x, int y)
{
    // this function tells you if a specific spot on the board is a valid move
    int m = 0;
    bool same = false;

    /////////////// ROW AND COL ////////////////////

    ////////// DIRECTIONS //////////////
    for (int delx = -1; delx < 2; delx++)
    {
        same = false;
        for (int dely = -1; dely < 2; dely++)
        {

            if ((delx == 0) && (dely == 0) || (board[x][y] != 'U'))
            {
                continue;
            }
            //////////////// IF VALID MOVE PRINT MOVE ///////////////
            if (checkLegalInDirection(board, n, x, y, colour, delx, dely))
            {
                return true;
            }
            else
            {
                continue;
            }
            ////////////////////////////////////////////////////////
        }

        if (same == true)
        {
            break;
        }
    }

    return false;

    //////////////////////////////////////////////
}

///////////// CHECKING FOR GIVEN PLAYER, IF ANY MOVES LEFT /////////////
bool valid_move_left(char board[][26], int n, char colour)
{
    for (int x = 0; x < n; x++)
    {
        for (int y = 0; y < n; y++)
        {
            for (int delx = -1; delx < 2; delx++)
            {
                for (int dely = -1; dely < 2; dely++)
                {

                    if ((delx == 0) && (dely == 0) || (board[x][y] != 'U'))
                    {
                        continue;
                    }

                    if (checkLegalInDirection(board, n, x, y, colour, delx, dely))
                    {
                        return true;
                    }
                    else
                    {
                        continue;
                    }
                }
            }
        }
    }

    return false;
}

int count_winner(char board[][26], int n, char colour)
{
    int counter = 0;
    for (int x = 0; x < n; x++)
    {
        for (int y = 0; y < n; y++)
        {
            if (board[x][y] == colour)
            {
                counter++;
            }
        }
    }

    return counter;
}

bool check_full_board(char board[][26], int n)
{

    // bool check = true;
    for (int x = 0; x < n; x++)
    {
        for (int y = 0; y < n; y++)
        {
            if (board[x][y] == 'U')
            {
                return false;
            }
        }
    }

    return true;
}

////////////////// PLAYER MOVES //////////////////////////////////////
bool player_moves(char board[][26], int n, char colour, int move1, int move2)
{

    if ((positionInBounds(n, move1, move2)) && possibleMoves(board, n, colour, move1, move2))
    {
        return true;
    }
    else if (!positionInBounds(n, move1, move2) || possibleMoves(board, n, colour, move1, move2))
    {
        return false;
    }
}

////////////////// COMPUTER MOVES ///////////////////////////////////

int makeMove(char board[26][26], int n, char turn, int *row, int *col)
{

    // check all positions valid

    int max = 0;
    int temp = 0;
    int max_row, max_col;

    for (int x = 0; x < n; x++)
    {
        for (int y = 0; y < n; y++)
        {
            temp = 0;

            for (int delx = -1; delx < 2; delx++)
            {
                for (int dely = -1; dely < 2; dely++)
                {

                    if ((delx == 0 && dely == 0) || (board[x][y] != 'U'))
                    {
                        continue;
                    }

                    /////////// TAKING IN A SPECIFIC POINT
                    if (checkLegalInDirection(board, n, x, y, turn, delx, dely))
                    {
                        temp++;
                    }
                    else
                    {
                        continue;
                    }
                }

                if ((delx == 1) && (temp > max))
                {
                    max = temp;
                    max_row = x;
                    max_col = y;
                }
            }

            // printf("[%d,%d] ", x, y);
        }
    }

    *row = max_row;
    *col = max_col;

    // ONCE LOOP COMPLETE MAKE MOVE USING THE MAX COL AND MAX ROW
}

/////////////// SELF CREATED FUNCTION ///////////////////////////////////
void dimension(int *n)
{
    printf("Enter the board dimension: ");
    scanf("%d", n);
}

void setup(char board[][26], int n)
{

    int lowerMid = floor((n - 1) / 2);
    int higherMid = ceil(n / 2);

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if ((i == lowerMid && j == lowerMid) || (i == higherMid && j == higherMid))
            {
                board[i][j] = 'W';
            }
            else if ((i == lowerMid && j == higherMid) || (i == higherMid && j == lowerMid))
            {
                board[i][j] = 'B';
            }
            else
            {
                board[i][j] = 'U';
            }
        }
    }
}

int main(void)
{
    // Write your own main function here

    ///// FIRST THING TAKING IN AN INPUT FROM USER ////
    int n = 0;
    dimension(&n);

    //////// DECLARING BOARD USEING USER DIM //////////

    char board[26][26];

    setup(board, n);

    ///////// DETERMINE PLAYERS ///////////////
    char computer;

    printf("Computer plays (B/W): ");
    scanf(" %c", &computer);

    /////////////// PRINTING OUT BOARD ////////////////

    printBoard(board, n);

    /////////////// PLAYING THE GAME ////////////////
    bool play_game = true;
    char winner;
    char B = 'B', W = 'W';
    bool invalid = false;

    while (play_game)
    {

        char move1, move2;
        int max_row, max_col;
        if (computer == 'W')
        {

            // FIRST PLAYER //////////////////////////////////////////////////////////////////////////////////////
            // checking if there are moves available first otherwise continuing
            if (!valid_move_left(board, n, B))
            {
                printf("%c player has no valid move.\n", B);
                play_game = false;
            }
            else
            {

                printf("Enter move for colour %c (RowCol): ", B);
                scanf(" %c%c", &move1, &move2);

                move1 = (int)(move1 - 97);
                move2 = (int)(move2 - 97);

                if (player_moves(board, n, B, move1, move2))
                {
                    doMove(board, n, B, move1, move2);
                    printBoard(board, n);
                }
                else if (!player_moves(board, n, B, move1, move2))
                {
                    printf("Invalid move.\n"); // If invalid move does other player automatically win

                    break;
                }
            }

            // PRINTF BOARD AND CHECK FOR WINNER AFTER //
            // printBoard(board, n);
            if (check_full_board(board, n))
            {
                play_game = false;
                // printf("I made it here");
                break; // break out of the loop
            }

            ////////////////////////////////////////////////////////////////////////////////////////////////////////

            //// SECOND PLAYER ////////////////////////////////////////////////////////////////////////////////////

            if (!valid_move_left(board, n, W))
            {
                printf("%c player has no valid move.\n", W);
                // play_game = false;
            }
            else
            {
                // computer move algorithm thing

                int f = makeMove(board, n, W, &max_row, &max_col);
                printf("Computer places %c at %c%c.\n", W, changeLetter(max_row), changeLetter(max_col));
                doMove(board, n, W, max_row, max_col);
                printBoard(board, n);
            }

            // PRINT BOARD AND CHECK FOR WINNER AFTER //
            // printBoard(board, n);
            if (check_full_board(board, n))
            {
                play_game = false;
                break;
            }

            ////////////////////////////////////////////////////////////////////////////////////////////////////////
        }
        else if (computer == 'B')
        {
            ///////////////////////////////// FIRST PLAYER /////////////////////////////////////////////////////////
            if (!valid_move_left(board, n, B))
            {
                printf("%c player has no valid move.\n", B);
                play_game = false;
            }
            else
            {
                // computer move algorithm
                int d = makeMove(board, n, B, &max_row, &max_col);
                printf("Computer places %c at %c%c.\n", B, changeLetter(max_row), changeLetter(max_col));
                doMove(board, n, B, max_row, max_col);
                printBoard(board, n);
            }

            // PRINT BOARD AND CHECK FOR WINNER AFTER //
            // printBoard(board, n);

            if (check_full_board(board, n))
            {
                // printf("here i am");
                play_game = false;
                break;
            }

            //////////////////////////////// SECOND PLAYER /////////////////////////////////////////////////////////////
            if (!valid_move_left(board, n, W))
            {
                printf("%c player has no valid move.\n", W);
                // play_game = false;
            }
            else
            {
                printf("Enter move for colour %c (RowCol): ", W);
                scanf(" %c%c", &move1, &move2);

                move1 = (int)(move1 - 97);
                move2 = (int)(move2 - 97);

                if (player_moves(board, n, W, move1, move2))
                {
                    doMove(board, n, W, move1, move2);
                    printBoard(board, n);
                }
                else if (!player_moves(board, n, W, move1, move2))
                {
                    printf("Invalid move.\n"); // If invalid move does other player automatically win
                    break;
                }
            }

            // PRINT BOARD AND CHECK FOR WINNER AFTER //
            // printBoard(board, n);
            if (check_full_board(board, n))
            {
                play_game = false;
                break;
            }

            /////////////////////////////////////////////////////////////////////////////////////////////////////////////
        }
    }

    char player;

    if (computer == 'W')
    {
        player = 'B';
    }
    else
    {
        player = 'W';
    }

    int comp_count = count_winner(board, n, computer);
    int player_count = count_winner(board, n, player);

    if (comp_count > player_count)
    {
        winner = computer;
        printf("%c player wins.", winner);
    }
    else if (player_count > comp_count)
    {
        winner = player;
        printf("%c player wins.", winner);
    }
    else if (player_count == comp_count)
    {
        printf("Draw!");
    }
    return 0;
}
