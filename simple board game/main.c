#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

void initialize (char board[][26], int n);
void printBoard (char board[][26], int n);
char oppositeColor(char color);
bool compMove (char board[][26], int n, char compColor);
void playerMove (char board[][26], int n, char playerColor);
bool positionInBounds (char board[][26], int n, char row, char col);
bool checkLegalInDirection (char board[][26], int n, char row, char col, char color, int deltaRow, int deltaCol);
void loopDirections (char board[][26], int n, char row, char col, char color);
void changeColor (char board[][26], int n, char row, char col, char color, int deltaRow, int deltaCol);
int highestScore (char board[][26], int n, char color);
int calculateScore(char board[][26], int n, int row, int col, char color, char playerColor, int deltaRow, int deltaCol);
void winColor(char board[][26], int n);

int main (void){
    int n;
    char comp, player;
    char board[26][26];
    
    printf("Enter the board dimension: ");
    scanf("%d", &n);
    printf("Computer plays (B/W): ");
    scanf(" %c", &comp);
    player = oppositeColor(comp);
    initialize (board, n);
    printBoard (board, n);
    
    if (player == 'B')
        playerMove(board, n, player);
    
    while(true){
            bool move = compMove (board, n, comp);
            playerMove (board, n , player);
        if (move == false && highestScore(board, n, player) == 0)
            winColor(board, n);
        }
    
    return 0;
}

void initialize (char board[][26], int n){
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            board[i][j] = 'U';
    
    board[n/2-1][n/2-1] = board[n/2][n/2] = 'W';
    board[n/2-1][n/2] = board[n/2][n/2-1] = 'B';
}

void printBoard (char board[][26], int n){
    char colLabel, rowLabel;
    printf("  ");
    
    for (int k = 0; k < n; k++){
        colLabel = 'a' + k;
        printf("%c", colLabel);
    }
    printf("\n");
    
    for (int i = 0; i < n; i++){
        rowLabel = 'a' + i;
        printf("%c ", rowLabel);
        
        for (int j = 0; j < n; j++)
            printf("%c", board[i][j]);
        printf("\n");
    }
}

char oppositeColor(char color){
    if (color == 'B')
        return 'W';
    else
        return 'B';
}

int highestScore (char board[][26], int n, char color){
    char opposite = oppositeColor(color);
    int score1 = 0, score2 = 0;
    for (int i = n-1; i >= 0; i--)
        for (int j = n-1; j >= 0; j--)
            if (board[i][j] == 'U'){
                score2 = calculateScore(board, n, i, j, color, opposite, 1, 1) + calculateScore(board, n, i, j, color, opposite, 1, 0)+calculateScore(board, n, i, j, color, opposite, 1, -1) + calculateScore(board, n, i, j, color, opposite, 0, 1) + calculateScore(board, n, i, j, color, opposite, 0, -1) + calculateScore(board, n, i, j, color, opposite, -1, 1) + calculateScore(board, n, i, j, color, opposite, -1, -1) + calculateScore(board, n, i, j, color, opposite, -1, 0);
                if (score2 >= score1)
                    score1 = score2;
            }
    return score1;

}

bool compMove (char board[][26], int n, char compColor){
    char row = 0, col = 0, playerColor = oppositeColor(compColor);
    int score1 = 0, score2 = 0;
    score1 = score2 = 0;
    for (int i = n-1; i >= 0; i--)
        for (int j = n-1; j >= 0; j--)
            if (board[i][j] == 'U'){
                score2 = calculateScore(board, n, i, j, compColor, playerColor, 1, 1) + calculateScore(board, n, i, j, compColor,playerColor, 1, 0)+calculateScore(board, n, i, j, compColor, playerColor, 1, -1) + calculateScore(board, n, i, j, compColor, playerColor, 0, 1) + calculateScore(board, n, i, j, compColor, playerColor, 0, -1) + calculateScore(board, n, i, j, compColor, playerColor, -1, 1) + calculateScore(board, n, i, j, compColor,playerColor, -1, -1) + calculateScore(board, n, i, j, compColor, playerColor, -1, 0);
                if (score2 >= score1){
                    row = i+'a';
                    col = j+'a';
                    score1 = score2;
                }
            }
    if (score1! = 0){
        printf("Computer places %c at %c%c.\n", compColor, row, col);
        loopDirections(board, n, row, col, compColor);
        printBoard(board, n);
        return true;
    }
    else{
        printf("%c player has no valid move.\n", compColor);
        return false;
    }
}

