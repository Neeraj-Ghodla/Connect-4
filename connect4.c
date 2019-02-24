/* ENGGEN131 Project - C Project - 2018 */
/* Connect Four */
#include "connect4.h"

/*
Author: Neeraj Ghodla
UserID: 489997898
UPI	  : ngho235
*/

// Helper Functions

// Swaps the value of two elements
void Swap(double *element1ptr, double *element2ptr)
{
	double temp = *element1ptr;
	*element1ptr = *element2ptr;
	*element2ptr = temp;
}

// Sorts the array
void BubbleSort(double *array, int size)
{
	for (int pass = 0; pass < size - 1; pass++) {
		for (int counter = 0; counter < size - 1; counter++) {
			if (array[counter] > array[counter + 1]) {
				Swap(&array[counter], &array[counter + 1]);
			}
		}
	}
}

// Raises a number to a power
int power(int base, int exp) {

	int ans = base;

	if (exp == 0) {
		return 1;
	}
	else if (exp == 1) {
		return ans;
	}
	else {
		for (int i = 0; i < exp - 1; i++) {
			ans *= base;
		}
		return ans;
	}
}

// Checks for a 4 in a row, col, and diagonal
int WinningFour(int board[MAX_SIZE][MAX_SIZE], int size, int player, int lastRow, int lastCol)
{
	int counter1 = 1, trueCheck1 = 1;
	int counter2 = 1, trueCheck2 = 1;
	int counter3 = 1, trueCheck3 = 1;
	int counter4 = 1, trueCheck4 = 1;

	// Checking for a 4 in a col
	for (int i = 1; i < 4; i++) {
		// Checking up
		if (trueCheck1 == 1 && lastRow - i >= 0 && board[lastRow - i][lastCol] == player/* && board[lastRow][lastCol] == player*/) {
			counter1++;
		}
		else {
			trueCheck1 = 0;
		}

		// Checking down
		if (trueCheck2 == 1 && lastRow + i < size && board[lastRow + i][lastCol] == player/* && board[lastRow][lastCol] == player*/) {
			counter2++;
		}
		else {
			trueCheck2 = 0;
		}
	}

	// Checking if player won
	if (counter1 == 4 || counter2 == 4 || counter1 + counter2 > 4) {
		return player;
	}
	// Setting variables back to 1
	else {
		counter1 = 1;
		counter2 = 1;
		trueCheck1 = 1;
		trueCheck2 = 1;
	}

	// Checking for a 4 in a row
	for (int i = 1; i < 4; i++) {
		// Checking left
		if (trueCheck1 == 1 && lastCol - i >= 0 && board[lastRow][lastCol - i] == player/* && board[lastRow][lastCol] == player*/) {
			counter1++;
		}
		else {
			trueCheck1 = 0;
		}

		// Checking right
		if (trueCheck2 == 1 && lastCol + i < size && board[lastRow][lastCol + i] == player/* && board[lastRow][lastCol] == player*/) {
			counter2++;
		}
		else {
			trueCheck2 = 0;
		}
	}
	// Checking if player won
	if (counter1 == 4 || counter2 == 4 || counter1 + counter2 > 4) {
		return player;
	}
	// Setting variables back to 1
	else {
		counter1 = 1;
		counter2 = 1;
		trueCheck1 = 1;
		trueCheck2 = 1;
	}

	// Checking for a 4 in a diagonal
	for (int i = 1; i < 4; i++) {
		// Checking Top Right
		if (trueCheck1 == 1 && lastRow - i >= 0 && lastCol  + i < size && board[lastRow - i][lastCol + i]  == player/* && board[lastRow][lastCol] == player*/) {
			counter1++;
		}
		else {
			trueCheck1 = 0;
		}

		// Checking Top Left
		if (trueCheck2 == 1 && lastRow - i >= 0 && lastCol - i >= 0 && board[lastRow - i][lastCol - i] == player/* && board[lastRow][lastCol] == player*/) {
			counter2++;
		}
		else {
			trueCheck2 = 0;
		}

		// Checking Bottom Right
		if (trueCheck3 == 1 && lastRow + i < size && lastCol + i < size && board[lastRow + i][lastCol + i] == player/* && board[lastRow][lastCol] == player*/) {
			counter3++;
		}
		else {
			trueCheck3= 0;
		}

		// Checking Bottom Left
		if (trueCheck4 == 1 && lastRow + i < size && lastCol - i >= 0 && board[lastRow + i][lastCol - i] == player/* && board[lastRow][lastCol] == player*/) {
			counter4++;
		}
		else {
			trueCheck4 = 0;
		}
	}
	// Checking if player won
	if (counter1 == 4 || counter2 == 4 || counter3 == 4 || counter4 == 4 || counter1 + counter4 > 4 || counter2 + counter3 > 4) {
		return player;
	}

	return 0;
}

