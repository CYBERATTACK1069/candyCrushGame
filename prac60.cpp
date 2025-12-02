/*
g++ prac60.cpp -o game -lgdi32 -luser32
start game
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

bool checkTPatterns(int matrix[100][100])
{
	bool isMatch = false;
	int key;
	for (int i = 0; i < rowCols; i++)
	{
		for (int j = 0; j < rowCols; j++)
		{
			if (matrix[i][j] != 32)
			{
				key = matrix[i][j];

				// 1. Down T (Matches user's logic: Stem Down i+1, i+2)
				if ((i >= 0 && i < rowCols - 2 && j >= 1 && j < rowCols - 1) && (matrix[i][j - 1] == key && matrix[i][j + 1] == key && matrix[i + 1][j] == key && matrix[i + 2][j] == key))
				{
					isMatch = true;
					score += 30;
					// Highlight Vertical
					for (int k = 0; k < 3; k++)
					{
						gotoxy(j * 4 + 1, (i + k) * 2 + 1);
						cout << "\033[47m" << " " << colors[key] << key << colors[0] << " " << "\033[0m";
					}
					// Highlight Left
					gotoxy((j - 1) * 4 + 1, i * 2 + 1);
					cout << "\033[47m" << " " << colors[key] << key << colors[0] << " " << "\033[0m";
					// Highlight Right
					gotoxy((j + 1) * 4 + 1, i * 2 + 1);
					cout << "\033[47m" << " " << colors[key] << key << colors[0] << " " << "\033[0m";

					Sleep(500); // Pause so player sees it

					// Clear Gems & Create Bomb
					matrix[i][j] = 7;			 // Center becomes Bomb
					matrix[i + 1][j] = 32; // Clear Stem
					matrix[i + 2][j] = 32; // Clear Stem
					matrix[i][j - 1] = 32; // Clear Left
					matrix[i][j + 1] = 32; // Clear Right
				}

				// 2. Up T (Stem points Up: i-1, i-2)
				else if ((i >= 2 && i < rowCols && j >= 1 && j < rowCols - 1) && (matrix[i][j - 1] == key && matrix[i][j + 1] == key && matrix[i - 1][j] == key && matrix[i - 2][j] == key))
				{
					isMatch = true;
					score += 30;
					// Highlight Vertical (Up)
					for (int k = 0; k < 3; k++)
					{
						gotoxy(j * 4 + 1, (i - k) * 2 + 1);
						cout << "\033[47m" << " " << colors[key] << key << colors[0] << " " << "\033[0m";
					}
					// Highlight Left
					gotoxy((j - 1) * 4 + 1, i * 2 + 1);
					cout << "\033[47m" << " " << colors[key] << key << colors[0] << " " << "\033[0m";
					// Highlight Right
					gotoxy((j + 1) * 4 + 1, i * 2 + 1);
					cout << "\033[47m" << " " << colors[key] << key << colors[0] << " " << "\033[0m";

					Sleep(500);

					// Clear
					matrix[i][j] = 7;
					matrix[i - 1][j] = 32;
					matrix[i - 2][j] = 32;
					matrix[i][j - 1] = 32;
					matrix[i][j + 1] = 32;
				}

				// 3. Left T (Stem points Left: j-1, j-2)
				else if ((i >= 1 && i < rowCols - 1 && j >= 2 && j < rowCols) && (matrix[i - 1][j] == key && matrix[i + 1][j] == key && matrix[i][j - 1] == key && matrix[i][j - 2] == key))
				{
					isMatch = true;
					score += 30;
					// Highlight Horizontal (Left)
					for (int k = 0; k < 3; k++)
					{
						gotoxy((j - k) * 4 + 1, i * 2 + 1);
						cout << "\033[47m" << " " << colors[key] << key << colors[0] << " " << "\033[0m";
					}
					// Highlight Up
					gotoxy(j * 4 + 1, (i - 1) * 2 + 1);
					cout << "\033[47m" << " " << colors[key] << key << colors[0] << " " << "\033[0m";
					// Highlight Down
					gotoxy(j * 4 + 1, (i + 1) * 2 + 1);
					cout << "\033[47m" << " " << colors[key] << key << colors[0] << " " << "\033[0m";

					Sleep(500);

					// Clear
					matrix[i][j] = 7;
					matrix[i - 1][j] = 32;
					matrix[i + 1][j] = 32;
					matrix[i][j - 1] = 32;
					matrix[i][j - 2] = 32;
				}

				// 4. Right T (Stem points Right: j+1, j+2)
				else if ((i >= 1 && i < rowCols - 1 && j >= 0 && j < rowCols - 2) && (matrix[i - 1][j] == key && matrix[i + 1][j] == key && matrix[i][j + 1] == key && matrix[i][j + 2] == key))
				{
					isMatch = true;
					score += 30;
					// Highlight Horizontal (Right)
					for (int k = 0; k < 3; k++)
					{
						gotoxy((j + k) * 4 + 1, i * 2 + 1);
						cout << "\033[47m" << " " << colors[key] << key << colors[0] << " " << "\033[0m";
					}
					// Highlight Up
					gotoxy(j * 4 + 1, (i - 1) * 2 + 1);
					cout << "\033[47m" << " " << colors[key] << key << colors[0] << " " << "\033[0m";
					// Highlight Down
					gotoxy(j * 4 + 1, (i + 1) * 2 + 1);
					cout << "\033[47m" << " " << colors[key] << key << colors[0] << " " << "\033[0m";

					Sleep(500);

					// Clear
					matrix[i][j] = 7;
					matrix[i - 1][j] = 32;
					matrix[i + 1][j] = 32;
					matrix[i][j + 1] = 32;
					matrix[i][j + 2] = 32;
				}
			}
		}
	}
	return isMatch;
}
bool checkLPatterns(int matrix[100][100])
{
	bool isMatch = false;
	int key;
	for (int i = 0; i < rowCols; i++)
	{
		for (int j = 0; j < rowCols; j++)
		{
			if (matrix[i][j] != 32)
			{
				key = matrix[i][j];

				/* Case 1: Down-Right (Corner is Top-Left)
				 * It checks if (i,j) matches the two gems below it (i+1, i+2) AND the two gems to its right (j+1, j+2).  */

				if ((i + 2 < rowCols && j + 2 < rowCols) &&
						(matrix[i + 1][j] == key && matrix[i + 2][j] == key && matrix[i][j + 1] == key && matrix[i][j + 2] == key))
				{
					isMatch = true;
					score += 10;
					// Highlight
					// Vertical
					for (int k = 0; k < 3; k++)
					{
						gotoxy(j * 4 + 1, (i + k) * 2 + 1);
						cout << "\033[47m" << " " << colors[key] << key << colors[0] << " " << "\033[0m";
					}
					// Horizontal
					for (int k = 1; k < 3; k++)
					{
						gotoxy((j + k) * 4 + 1, i * 2 + 1);
						cout << "\033[47m" << " " << colors[key] << key << colors[0] << " " << "\033[0m";
					}
					Sleep(500);
					// Clear
					matrix[i][j] = 6;
					matrix[i + 1][j] = 32;
					matrix[i + 2][j] = 32;
					matrix[i][j + 1] = 32;
					matrix[i][j + 2] = 32;
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

						cout << "\033[47m" << " " << colors[key] << key << colors[0] << " " << "\033[0m";
					}
					// Horizontal
					for (int k = 1; k < 3; k++)
					{
						gotoxy((j - k) * 4 + 1, i * 2 + 1);
						cout << "\033[47m" << " " << colors[key] << key << colors[0] << " " << "\033[0m";
					}
					Sleep(500);
					matrix[i][j] = 6;
					matrix[i + 1][j] = 32;
					matrix[i + 2][j] = 32;
					matrix[i][j - 1] = 32;
					matrix[i][j - 2] = 32;
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
						cout << "\033[47m" << " " << colors[key] << key << colors[0] << " " << "\033[0m";
					} // Horizontal
					for (int k = 1; k < 3; k++)
					{
						gotoxy((j + k) * 4 + 1, i * 2 + 1);
						cout << "\033[47m" << " " << colors[key] << key << colors[0] << " " << "\033[0m";
					}
					Sleep(500);
					matrix[i][j] = 6;
					matrix[i - 1][j] = 32;
					matrix[i - 2][j] = 32;
					matrix[i][j + 1] = 32;
					matrix[i][j + 2] = 32;
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
						cout << "\033[47m" << " " << colors[key] << key << colors[0] << " " << "\033[0m";
					}
					// Horizontal
					for (int k = 1; k < 3; k++)
					{
						gotoxy((j - k) * 4 + 1, i * 2 + 1);
						cout << "\033[47m" << " " << colors[key] << key << colors[0] << " " << "\033[0m";
					}
					Sleep(500);
					matrix[i][j] = 6;
					matrix[i - 1][j] = 32;
					matrix[i - 2][j] = 32;
					matrix[i][j - 1] = 32;
					matrix[i][j - 2] = 32;
				}
			}
		}
	}
	return isMatch;
}