void playerMove (char board[][26], int n, char playerColor){
    char row, col;
    printf("Enter move for colour %c (RowCol): ", playerColor);
    scanf(" %c%c",&row, &col);
    loopDirections(board, n, row, col, playerColor);
    printBoard(board, n);
}

bool positionInBounds (char board[][26], int n, char row, char col){
    bool inBounds = false;
    if (row >= 'a' && row < 'a' + n)
        if (col >= 'a' && col < 'a' + n)
            inBounds = true;
    return inBounds;
}

void loopDirections (char board[][26], int n, char row, char col, char color){
    bool check = false;
    if(row-'a' != 0)
        if(checkLegalInDirection(board, n, row, col, color, -1, 0)){
            changeColor(board, n, row, col, color, -1, 0);
            check = true;
        }
    
    if(col-'a'! = 0)
        if(checkLegalInDirection(board, n, row, col, color, 0, -1)){
            changeColor(board, n, row, col, color, 0, -1);
            check = true;
        }
    
    if(row - 'a' != n - 1)
        if(checkLegalInDirection(board, n, row, col, color, 1, 0)){
            changeColor(board, n,r ow,co l, color, 1, 0);
            check = true;
        }
    
    if(col - 'a'! = n - 1)
        if(checkLegalInDirection(board, n, row, col, color, 0, 1)){
            changeColor(board ,n, row,c ol, color,0 , 1);
            check=true;
        }
    
    if(row - 'a'!= 0 && col-'a'!= 0)
        if(checkLegalInDirection(board, n, row, col, color, -1, -1)){
            changeColor(board, n, row, col, color, -1, -1);
            check = true;
        }
    
    if(row - 'a'!= 0 && col - 'a'!= n - 1)
        if(checkLegalInDirection(board, n, row, col, color, -1, 1)){
            changeColor(board, n, row, col, color, -1, 1);
            check = true;
        }
    
    if(row - 'a'!= n - 1 && col - 'a'!= 0)
        if(checkLegalInDirection(board, n, row, col, color, 1, -1)){
            changeColor(board, n, row, col, color, 1, -1);
            check = true;
        }
    
    if(row - 'a' != n-1 && col -'a'!= n - 1)
        if(checkLegalInDirection(board, n, row, col, color, 1, 1)){
            changeColor(board, n, row, col, color, 1, 1);
            check = true;
        }
    
    if (check == false){
        printf("Invalid move.\n");
        printf("%c player wins.", oppositeColor(color));
        exit(0);
    }
}

bool checkLegalInDirection (char board[][26], int n, char row, char col, char color, int deltaRow, int deltaCol){
    bool check = false;
    if (board[row - 'a' + deltaRow][col - 'a' + deltaCol] != color && board[row - 'a' + deltaRow][col - 'a' + deltaCol] != 'U'){
        while (positionInBounds(board, n, row, col) && check == false){
            row = row + (deltaRow);
            col = col + (deltaCol);
            if (board[row - 'a'][col - 'a'] == color)
                check = true;
            if (board[row - 'a'][col - 'a'] == 'U')
                return check;
        }
    }
    return check;
}

void changeColor (char board[][26], int n, char row, char col, char color, int deltaRow, int deltaCol){
    board[row - 'a'][col - 'a'] = color;
    while (positionInBounds(board, n, row, col)){
        row = row + (deltaRow);
        col = col + (deltaCol);
        if (board[row-'a'][col-'a'] != color)
            board[row-'a'][col-'a'] = color;
        else
            return;
    }
}

int calculateScore(char board[][26], int n, int row, int col, char compColor, char playerColor, int deltaRow, int deltaCol){
    int score = 0;
    row = row + deltaRow;
    col = col + deltaCol;
    while (positionInBounds(board, n, row + 'a', col + 'a') && board[row][col] == playerColor){
        score++;
        row = row + deltaRow;
        col = col + deltaCol;
        if (board[row][col] == 'U')
            return 0;
    }
    if (positionInBounds(board, n, row + 'a', col + 'a') == false)
        return 0;
    return score;
}

void winColor(char board[][26], int n){
    int scoreW = 0, scoreB = 0;
    
    for (int i = n-1; i >= 0; i--)
        for (int j = n-1; j >= 0; j--){
            if (board[i][j] == 'W')
                scoreW++;
            else if(board[i][j] == 'B')
                scoreB++;
        }
    
    if (scoreW > scoreB)
        printf("W player wins.");
    else if (scoreB > scoreW)
        printf("B player wins.");
    else
        printf("Draw!");
    
    exit(0);
}