// Moves the value in an array 1 index back
void MoveBack(char *name, int index)
{
	while (name[index] != '\0') {
		name[index] = name[index + 1];
		index++;
	}
}

// Checks for the next winning move
int WinningMove(int board[MAX_SIZE][MAX_SIZE], int size, char *side, int *move, int player)
{
	int lastRow, lastCol;
	char dir;

	// Add a temporary token to see if the player wins
	for (int x = 0; x < 4; x++) {
		for (int pos = 0; pos < size; pos++) {

			// Assigning x to a direction
			if (x == 0) {
				dir = 'N';
			}
			else if (x == 1) {
				dir = 'E';
			}
			else if (x == 2) {
				dir = 'S';
			}
			else {
				dir = 'W';
			}
			
			// Adding the temporary token
			AddMoveToBoard(board, size, dir, pos, player, &lastRow, &lastCol);

			// If the temporary token is not placed at a invalid position
			if (lastRow != -1 || lastCol != -1) {

				// If the temporary causes a 4 in a row
				if (WinningFour(board, size, player, lastRow, lastCol) == player) {

					// Reset the temporary token and set the side and move to current dir and pos
					board[lastRow][lastCol] = 0;
					*side = dir;
					*move = pos;
					return 1;
				}
				// Reset the temporary token
				else {
					board[lastRow][lastCol] = 0;
				}
			}
		}
	}
	return 0;
}


// Required Functions

int SecondPlacePrize(int prize1, int prize2, int prize3)
{
	// Putting the prizes in an array so they can be sorted
	double prizeMoney[3];
	prizeMoney[0] = prize1;
	prizeMoney[1] = prize2;
	prizeMoney[2] = prize3;

	// Sorting the prizes
	BubbleSort(prizeMoney, 3);

	return (int)prizeMoney[1];
}

int FourInARow(int values[], int length)
{
	int counter = 1;

	for (int i = 0; i < length - 1; i++) {
		if (values[i] == values[i + 1]) {
			counter++;
			if (counter == 4) {
				return (i - 2);
			}
		}
		else {
			counter = 1;
		}
	}

	return -1;
}

int BinaryToDecimal(int binary)
{
	int quotient = binary / 10;;
	int decimal = 0;
	int i = 0;

	// If the value is just 1 digit long
	if (quotient == 0) {
		decimal += power(2, i)*(binary % 10);
		return decimal;
	}
	else {
		while (quotient != 0) {
			quotient = binary / 10;
			decimal += power(2, i)*(binary % 10);
			binary = quotient;
			i++;
		}
		return decimal;
	}
}

double MedianAbility(double abilities[], int length)
{
	// Passing the array to the sorting function
	BubbleSort(abilities, length);

	// Even number of values
	if (length % 2 == 0) {
		return (abilities[length / 2 - 1] + abilities[length / 2]) / 2;
	}

	// Odd number of values
	else {
		return abilities[length / 2];
	}
}

void RemoveSpaces(char *name)
{
	int i = 0;

	// Moving the element 1 index back whenever 2 continuous spaces are encountered
	for (int j = 0; j < (int)strlen(name); j++) {
		while (name[i] != '\0') {
			if (name[i] == ' ' && name[i + 1] == ' ') {
				MoveBack(name, i);
			}
			i++;
		}
		i = 0;
	}
}

void InitialiseBoard(int board[MAX_SIZE][MAX_SIZE], int size)
{
	// Settin all the values to 0
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			board[i][j] = 0;
		}
	}

	// Putting the center # if the board is even sized
	if (size % 2 == 0) {
		board[size / 2][size / 2] = 3;
		board[size / 2 - 1][size / 2] = 3;
		board[size / 2][size / 2 - 1] = 3;
		board[size / 2 - 1][size / 2 - 1] = 3;

	}

	// Putting the center # if the board is odd sized
	else {
		board[size / 2][size / 2] = 3;
	}
}

