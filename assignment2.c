//  Program:    tic-tac-toe
//  Purpose:    Coding tic-tac-toe with dynamic 2d array
//  Author:     Akif Artun
//  Date:       09/04/2022

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int** initialize_board(int board_size);
//  Initialize the board with board size
//  Parameters:     board_size - size of the tac-tac-toe board
//  Return:         board with double pointer

void update_board(int marker, int** board, int col, int row);
//  Updates the board with user's move
//  Paramaters:     marker - X for the first user, O for the second user
//                  board - game board with double pointer 
//                  col - column of the input
//                  row - row of the input
//  Return:         nothing(void)

int validate_move(int col, int row, int** board);
//  Checks the move its valid or not
//  Parameters:     col - column of the input
//                  row - row of the input
//                  board - game board with double pointer
//  Return:         1 or 0 (valid or not)

int check_winner(int** board);
//  Checks the winner of the game
//  Parameters:     board - game board with double pointer
//  Return:         1 or 0 (there is winner or not)

void print_state(int** board);
//  Prints the game board
//  Parameters:     board - game board with double pointer
//  Return:         nothing(void)

int size;
char input_file[20];
char marker;
int col;
int row;

int main(int argc, char **argv) {

    if(argc != 3) {
        printf("Format is wrong please enter 3 arguments with './a.out'.\n");
        exit(1);
    }

    char *size_string = argv[1];
    size = atoi(size_string);

    int** game_board = initialize_board(size);
    print_state(game_board);

    strcpy(input_file,argv[2]);

    FILE *fpt;
    fpt = fopen(input_file,"r");

    if (fpt == NULL) {
        printf("The file could not be opened. \n"); 
        exit(1);
    }
    
    char lines[50];

    while (fgets(lines, sizeof(lines), fpt)) {

        marker = lines[4];
        col = lines[2] - '0';
        row = lines[0] - '0';

        if(validate_move(col,row,game_board)) {
            
            if(marker == 'X') {
                printf("First player moves to %d,%d \n",row,col);
            } else {
                printf("Second player moves to %d,%d \n",row,col);
            }

            update_board(marker, game_board, col, row);
            print_state(game_board);
            
        } else {
            printf("Move is not valid!\n");
        }

        if(check_winner(game_board) == 1 && marker == 'X') {
            printf("The winner is the first player \n");
            exit(1);
        } else if(check_winner(game_board) == 1 && marker == 'O') {
            printf("The winner is the second player \n");
            exit(1);
        }
        
    }

    fclose(fpt);

}

int** initialize_board(int board_size) {

    int** table;
    table = (int** )calloc(board_size, sizeof(int*));
    
    for(int i = 0; i < board_size; i++) {
        table[i] = (int* )calloc(board_size, sizeof(int));
    }

    for(int j = 0; j < board_size; j++) {
        for(int k = 0; k < board_size; k++) {
            *(*(table + j) + k ) = '-';
        }
    }

    return table;

}

void print_state(int** board) {
    
    for(int i = 0; i < size; i++) {
        for(int j = 0; j < size; j++) {
            printf("%c\t",*(*(board + i) + j ));
        }
        printf("\n");
    }

}

void update_board(int marker, int** board, int col, int row) {

    *(*(board + row) + col) = marker;

}

int check_winner(int** board) {

    int winner;

    for(int i = 0; i < size; i++) {
        if(*(*(board + i) + 0) == *(*(board + i) + 1) && *(*(board + i) + 1) == *(*(board + i) + 2) && *(*(board + i) + 1) != '-' ) {
            winner = 1;
        }
    }

    for(int j = 0; j < size; j++) {
        if(*(*(board + 0) + j) == *(*(board + 1) + j) && *(*(board + 1) + j) == *(*(board + 2) + j) && *(*(board + 1) + j) != '-' ) {
            winner = 1;
        }
    }

    if(*(*(board + 0) + 0) == *(*(board + 1) + 1) && *(*(board + 1) + 1) == *(*(board + 2) + 2) && *(*(board + 0) + 0) != '-' ) {
        winner = 1;
    } else if(*(*(board + 0) + 2) == *(*(board + 1) + 1) && *(*(board + 1) + 1) == *(*(board + 2) + 0) && *(*(board + 0) + 2) != '-' ) {
        winner = 1;
    }

    return winner;

}

int validate_move(int col, int row, int** board) {

    int isValid = 1;

    if(size <= col || size <= row || *(*(board + row) + col) != '-') {
        isValid = 0;
    }

    return isValid;

}