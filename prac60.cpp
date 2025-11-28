/*
g++ prac60.cpp -o game -lgdi32 -luser32
game
*/

#include <iostream>
#include "help.h"
#include <windows.h>
#include <cstdlib> // For system("cls")
#include <ctime>	 // For time() to seed rand()
using namespace std;
int rowCols = 8;
int userMoves = 20;
int score = 0;
string colors[7] = {
		"\033[37m", // White (Bright White)
		"\033[31m", // Red
		"\033[33m", // Yellow
		"\033[35m", // Purple (Magenta)
		"\033[32m", // Green
		// "\033[34m",				// Blue
		// "\033[38;5;208m", // Orange (Extended ANSI code, or use \03331m if simple console)
};

int swapValues(int &a, int &b)
{
	int temp = a;
	a = b;
	b = temp;
	return true;
}

void checkL(int matrix[100][100]) {}

bool checkLPatterns(int matrix[100][100])
{
	bool isMatch = false;
	int key;
	for (int i = 0; i < rowCols; i++)
	{
		for (int j = 0; j < rowCols; j++)
		{
			if (matrix[i][j] != 0)
			{
				key = matrix[i][j];

				/* Case 1: Down-Right (Corner is Top-Left)
				 * It checks if (i,j) matches the two gems below it (i+1, i+2) AND the two gems to its right (j+1, j+2).  */

				if (i + 2 < rowCols && j + 2 < rowCols &&
						matrix[i + 1][j] == key && matrix[i + 2][j] == key &&
						matrix[i][j + 1] == key && matrix[i][j + 2] == key)
				{
					isMatch = true;
					score += 10;
					// Highlight
					// Vertical
					for (int k = 0; k < 3; k++)
					{
						gotoxy(j * 4 + 1, (i + k) * 2 + 1);
						cout << "\033[47m" << " " << colors[matrix[i + k][j]] << matrix[i + k][j] << colors[0] << " " << "\033[0m";
					}
					// Horizontal
					for (int k = 1; k < 3; k++)
					{
						gotoxy((j + k) * 4 + 1, i * 2 + 1);
						cout << "\033[47m" << " " << colors[matrix[i][j + k]] << matrix[i][j + k] << colors[0] << " " << "\033[0m";
					}
					Sleep(500);
					// Clear
					matrix[i][j] = 5;
					matrix[i + 1][j] = 0;
					matrix[i + 2][j] = 0;
					matrix[i][j + 1] = 0;
					matrix[i][j + 2] = 0;
				}
				// 2. Down-Left (Corner Top-Right)
				else if (i + 2 < rowCols && j - 2 >= 0 &&
								 matrix[i + 1][j] == key && matrix[i + 2][j] == key &&
								 matrix[i][j - 1] == key && matrix[i][j - 2] == key)
				{
					isMatch = true;
					// Vertical
					for (int k = 0; k < 3; k++)
					{
						gotoxy(j * 4 + 1, (i + k) * 2 + 1);
						cout << "\033[47m" << " " << colors[matrix[i + k][j]] << matrix[i + k][j] << colors[0] << " " << "\033[0m";
					}
					// Horizontal
					for (int k = 1; k < 3; k++)
					{
						gotoxy((j - k) * 4 + 1, i * 2 + 1);
						cout << "\033[47m" << " " << colors[matrix[i][j - k]] << matrix[i][j - k] << colors[0] << " " << "\033[0m";
					}
					Sleep(500);
					matrix[i][j] = 5;
					matrix[i + 1][j] = 0;
					matrix[i + 2][j] = 0;
					matrix[i][j - 1] = 0;
					matrix[i][j - 2] = 0;
				}
				// 3. Up-Right (Corner Bottom-Left)
				else if (i - 2 >= 0 && j + 2 < rowCols &&
								 matrix[i - 1][j] == key && matrix[i - 2][j] == key &&
								 matrix[i][j + 1] == key && matrix[i][j + 2] == key)
				{
					isMatch = true;
					// Vertical
					for (int k = 0; k < 3; k++)
					{
						gotoxy(j * 4 + 1, (i - k) * 2 + 1);
						cout << "\033[47m" << " " << colors[matrix[i - k][j]] << matrix[i - k][j] << colors[0] << " " << "\033[0m";
					}
					// Horizontal
					for (int k = 1; k < 3; k++)
					{
						gotoxy((j + k) * 4 + 1, i * 2 + 1);
						cout << "\033[47m" << " " << colors[matrix[i][j + k]] << matrix[i][j + k] << colors[0] << " " << "\033[0m";
					}
					Sleep(500);
					matrix[i][j] = 5;
					matrix[i - 1][j] = 0;
					matrix[i - 2][j] = 0;
					matrix[i][j + 1] = 0;
					matrix[i][j + 2] = 0;
				}
				// 4. Up-Left (Corner Bottom-Right)
				else if (i - 2 >= 0 && j - 2 >= 0 &&
								 matrix[i - 1][j] == key && matrix[i - 2][j] == key &&
								 matrix[i][j - 1] == key && matrix[i][j - 2] == key)
				{
					isMatch = true;
					// Vertical
					for (int k = 0; k < 3; k++)
					{
						gotoxy(j * 4 + 1, (i - k) * 2 + 1);
						cout << "\033[47m" << " " << colors[matrix[i - k][j]] << matrix[i - k][j] << colors[0] << " " << "\033[0m";
					}
					// Horizontal
					for (int k = 1; k < 3; k++)
					{
						gotoxy((j - k) * 4 + 1, i * 2 + 1);
						cout << "\033[47m" << " " << colors[matrix[i][j - k]] << matrix[i][j - k] << colors[0] << " " << "\033[0m";
					}
					Sleep(500);
					matrix[i][j] = 5;
					matrix[i - 1][j] = 0;
					matrix[i - 2][j] = 0;
					matrix[i][j - 1] = 0;
					matrix[i][j - 2] = 0;
				}
			}
		}
	}
	return isMatch;
}