void AddMoveToBoard(int board[MAX_SIZE][MAX_SIZE], int size, char side, int move, int player, int *lastRow, int *lastCol)
{
	int row, col;

	switch (side) {
		// Releasing the token from the west direction
		case 'W':
			col = 0;
			if (board[move][col] > 0) {
				*lastRow = -1;
				*lastCol = -1;
			}
			else {
				while (board[move][col] == 0 && col <= size - 1) {
					col++;
				}
				board[move][col - 1] = player;
				*lastRow = move;
				*lastCol = col - 1;
			}
			break;
		// Releasing the token from the east direction
		case 'E':
			col = size - 1;
			if (board[move][col] > 0) {
				*lastRow = -1;
				*lastCol = -1;
			}
			else {
				while (board[move][col] == 0 && col >= 0) {
					col--;
				}
				board[move][col + 1] = player;
				*lastRow = move;
				*lastCol = col + 1;
			}
			break;
		// Releasing the token from the north direction
		case 'N':
			row = 0;
			if (board[row][move] > 0 ) {
				*lastRow = -1;
				*lastCol = -1;
			}
			else {
				while (board[row][move] == 0 && row <= size - 1) {
					row++;
				}
				board[row - 1][move] = player;
				*lastRow = row - 1;
				*lastCol = move;
			}
			break;
		// Releasing the token from the south direction
		case 'S':
			row = size - 1;
			if (board[row][move] > 0) {
				*lastRow = -1;
				*lastCol = -1;
			}
			else {
				while (board[row][move] == 0 && row >= 0) {
					row--;
				}
				board[row + 1][move] = player;
				*lastRow = row + 1;
				*lastCol = move;
			}
		}
}

int CheckGameOver(int board[MAX_SIZE][MAX_SIZE], int size, int player, int row, int col)
{
	int counter = 0;

	// Checking if the last move was a poor move
	if (row == -1 || col == -1) {
		return 0;
	}
	else {
		// Check how many positions available in the board
		for (int i = 0; i < size; i++) {
			// Top edge
			if (board[0][i] != 0) {
				counter++;
			}
			// Left edge
			if (board[i+1][0] != 0 && i < size - 2) {
				counter++;
			}
			// Right edge
			if (board[i + 1][size - 1] != 0 && i < size - 2) {
				counter++;
			}
			// Bottom edge
			if (board[size - 1][i] != 0) {
				counter++;
			}
		}

		// If no position available return the player
		if (counter == size * 4 - 4) {
			return 3 - player;
		}

		// Check for a 4 in a row match
		else {
			// If there is a four in a row
			if (WinningFour(board, size, player, row, col) == player) {
				return player;
			}
			else {
				return 0;
			}
		}
	}
}

