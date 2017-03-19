/**
 * fifteen.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Implements Game of Fifteen (generalized to d x d).
 *
 * Usage: fifteen d
 *
 * whereby the board's dimensions are to be d x d,
 * where d must be in [DIM_MIN,DIM_MAX]
 *
 * Note that usleep is obsolete, but it offers more granularity than
 * sleep and is simpler to use than nanosleep; `man usleep` for more.
 */
 
#define _XOPEN_SOURCE 500

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// constants
#define DIM_MIN 3
#define DIM_MAX 9

// board
int board[DIM_MAX][DIM_MAX];

// dimensions
int d;

// prototypes
void clear(void);
void greet(void);
void init(void);
void draw(void);
bool move(int tile);
bool won(void);

int main(int argc, string argv[])
{
    // ensure proper usage
    if (argc != 2)
    {
        printf("Usage: fifteen d\n");
        return 1;
    }

    // ensure valid dimensions
    d = atoi(argv[1]);
    if (d < DIM_MIN || d > DIM_MAX)
    {
        printf("Board must be between %i x %i and %i x %i, inclusive.\n",
            DIM_MIN, DIM_MIN, DIM_MAX, DIM_MAX);
        return 2;
    }

    // open log
    FILE* file = fopen("log.txt", "w");
    if (file == NULL)
    {
        return 3;
    }

    // greet user with instructions
    greet();

    // initialize the board
    init();

    // accept moves until game is won
    while (true)
    {
        // clear the screen
        clear();

        // draw the current state of the board
        draw();

        // log the current state of the board (for testing)
        for (int i = 0; i < d; i++)
        {
            for (int j = 0; j < d; j++)
            {
                fprintf(file, "%i", board[i][j]);
                if (j < d - 1)
                {
                    fprintf(file, "|");
                }
            }
            fprintf(file, "\n");
        }
        fflush(file);

        // check for win
        if (won())
        {
            printf("ftw!\n");
            break;
        }

        // prompt for move
        printf("Tile to move: ");
        int tile = GetInt();
        
        // quit if user inputs 0 (for testing)
        if (tile == 0)
        {
            break;
        }

        // log move (for testing)
        fprintf(file, "%i\n", tile);
        fflush(file);

        // move if possible, else report illegality
        if (!move(tile))
        {
            printf("\nIllegal move.\n");
            usleep(500000);
        }

        // sleep thread for animation's sake
        usleep(500000);
    }
    
    // close log
    fclose(file);

    // success
    return 0;
}

/**
 * Clears screen using ANSI escape sequences.
 */
void clear(void)
{
    printf("\033[2J");
    printf("\033[%d;%dH", 0, 0);
}

/**
 * Greets player.
 */
void greet(void)
{
    clear();
    printf("WELCOME TO GAME OF FIFTEEN\n");
    usleep(2000000);
}

/**
 * Initializes the game's board with tiles numbered 1 through d*d - 1
 * (i.e., fills 2D array with values but does not actually print them).  
 */
void init(void)
{   
    //counter = square of dimensions since we're starting from the top. if starting from the bottom (i.e., 0, then counter = 0)
    int counter = (d*d)-1;
    bool odd;
    
    //checking if odd or even
    if((counter % 2) == 1)
    {
        odd = true;   
    }
    for(int i = 0; i < d; i++)
    {
        for(int j = 0; j < d; j++)
        {
            board[i][j] = counter;
            counter--;
        }
    }
    //if odd, switch 1 and 2 in the arrays
    if(odd == true)
    {
        board[d-1][d-2] = 2;
        board[d-1][d-3] = 1;
    }
}

/**
 * Prints the board in its current state.
 */
void draw(void)
{
    for(int i = 0; i < d; i++)
    {
        for(int j = 0; j < d; j++)
        {
            if(board[i][j] >= 10)
            {
                printf("%d ", board[i][j]);   
            }
            else if(board[i][j] < 10)
            {
                printf("%d  ", board[i][j]);
            }
        }
        printf("\n");
    }
}

/**
 * If tile borders empty space, moves tile and returns true, else
 * returns false. 
 */
bool move(int tile)
{
    //initialising positions of tile(positionR and positionC) and the empty space(positionZR, positionZC)
    int positionR, positionC, positionZR, positionZC = 0;
    //searching for current position of tile
    for(int i = 0; i < d; i++)
    {
        for(int j = 0; j < d; j++)
        {
            if(board[i][j] == tile)
            {
                positionR = i;
                positionC = j;
            }
            else if(board[i][j] == 0)
            {
                positionZR = i;
                positionZC = j;
            }
            
        }
    }
    //check whether zero is bordering the tile - better than brute forcing and doesn't make the mistake of going beyond the array like you would if you did it with simple arithmatics.
    if(abs(positionZR-positionR) == 1 && positionZC == positionC)               //abs checks both left and right one position, without the risk of going beyond the array since it extrapolates the values from the array first.
    {
        board[positionZR][positionZC] = tile;
        board[positionR][positionC] = 0;
        return true;
    }
    else if(abs(positionZC-positionC) == 1 && positionZR == positionR)
    {
        board[positionZR][positionZC] = tile;
        board[positionR][positionC] = 0;   
        return true;
    }
    return false;
}

/**
 * Returns true if game is won (i.e., board is in winning configuration), 
 * else false.
 */
bool won(void)
{
    int condition = 1;
    for(int i = 0; i < d; i++)
    {
        for(int j = 0; j < d; j++)
        {
            if(condition > (d*d)-1)
            {
            return true;   
            }
            else if(board[i][j] != condition)
            {
                return false;
            }
            else if(board[i][j] == condition)
            {
                condition++;
            }
        }
    }
    return true;
    
}