bool checkRowColMatch(int matrix[100][100])
{
	bool isMatch = false;
	int key;
	checkLPatterns(matrix);
	// it is for checking the rows
	for (int i = 0; i < rowCols; i++)
	{
		int currentCount = 1;
		for (int j = 0; j < rowCols - 1; j++)
		{
			key = matrix[i][j];

			if (matrix[i][j] != 0 && matrix[i][j] == matrix[i][j + 1])
			{
				++currentCount;
			}
			else
			{
				if (currentCount >= 3)
				{
					score += 2;
					isMatch = true;

					for (int k = 0; k < currentCount; k++)

					{

						int r = i;

						int c = j - k;

						gotoxy(c * 4 + 1.5, r * 2 + 1);

						cout << "\033[47m" << " " << colors[matrix[r][c]] << matrix[r][c] << colors[0] << " " << "\033[0m";
					}

					Sleep(500);

					for (int k = 0; k < currentCount; k++)
					{
						if (currentCount >= 4 && k == currentCount - 1) // First index of consecutive (j - (currentCount-1))
						{
							score += 4;
							matrix[i][j - k] = 5;
						}
						else
						{
							matrix[i][j - k] = 0;
						}
					}
				}
				currentCount = 1;
			}
		}
		// Check if the last group in the row was a match
		if (currentCount >= 3)
		{
			score += 2;
			isMatch = true;
			for (int k = 0; k < currentCount; k++)
			{
				int r = i;
				int c = rowCols - 1 - k;
				gotoxy(c * 4 + 1, r * 2 + 1);
				cout << "\033[47m" << " " << colors[matrix[r][c]] << matrix[r][c] << colors[0] << " " << "\033[0m";
			}
			Sleep(500);
			for (int k = 0; k < currentCount; k++)
			{
				if (currentCount >= 4 && k == currentCount - 1)
				{
					score += 4;
					matrix[i][rowCols - 1 - k] = 5;
				}
				else
				{
					matrix[i][rowCols - 1 - k] = 0;
				}
			}
		}
	}

	// it is for checking the columns
	for (int j = 0; j < rowCols; j++)
	{
		int colCount = 1;
		for (int i = 0; i < rowCols - 1; i++)
		{
			if (matrix[i][j] != 0 && matrix[i][j] == matrix[i + 1][j])
			{
				colCount++;
			}
			else
			{
				if (colCount >= 3)
				{
					score += 2;
					isMatch = true;
					for (int k = 0; k < colCount; k++)
					{
						int r = i - k;
						int c = j;
						gotoxy(c * 4 + 1, r * 2 + 1);
						cout << "\033[47m" << " " << colors[matrix[r][c]] << matrix[r][c] << colors[0] << " " << "\033[0m";
					}
					Sleep(500);
					for (int k = 0; k < colCount; k++)
					{
						if (colCount >= 4 && k == colCount - 1)
						{
							score += 4;
							matrix[i - k][j] = 5;
						}
						else
						{
							matrix[i - k][j] = 0;
						}
					}
				}
				colCount = 1;
			}
		}
		// Check if the last group in the column was a match
		if (colCount >= 3)
		{
			score += 2;
			isMatch = true;
			for (int k = 0; k < colCount; k++)
			{
				int r = rowCols - 1 - k;
				int c = j;
				gotoxy(c * 4 + 1, r * 2 + 1);
				cout << "\033[47m" << " " << colors[matrix[r][c]] << matrix[r][c] << colors[0] << " " << "\033[0m";
			}
			Sleep(500);
			for (int k = 0; k < colCount; k++)
			{
				if (colCount >= 4 && k == colCount - 1)
				{
					score += 4;
					matrix[rowCols - 1 - k][j] = 5;
				}
				else
				{
					matrix[rowCols - 1 - k][j] = 0;
				}
			}
		}
	}
	return isMatch;
}