void GetDisplayBoardString(int board[MAX_SIZE][MAX_SIZE], int size, char *boardString)
{
	char pos = '0';
	int nextLine;
	int index;
	int lastLine;

	// Storing the first 2 lines of the board in the boardString
	for (index = 0; index < size + 5; index++) {
		if (index < 2) {
			boardString[index] = '-';
			boardString[index + size + 5] = '-';
		}
		else if (index >= 2 && index <= 1 + size) {
			boardString[index] = 'N';
			boardString[index + size + 5] = pos;
			pos++;
		}
		else if (index > 1 + size && index < size + 4){
			boardString[index] = '-';
			boardString[index + size + 5] = '-';
		}
		else {
			boardString[index] = '\n';
			boardString[index + size + 5] = '\n';
		}
	}

	nextLine = index + size + 5;

	// Set pos to 0 again
	pos = '0';

	// Storing the vertical direction and position lines in the boardString
	for (nextLine; nextLine < (size + 5) * (size + 2); nextLine+= (size + 5)) {
		boardString[nextLine] = 'W';
		boardString[nextLine + 1] = pos;
		boardString[nextLine + 2 + size] = pos;
		boardString[nextLine + 3 + size] = 'E';
		boardString[nextLine + 4 + size] = '\n';
		index = nextLine + 5 + size;
		pos++;
	}

	// Index of the last line
	lastLine = index;

	// Setting pos to 0 again
	pos = '0';

	// Storing the bottom 2 lines in the boardString
	for (index; index < lastLine + size + 5; index++) {
		if (index < lastLine + 2) {
			boardString[index] = '-';
			boardString[index + size + 5] = '-';
		}
		else if (index >= lastLine + 2 && index <= lastLine + 1 + size) {
			boardString[index] = pos;
			boardString[index + size + 5] = 'S';
			pos++;
		}
		else if (index > lastLine + 1 + size && index < lastLine + size + 4) {
			boardString[index] = '-';
			boardString[index + size + 5] = '-';
		}
		else {
			boardString[index] = '\n';
		}

	}
	
	// Storing the newline and end of the string character
	boardString[index + size + 4] = '\n';
 	boardString[index + size + 5] = '\0';

	// startIndex the starting index of the board data in the boardString
	int startIndex = (5 + size) * 2 + 2;

	// Factor by which the index is increasing for each line
	int factor = 2;

	// Set index to startIndex
	index = startIndex;

	// Storing the actual board data in the boardString
	for (int row = 0; row < size; row++) {
		for (int col = 0; col < size; col++) {
			if (board[row][col] == 0) {
				boardString[index] = '.';
			}
			else if (board[row][col] == 1) {
				boardString[index] = 'X';
			}
			else if (board[row][col] == 2) {
				boardString[index] = 'O';
			}
			else {
				boardString[index] = '#';
			}
			index++;
		}
		factor++;

		index = (5 + size) * factor + 2;
	}
}

void GetMoveBot1(int board[MAX_SIZE][MAX_SIZE], int size, int player, char *side, int *move)
{
	// Check if bot has a winning move
	if (WinningMove(board, size, side, move, player) == 1) {
		return;
	}
	// Check if opponent has a winning move
	else if (WinningMove(board, size, side, move, 3 - player) == 1) {
		return;
	}
	else {
		// If the bot doesn't have a winning move then select a random direction and position
		int i = rand() % 4;

		if (i == 0) {
			*side = 'W';
		}
		else if (i == 1) {
			*side = 'E';
		}
		else if (i == 2) {
			*side = 'N';
		}
		else {
			*side = 'S';
		}

		*move = rand() % size;
	}

	// Check if the position has already been visited
	if (*side == 'W' && (board[*move][0] == player || board[*move][0] == 3 - player)) {
		GetMoveBot1(board, size, player, side, move);
	}
	else if (*side == 'E' && (board[*move][size - 1] == player || board[*move][size - 1] == 3 - player)) {
		GetMoveBot1(board, size, player, side, move);
	}
	else if (*side == 'N' && (board[0][*move] == player || board[0][*move] == 3 - player)) {
		GetMoveBot1(board, size, player, side, move);
	}
	else if (*side == 'S' && (board[size - 1][*move] == player || board[size - 1][*move] == 3 - player)) {
		GetMoveBot1(board, size, player, side, move);
	}
}

void GetMoveBot2(int board[MAX_SIZE][MAX_SIZE], int size, int player, char *side, int *move)
{

	GetMoveBot1(board, size, player, side, move);
	// int i = rand() % 4;

	// if (i == 0) {
	// 	*side = 'W';
	// }
	// else if (i == 1) {
	// 	*side = 'E';
	// }
	// else if (i == 2) {
	// 	*side = 'N';
	// }
	// else {
	// 	*side = 'S';
	// }

	// *move = rand() % size;

	// // If the move is invalid then call the function again
	// if (*side == 'W' && (board[*move][0] == player || board[*move][0] == 3 - player)) {
	// 	GetMoveBot2(board, size, player, side, move);
	// }
	// else if (*side == 'E' && (board[*move][size - 1] == player || board[*move][size - 1] == 3 - player)) {
	// 	GetMoveBot2(board, size, player, side, move);
	// }
	// else if (*side == 'N' && (board[0][*move] == player || board[0][*move] == 3 - player)) {
	// 	GetMoveBot2(board, size, player, side, move);
	// }
	// else if (*side == 'S' && (board[size - 1][*move] == player || board[size - 1][*move] == 3 - player)) {
	// 	GetMoveBot2(board, size, player, side, move);
	// }
}