bool checkRowColMatch(int matrix[100][100])
{
	bool isMatch = false;
	if (checkLPatterns(matrix))
	{
		isMatch = true;
	}
	if (checkTPatterns(matrix))
	{
		isMatch = true;
	}

	int key;
	// Check Rows
	for (int i = 0; i < rowCols; i++)
	{
		int currentCount = 1;
		for (int j = 0; j < rowCols - 1; j++)
		{
			if (matrix[i][j] != 32 && matrix[i][j] == matrix[i][j + 1])
			{
				currentCount++;
			}
			else
			{
				if (currentCount >= 3)
				{
					isMatch = true;
					score += (currentCount * 2);
					// Highlight
					for (int k = 0; k < currentCount; k++)
					{
						int c = j - k;
						gotoxy(c * 4 + 1, i * 2 + 1);
						cout << "\033[47m" << " " << colors[matrix[i][c]] << matrix[i][c] << colors[0] << " " << "\033[0m";
					}
					Sleep(500);
					// Clear
					for (int k = 0; k < currentCount; k++)
					{
						int c = j - k;
						if (currentCount >= 4 && k == currentCount - 1)
						{
							matrix[i][c] = 5; // Special gem
							score += 4;
						}
						else
						{
							matrix[i][c] = 32;
						}
					}
				}
				currentCount = 1;
			}
		}
		// Check end of row
		if (currentCount >= 3)
		{
			isMatch = true;
			score += (currentCount * 2);
			for (int k = 0; k < currentCount; k++)
			{
				int c = rowCols - 1 - k;
				gotoxy(c * 4 + 1, i * 2 + 1);
				cout << "\033[47m" << " " << colors[matrix[i][c]] << matrix[i][c] << colors[0] << " " << "\033[0m";
			}
			Sleep(500);
			for (int k = 0; k < currentCount; k++)
			{
				int c = rowCols - 1 - k;
				if (currentCount >= 4 && k == currentCount - 1)
				{
					matrix[i][c] = 5;
					score += 4;
				}
				else
				{
					matrix[i][c] = 32;
				}
			}
		}
	}

	// Check Columns
	for (int j = 0; j < rowCols; j++)
	{
		int colCount = 1;
		for (int i = 0; i < rowCols - 1; i++)
		{
			if (matrix[i][j] != 32 && matrix[i][j] == matrix[i + 1][j])
			{
				colCount++;
			}
			else
			{
				if (colCount >= 3)
				{
					isMatch = true;
					score += (colCount * 2);
					for (int k = 0; k < colCount; k++)
					{
						int r = i - k;
						gotoxy(j * 4 + 1, r * 2 + 1);
						cout << "\033[47m" << " " << colors[matrix[r][j]] << matrix[r][j] << colors[0] << " " << "\033[0m";
					}
					Sleep(500);
					for (int k = 0; k < colCount; k++)
					{
						int r = i - k;
						if (colCount >= 4 && k == colCount - 1)
						{
							matrix[r][j] = 5;
							score += 4;
						}
						else
						{
							matrix[r][j] = 32;
						}
					}
				}
				colCount = 1;
			}
		}
		// Check end of column
		if (colCount >= 3)
		{
			isMatch = true;
			score += (colCount * 2);
			for (int k = 0; k < colCount; k++)
			{
				int r = rowCols - 1 - k;
				gotoxy(j * 4 + 1, r * 2 + 1);
				cout << "\033[47m" << " " << colors[matrix[r][j]] << matrix[r][j] << colors[0] << " " << "\033[0m";
			}
			Sleep(500);
			for (int k = 0; k < colCount; k++)
			{
				int r = rowCols - 1 - k;
				if (colCount >= 4 && k == colCount - 1)
				{
					matrix[r][j] = 5;
					score += 4;
				}
				else
				{
					matrix[r][j] = 32;
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

// void checkFirstRowZeroes(int matrix[100][100])
// {

// 	for (int j = 0; j < rowCols; j++)
// 	{
// 		if (matrix[0][j] == 32)
// 		{
// 			// Sleep(2000);
// 			matrix[0][j] = (rand() % 4) + 1;
// 		}
// 	}
// }

void activateSpecialGem(int matrix[100][100], int r, int c, int val)
{
	int type = matrix[r][c];
	matrix[r][c] = 32; // Remove the special gem itself first

	if (type == 5) // Line Blast (from 4-match)
	{
		score += 20; // Bonus for activating the special gem

		// Highlight entire row to be cleared
		for (int j = 0; j < rowCols; j++)
		{
			if (matrix[r][j] != 32)
			{
				gotoxy(j * 4 + 1, r * 2 + 1);
				cout << "\033[47m" << " " << colors[matrix[r][j]] << matrix[r][j] << colors[0] << " " << "\033[0m";
			}
		}
		for (int i = 0; i < rowCols; i++)
		{
			if (matrix[i][c] != 32)
			{
				gotoxy(c * 4 + 1, i * 2 + 1);
				cout << "\033[47m" << " " << colors[matrix[i][c]] << matrix[i][c] << colors[0] << " " << "\033[0m";
			}
		}
		Sleep(500); // Show highlight for a moment

		// Clear entire row
		for (int j = 0; j < rowCols; j++)
		{
			if (matrix[r][j] != 32) // Only clear if it's not already empty
			{
				// Score for each cleared gem
				matrix[r][j] = 32;
			}
		}

		Sleep(500);
		for (int i = 0; i < rowCols; i++)
		{
			if (matrix[i][c] != 32)
			{
				matrix[i][c] = 32;
			}
		}
	}
	else if (type == 6) // Bomb (from L-match)
	{
		score += 30;
		// Highlight 3x3 area
		for (int i = r - 1; i <= r + 1; i++)
		{
			for (int j = c - 1; j <= c + 1; j++)
			{
				// CORRECT BOUNDARY CHECK: Check i and j
				if (i >= 0 && i < rowCols && j >= 0 && j < rowCols)
				{
					// Skip the center if desired, or just check for non-empty
					if (r == i && c == j)
						continue;

					if (matrix[i][j] != 32)
					{
						gotoxy(j * 4 + 1, i * 2 + 1);
						cout << "\033[47m" << " " << colors[matrix[i][j]] << matrix[i][j] << colors[0] << " " << "\033[0m";
					}
				}
			}
		}

		Sleep(500);

		// Clear 3x3 area
		for (int i = r - 1; i <= r + 1; i++)
		{
			for (int j = c - 1; j <= c + 1; j++)
			{
				if (i >= 0 && i < rowCols && j >= 0 && j < rowCols)
				{
					if (matrix[i][j] != 32)
					{
						matrix[i][j] = 32;
					}
				}
			}
		}
	}
	else if (type == 7)
	{
		for (int i = 0; i < rowCols; i++)
		{
			for (int j = 0; j < rowCols; j++)
			{
				if (matrix[i][j] == val)
				{
					gotoxy(j * 4 + 1, i * 2 + 1);
					cout << "\033[47m" << " " << colors[matrix[i][j]] << matrix[i][j] << colors[0] << " " << "\033[0m";
				}
			}
		}
		Sleep(500);
		for (int i = 0; i < rowCols; i++)
		{
			for (int j = 0; j < rowCols; j++)
			{
				if (matrix[i][j] == val)
				{
					matrix[i][j] = 32;
				}
			}
		}
	}
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

				if (matrix[i][j] == 32)
				{
					cout << "   ";
				}
				else
				{
					cout << " " << colors[matrix[i][j]] << matrix[i][j] << colors[0] << " ";
				}
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

void gravity(int matrix[100][100])
{
	bool moved = true;
	while (moved)
	{
		moved = false;
		// Move gems down
		for (int i = rowCols - 1; i > 0; i--)
		{
			for (int j = 0; j < rowCols; j++)
			{
				if (matrix[i][j] == 32 && matrix[i - 1][j] != 32)
				{
					swapValues(matrix[i][j], matrix[i - 1][j]);
					moved = true;
				}
			}
		}

		// Refill top row
		for (int j = 0; j < rowCols; j++)
		{
			if (matrix[0][j] == 32)
			{
				matrix[0][j] = (rand() % 4) + 1;
				moved = true;
			}
		}

		if (moved)
		{
			gotoxy(0, 0);
			displayTable(matrix);

			gotoxy(40, 1);
			cout << "Moves left : " << userMoves << "   " << endl;

			gotoxy(40, 4);
			cout << "Users Score : " << score << "   " << endl;
			Sleep(200);
		}
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
	// checkRowColMatch(matrix);

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
					gotoxy(0, 0);
					gotoxy(selected_x * 4 + 1, selected_y * 2 + 1);
					cout << "\033[47m" << " " << colors[matrix[selected_y][selected_x]] << matrix[selected_y][selected_x] << colors[0] << " " << "\033[0m";

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
						gotoxy(0, 0);
						// system("cls");
						swapValues(matrix[selected_y][selected_x], matrix[gridY][gridX]);
						displayTable(matrix);

						if (matrix[selected_y][selected_x] == 5 || matrix[selected_y][selected_x] == 6 || matrix[selected_y][selected_x] == 7)
						{
							system("cls");
							gotoxy(0, 0);
							displayTable(matrix);
							gotoxy(0, 0);
							// Special gem is at selected_y, selected_x. The OTHER gem is at gridY, gridX.
							activateSpecialGem(matrix, selected_y, selected_x, matrix[gridY][gridX]);

							gotoxy(0, 0);
							displayTable(matrix);
							gotoxy(0, 0);

							gotoxy(0, 18);
							cout << "Swapped." << endl;
						}
						else if (matrix[gridY][gridX] == 5 || matrix[gridY][gridX] == 6 || matrix[gridY][gridX] == 7)
						{
							system("cls");
							gotoxy(0, 0);
							displayTable(matrix);
							gotoxy(0, 0);
							// Special gem is at gridY, gridX. The OTHER gem is at selected_y, selected_x.
							activateSpecialGem(matrix, gridY, gridX, matrix[selected_y][selected_x]);

							gotoxy(0, 0);
							displayTable(matrix);
							gotoxy(0, 0);

							gotoxy(0, 18);
							cout << "Swapped." << endl;
						}
						else
						{
						}

						if (!checkRowColMatch(matrix))
						{
							swapValues(matrix[gridY][gridX], matrix[selected_y][selected_x]);
							userMoves--;
							// system("cls");
							gotoxy(0, 0);

							displayTable(matrix);
							gotoxy(0, 0);
							gotoxy(0, 18);
							cout << "Invalid! Must be adjacent. Deselected." << endl;
						}
						else
						{
							// displayTable(matrix);
							Sleep(500);
							gotoxy(0, 0);

							displayTable(matrix);
							gotoxy(0, 20);
							cout << "Swapped!" << endl;
							Sleep(1500);

							system("cls");

							gotoxy(0, 0);

							displayTable(matrix);
							gotoxy(0, 20);
							userMoves--;
						}
						// Redraw the whole table to show the swap

						Sleep(1000);
						gravity(matrix);
						gotoxy(0, 0);
						Sleep(1000);

						displayTable(matrix);
						gotoxy(0, 0);
						gotoxy(40, 1);
						cout << "Moves left : " << userMoves << endl;

						gotoxy(0, 0);
						gotoxy(40, 4);
						cout << "Users Score : " << score << endl;

						while ((checkLPatterns(matrix) || checkRowColMatch(matrix)) && userMoves != 0)
						{
							gotoxy(0, 18);
							cout << " ";
							Sleep(5000); // Optional delay to see the cascade

							gotoxy(0, 0);
							displayTable(matrix);
							Sleep(1000);
							gotoxy(0, 0);
							gravity(matrix);

							// userMoves--;
							gotoxy(0, 0);
							gotoxy(40, 1);
							cout << "Moves left : " << userMoves << endl;

							gotoxy(0, 0);
							gotoxy(40, 4);
							cout << "Users Score : " << score << endl;
							if (userMoves == 0)
							{
								exit(0);
								abort();
							}
							// Sleep(10000); // Optional delay to see the cascade
						} // gravity(matrix);
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