/*
 * connect.c
 *
 *  Created on: Sep 17, 2023
 *      Author: anirudhjai
 */

#include <stdio.h>
#include <string.h>

#define row 6
#define column 7

typedef struct{
	char name[25];
	char color;
} Player;

Player* switchPlayer(Player* currentPlayer, Player* player1, Player* player2){
	if(strcmp(currentPlayer->name, player1->name) == 0){  //Firs ttime using, used == to compare but it wasn't working.
		return player2;
	} else return player1;
}

void iBoard(char board[][column]) {
    for(int i = 0; i < row; i++) {
        for(int j = 0; j < column; j++) { // Make empty board
            board[i][j] = ' ';
        }
    }
}
void dispBoard(char Board[row][column]){
	for (int i = 0; i < row; i++) {
		        for (int j = 0; j < column; j++) { // display board and any tokens
		            printf("|%c", Board[i][j]);
		        }
		        printf("|\n");
		    }
	printf("---------------\n");
}

int checkDraw(char board[row][column]){
	int check = 0;
	for(int i = 0; i < column; i++){
		if(board[0][i] == ' '){
			return 0;
		}
	}
	return 1;
}

void game(Player* player1, Player* player2, int* tokensToWin){
	printf("Enter name for player1: ");
	scanf("%s", player1->name);				//initialize players and which version of game to play
	player1->color = 'R';

	printf("Enter name for player2: ");
	scanf("%s", player2->name);
	player2->color = 'Y';

	printf("How many tokens are needed to win (3, 4, 5)? ");
	scanf("%d", tokensToWin);
	while (*tokensToWin < 3 || *tokensToWin > 5) {
	    printf("Invalid choice. Please enter 3, 4, or 5: ");
	    scanf("%d", tokensToWin);
	}
}


void move(Player* currentPlayer, char board[row][column]){
	int valid = 0;
	int Column = 0;
	while(!valid){
		printf("%s to play. Pick a column (1-7): ", currentPlayer->name);

		scanf("%d", &Column);
		Column--;

		if(Column >= 0 && Column < column){
			if(board[0][Column] == ' '){
				for(int i = row-1; i>= 0; i--){
					if(board[i][Column] == ' '){ //function for player move
							board[i][Column] = currentPlayer->color;
							valid = 1;
							break;
					}
				}
			} else {
				printf("Column is full. Try again.\n");
			}
		} else {
			printf("Invalid column. Choose between 1 and 7.\n");
		}
	}

}
int check(char board[row][column], int startX, int startY, int stepX, int stepY, char token, int tokensToWin) {
    int count = 0;
    for (int i = 0; i < tokensToWin; i++) {
        if (startX < 0 || startX >= row || startY < 0 || startY >= column || board[startX][startY] != token) {
            return 0;
        }
        count++;
        startX += stepX; // helper for checkWin to check all instances.
        startY += stepY;
    }
    return count == tokensToWin;
}

int checkWin(char board[row][column], int tokensToWin) {
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < column; j++) {
            char current = board[i][j];
            if (current == ' ') continue;

            if (check(board, i, j, 0, 1, current, tokensToWin) ||  // Horizontal
                check(board, i, j, 1, 0, current, tokensToWin) ||  // Vertical
                check(board, i, j, 1, 1, current, tokensToWin) ||  // Diagonal (top-left to bottom-right)
                check(board, i, j, 1, -1, current, tokensToWin)) { // Diagonal (top-right to bottom-left)
                return 1;
            }
        }
    }
    return 0;
}




int main(){

	char board[row][column];
	Player player1, player2;
	Player* currentPlayer;
	int tokensToWin;
	int win;
	int draw;

	game(&player1, &player2, &tokensToWin);

	iBoard(board);
	int game = 1;
	while(game == 1){
		iBoard(board);

		currentPlayer = &player1;
		win = 0;
		draw = 0;
		dispBoard(board);
		while(win == 0 && draw == 0){

			move(currentPlayer, board);
			dispBoard(board);

			win = checkWin(board, tokensToWin);
			draw = checkDraw(board);
			if(win == 1 || draw == 1){
				break;
			}

			currentPlayer = switchPlayer(currentPlayer, &player1, &player2);

		}

		dispBoard(board);
		if(win == 1){
			printf("%s has won!\n", currentPlayer->name);
		} else if (draw == 1){
			printf("The game is a draw!\n");
		}

		 printf("Do you want to play again? (1 for Yes, 0 for No): ");
		 scanf("%d", &game);
	}

	return 0;




}