void genTableValues(int matrix[100][100])
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			while (true)
			{
				int randomNumber = (rand() % 4) + 1;
				matrix[i][j] = randomNumber;

				// Check for Horizontal Match (Left) or Vertical Match (Up)

				if ((j >= 2 && matrix[i][j] == matrix[i][j - 1] && matrix[i][j] == matrix[i][j - 2]) ||

						(i >= 2 && matrix[i][j] == matrix[i - 1][j] && matrix[i][j] == matrix[i - 2][j]))

				{

					// If it matches either way, try again (continue while loop)

					continue;
				}
				else
				{
					// If no match, we are good to go. Break the while loop and move to next cell.
					break;
				}
			}
		}
	}
}

void checkFirstRowZeroes(int matrix[100][100])
{

	for (int j = 0; j < rowCols; j++)
	{
		if (matrix[0][j] == 0)
		{
			// Sleep(2000);
			matrix[0][j] = (rand() % 4) + 1;
		}
	}
}

void gravity(int matrix[100][100])
{
	bool moved = true;
	while (moved)
	{
		moved = false;
		for (int i = rowCols - 1; i > 0; i--)
		{
			for (int j = 0; j < rowCols; j++)
			{
				if (matrix[i][j] == 0 && matrix[i - 1][j] != 0)
				{
					swapValues(matrix[i][j], matrix[i - 1][j]);
					moved = true;
				}
				// for (int j = 0; j < rowCols; j++)
				// {
				if (matrix[0][j] == 0)
				{
					matrix[0][j] = (rand() % 4) + 1;
					moved = true;
				}
				// }
			}
		}
	}
	checkFirstRowZeroes(matrix);
}

void displayTable(int matrix[100][100])
{
	int i = 0;
	while (i < 8)
	{
		// gotoxy(6, 1);
		{

			cout << "+---+---+---+---+---+---+---+---+";
			cout << endl;
			int j = 0;
			while (j < 8)
			{
				if (j < 8)
				{
					cout << "|";
				}

				cout << " " << colors[matrix[i][j]] << matrix[i][j] << colors[0] << " ";
				// Sleep(100);

				j++;
			}
			if (j == 8)
			{
				cout << "|" << endl;
			}
		}
		i++;
	}
	if (i == 8)
	{
		cout << "+---+---+---+---+---+---+---+---+";
		cout << endl;
	}
}

// Function to move the cursor to a specific grid cell
void moveCursor(int gridX, int gridY)
{
	int x = gridX * 4 + 2;
	int y = gridY * 2 + 1;
	gotoxy(x, y); /* It is used in moveCursor to place the cursor inside the correct "box" of your grid so the user knows which gem they are currently selecting. */
}

