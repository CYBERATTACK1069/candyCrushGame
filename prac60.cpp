/*
g++ prac60.cpp -o game -lgdi32 -luser32
game
*/

#include <iostream>
#include "help.h"
#include <windows.h>
#include <cstdlib> // For system("cls")
using namespace std;
int rowCols = 8;
string colors[7] = {
		"\033[37m",			 // White (Bright White)
		"\033[31m",			 // Red
		"\033[33m",			 // Yellow
		"\033[35m",			 // Purple (Magenta)
		"\033[32m",			 // Green
		"\033[34m",			 // Blue
		"\033[38;5;208m" // Orange (Extended ANSI code, or use \033[31m if simple console)
};

string shapes[] = {
		" O ", // White: Circle
		"[#]", // Red: Square
		"<> ", // Yellow: Diamond
		" ^ ", // Purple: Triangle Up
		"[_]", // Green: Rectangle/Gem
		" v ", // Blue: Triangle Down
		"(O)"	 // Orange: Hexagon/Orb
};

void checkRowColMatch(int matrix[100][100])
{
	int key;
	for (int i = 0; i < rowCols; i++)
	{
		int currentCount = 1;
		for (int j = 0; j < rowCols - 1; j++)
		{
			key = matrix[i][j];

			if (matrix[i][j] == matrix[i][j + 1])
			{
				++currentCount;
			}
			else
			{
				if (currentCount >= 3)
				{
					// cout << key << " comes " << currentCount << " times consecutively row : " << i + 1 << endl;
					for (int k = 0; k < currentCount; k++)
					{
						matrix[i][j - k] = 0;
					}
				}
				currentCount = 1;
			}
		}
		// Check if the last group in the row was a match
		if (currentCount >= 3)
		{
			// cout << key << " comes " << currentCount << " times consecutively row : " << i + 1 << " replaced by 0." << endl;
		}
	}
}

int generateRandomNumber(int min, int max)
{
	// This is now only used for the *initial* seed on the first function call.
	int localVariable;

	// 'seed' is now static. It is initialized ONLY ONCE.
	// After the first call, this line is effectively skipped.
	static size_t seed = (size_t)&localVariable;

	// The LCG formula updates the seed. This new value will be retained
	// for the next function call because 'seed' is static.
	seed = (seed * 9301 + 49297);

	// Scale the new seed to the desired range [min, max].
	int finalNumber = (seed % (max - min + 1));

	return finalNumber + min;
}

void genTableValues(int matrix[100][100])
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			while (true)
			{
				int randomNumber = generateRandomNumber(1, 5);
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
	int i = 0;
	for (int j = 0; j < rowCols; j++)
	{
		if (matrix[i][j] == 0)
		{
			matrix[i][j] == generateRandomNumber(1, 5);
		}
	}
}

void gravity(int matrix[100][100])
{
	for (int i = rowCols - 1; i > 0; i--)
	{
		for (int j = 0; j < rowCols; j++)
		{
			if (matrix[i][j] == 0)
			{
				int temp = matrix[i - 1][j];
				matrix[i - 1][j] = matrix[i][j];
				matrix[i][j] = temp;
			}
		}
	}
	// Sleep(1000);
	checkFirstRowZeroes(matrix);
}

void displayTable(int matrix[100][100])
{
	int i = 0;
	while (i < 8)
	{
		// gotoxy(6, 1);
		{

			cout << "---------------------------------";
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
		cout << "---------------------------------";
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
	system("cls"); // Clear the console for consistent output
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

					gotoxy(0, 20);
					cout << "Selected (" << selected_y + 1 << ", " << selected_x + 1 << "). Now pick a neighbor to swap.      " << endl;
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
						int temp = matrix[selected_y][selected_x];
						matrix[selected_y][selected_x] = matrix[gridY][gridX];
						matrix[gridY][gridX] = temp;

						// Redraw the whole table to show the swap
						system("cls");
						checkRowColMatch(matrix);
						gravity(matrix);
						// checkFirstRowZeroes(matrix);
						displayTable(matrix);
						checkRowColMatch(matrix);
						gravity(matrix);

						// checkRowColMatch(matrix);
						gotoxy(0, 20);
						cout << "Swapped!" << endl;
					}
					else
					{
						gotoxy(0, 20);
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
	}

	return 0;
}

/*
moving next what can i do is that simply i have to call the function for same cell matches in a certain row or column how much values are being matched
*/