int main()
{
	system("cls");		 // Clear the console for consistent output
	srand(time(NULL)); // Seed the random number generator
	int matrix[100][100];
	genTableValues(matrix);
	displayTable(matrix);
	checkRowColMatch(matrix);

	int gridX = 0, gridY = 0;
	moveCursor(gridX, gridY); // Set initial cursor position
	// myLine(100, 50, 100, 300, 255);
	// Variables to track the first selected gem
	bool isSelected = false;
	int selected_x = 0;
	int selected_y = 0;

	int key;
	while (true)
	{
		if (isCursorKeyPressed(key))
		{
			switch (key)
			{
			case 1: // Left
				if (gridX > 0)
					gridX--;
				break;
			case 2: // Up
				if (gridY > 0)
					gridY--;
				break;
			case 3: // Right
				if (gridX < 7)
					gridX++;
				break;
			case 4: // Down
				if (gridY < 7)
					gridY++;
				break;
			case 5: // Enter
				if (!isSelected)
				{
					// 1. First Selection
					selected_x = gridX;
					selected_y = gridY;
					isSelected = true;

					gotoxy(0, 18);
					cout << "Selected (" << selected_y + 1 << ", " << selected_x + 1 << "). Now pick a neighbor to swap.      " << endl;

					gotoxy(0, 0);
					gotoxy(40, 1);
					cout << "Moves left : " << userMoves << endl;

					gotoxy(0, 0);
					gotoxy(40, 4);
					cout << "Users Score : " << score << endl;
				}
				else
				{
					// 2. Second Selection (Swap Attempt)

					// Check if adjacent (distance is exactly 1)
					int dx = abs(gridX - selected_x);
					int dy = abs(gridY - selected_y);

					if (dx + dy == 1)
					{
						// SWAP Logic
						// int temp = matrix[selected_y][selected_x];
						// matrix[selected_y][selected_x] = matrix[gridY][gridX];
						// matrix[gridY][gridX] = temp;

						swapValues(matrix[selected_y][selected_x], matrix[gridY][gridX]);

						if (!checkRowColMatch(matrix))
						{
							swapValues(matrix[gridY][gridX], matrix[selected_y][selected_x]);
							userMoves--;
						}
						else
						{
							swapValues(matrix[selected_y][selected_x], matrix[gridY][gridX]);
							displayTable(matrix);
							gotoxy(0, 20);
							cout << "Swapped!" << endl;
							userMoves--;
						}
						// Redraw the whole table to show the swap
						// Sleep(10000); // Optional delay to see the cascade

						system("cls");
						gravity(matrix);
						displayTable(matrix);
						gotoxy(0, 0);
						gotoxy(40, 1);
						cout << "Moves left : " << userMoves << endl;
						gotoxy(0, 0);
						gotoxy(40, 4);
						cout << "Users Score : " << score << endl;
						// Cascading Loop
						while ((checkLPatterns(matrix) | checkRowColMatch(matrix)) && userMoves != 0)
						{
							Sleep(10000); // Optional delay to see the cascade
							system("cls");

							gravity(matrix);
							displayTable(matrix);
							// userMoves--;
							gotoxy(0, 0);
							gotoxy(40, 1);
							cout << "Moves left : " << userMoves << endl;

							gotoxy(0, 0);
							gotoxy(40, 4);
							cout << "User Score : " << score << endl;
							if (userMoves == 0)
							{
								// exit(0);
								abort();
							}
						}
						// gravity(matrix);
					}
					else
					{
						gotoxy(0, 18);
						cout << "Invalid! Must be adjacent. Deselected." << endl;
					}

					// Reset selection state
					isSelected = false;
				}
				break;
			}
			moveCursor(gridX, gridY); // Move the cursor to the new position
		}

		// Sleep(100); // Add a small delay to prevent high CPU usage
		// checkRowColMatch(matrix);
		gravity(matrix);
		// checkFirstRowZeroes(matrix);
		// displayTable(matrix);
	}

	return 0;
}

/*
moving next what can i do is that simply i have to call the function for same cell matches in a certain row or column how much values are being matched
*/