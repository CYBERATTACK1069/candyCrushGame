/*
g++ candyCrushGame.cpp -o game -lgdi32 -luser32

start game
*/

#include <iostream>
#include "help.h"
#include <windows.h>
#include <cstdlib>
#include <ctime>
#include <cmath>

using namespace std;

int rowCols = 8;
int userMoves = 20;
int score = 0;

const int CELL_SIZE = 60;
const int BOARD_OFFSET_X = 50;
const int BOARD_OFFSET_Y = 50;

// --- GDI SHAPE FUNCTIONS (Small Sizes & Good Colors) ---

void drawGem1_Circle(int x1, int y1, int x2, int y2)
{
  int pad = 15;
  myEllipse(x1 + pad, y1 + pad, x2 - pad, y2 - pad, 255, 50, 50); // Red
}

void drawGem2_Square(int x1, int y1, int x2, int y2)
{
  int pad = 16;
  myRect(x1 + pad, y1 + pad, x2 - pad, y2 - pad, 50, 205, 50); // Green
}

void drawGem3_Triangle(int x1, int y1, int x2, int y2)
{
  int pad = 15;
  myTriangle(x1 + pad, y1 + pad, x2 - pad, y2 - pad, 65, 105, 225); // Blue
}

void drawGem4_HorizontalRect(int x1, int y1, int x2, int y2)
{
  int padX = 12;
  int padY = 22;
  myRect(x1 + padX, y1 + padY, x2 - padX, y2 - padY, 255, 215, 0); // Yellow
}

void drawGem5_VerticalOval(int x1, int y1, int x2, int y2)
{
  int padX = 22;
  int padY = 12;
  myEllipse(x1 + padX, y1 + padY, x2 - padX, y2 - padY, 255, 0, 255); // Magenta
}

void drawGem6_Cross(int x1, int y1, int x2, int y2)
{
  int pad = 18;
  int midX = (x1 + x2) / 2;
  int midY = (y1 + y2) / 2;
  for (int i = -1; i <= 1; i++)
  {
    myLine(x1 + pad, midY + i, x2 - pad, midY + i, RGB(0, 255, 255)); // Cyan
    myLine(midX + i, y1 + pad, midX + i, y2 - pad, RGB(0, 255, 255));
  }
  myRect(midX - 4, midY - 4, midX + 4, midY + 4, 0, 255, 255);
}

void drawGem7_X(int x1, int y1, int x2, int y2)
{
  int pad = 18;
  for (int i = -1; i <= 1; i++)
  {
    myLine(x1 + pad + i, y1 + pad, x2 - pad + i, y2 - pad, RGB(255, 140, 0)); // Orange
    myLine(x2 - pad + i, y1 + pad, x1 + pad + i, y2 - pad, RGB(255, 140, 0));
  }
  myEllipse((x1 + x2) / 2 - 5, (y1 + y2) / 2 - 5, (x1 + x2) / 2 + 5, (y1 + y2) / 2 + 5, 255, 140, 0);
}

// --- VISUAL FUNCTIONS ---

void displayTable(int matrix[100][100])
{
  // 1. Draw Board
  for (int i = 0; i < rowCols; i++)
  {
    for (int j = 0; j < rowCols; j++)
    {
      int x1 = BOARD_OFFSET_X + j * CELL_SIZE;
      int y1 = BOARD_OFFSET_Y + i * CELL_SIZE;
      int x2 = x1 + CELL_SIZE;
      int y2 = y1 + CELL_SIZE;

      // Clear cell
      myRect(x1, y1, x2, y2, 0, 0, 0);

      // Draw Grid Lines (Gray)
      myLine(x1, y1, x2, y1, 100);
      myLine(x1, y2, x2, y2, 100);
      myLine(x1, y1, x1, y2, 100);
      myLine(x2, y1, x2, y2, 100);

      // Draw Gem
      if (matrix[i][j] != 32)
      {
        switch (matrix[i][j])
        {
        case 1:
          drawGem1_Circle(x1, y1, x2, y2);
          break;
        case 2:
          drawGem2_Square(x1, y1, x2, y2);
          break;
        case 3:
          drawGem3_Triangle(x1, y1, x2, y2);
          break;
        case 4:
          drawGem4_HorizontalRect(x1, y1, x2, y2);
          break;
        case 5:
          drawGem5_VerticalOval(x1, y1, x2, y2);
          break;
        case 6:
          drawGem6_Cross(x1, y1, x2, y2);
          break;
        case 7:
          drawGem7_X(x1, y1, x2, y2);
          break;
        }
      }
    }
  }

  // 2. Draw HUD (Replaces printStatus)
  gotoxy(0, 0);
  cout << "Moves left : " << userMoves << "    Score : " << score << "      " << endl;
  cout << "Use Arrow Keys. Enter to Select/Swap.         ";
}

void drawCursor(int r, int c, int R, int G, int B)
{
  int x1 = BOARD_OFFSET_X + c * CELL_SIZE;
  int y1 = BOARD_OFFSET_Y + r * CELL_SIZE;
  int x2 = x1 + CELL_SIZE;
  int y2 = y1 + CELL_SIZE;

  // Draw lines ON TOP of the grid lines
  // We draw 3 layers to make it thick
  for (int k = 0; k < 3; k++)
  {
    myLine(x1 + k, y1 + k, x2 - k, y1 + k, RGB(R, G, B)); // Top
    myLine(x1 + k, y2 - k, x2 - k, y2 - k, RGB(R, G, B)); // Bottom
    myLine(x1 + k, y1 + k, x1 + k, y2 - k, RGB(R, G, B)); // Left
    myLine(x2 - k, y1 + k, x2 - k, y2 - k, RGB(R, G, B)); // Right
  }
}

int swapValues(int &a, int &b)
{
  int temp = a;
  a = b;
  b = temp;
  return true;
}

// --- LOGIC FUNCTIONS (From your provided file, stripped of 'cout' highlights) ---

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

        // 1. Down T
        if ((i >= 0 && i < rowCols - 2 && j >= 1 && j < rowCols - 1) && (matrix[i][j - 1] == key && matrix[i][j + 1] == key && matrix[i + 1][j] == key && matrix[i + 2][j] == key))
        {
          isMatch = true;
          score += 30;
          matrix[i][j] = 7; // Bomb
          matrix[i + 1][j] = 32;
          matrix[i + 2][j] = 32;
          matrix[i][j - 1] = 32;
          matrix[i][j + 1] = 32;
        }
        // 2. Up T
        else if ((i >= 2 && i < rowCols && j >= 1 && j < rowCols - 1) && (matrix[i][j - 1] == key && matrix[i][j + 1] == key && matrix[i - 1][j] == key && matrix[i - 2][j] == key))
        {
          isMatch = true;
          score += 30;
          matrix[i][j] = 7;
          matrix[i - 1][j] = 32;
          matrix[i - 2][j] = 32;
          matrix[i][j - 1] = 32;
          matrix[i][j + 1] = 32;
        }
        // 3. Left T
        else if ((i >= 1 && i < rowCols - 1 && j >= 2 && j < rowCols) && (matrix[i - 1][j] == key && matrix[i + 1][j] == key && matrix[i][j - 1] == key && matrix[i][j - 2] == key))
        {
          isMatch = true;
          score += 30;
          matrix[i][j] = 7;
          matrix[i - 1][j] = 32;
          matrix[i + 1][j] = 32;
          matrix[i][j - 1] = 32;
          matrix[i][j - 2] = 32;
        }
        // 4. Right T
        else if ((i >= 1 && i < rowCols - 1 && j >= 0 && j < rowCols - 2) && (matrix[i - 1][j] == key && matrix[i + 1][j] == key && matrix[i][j + 1] == key && matrix[i][j + 2] == key))
        {
          isMatch = true;
          score += 30;
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

        // 1. Down-Right
        if ((i + 2 < rowCols && j + 2 < rowCols) &&
            (matrix[i + 1][j] == key && matrix[i + 2][j] == key && matrix[i][j + 1] == key && matrix[i][j + 2] == key))
        {
          isMatch = true;
          score += 10;
          matrix[i][j] = 6;
          matrix[i + 1][j] = 32;
          matrix[i + 2][j] = 32;
          matrix[i][j + 1] = 32;
          matrix[i][j + 2] = 32;
        }
        // 2. Down-Left
        else if (i + 2 < rowCols && j - 2 >= 0 &&
                 matrix[i + 1][j] == key && matrix[i + 2][j] == key &&
                 matrix[i][j - 1] == key && matrix[i][j - 2] == key)
        {
          isMatch = true;
          score += 10;
          matrix[i][j] = 6;
          matrix[i + 1][j] = 32;
          matrix[i + 2][j] = 32;
          matrix[i][j - 1] = 32;
          matrix[i][j - 2] = 32;
        }
        // 3. Up-Right
        else if (i - 2 >= 0 && j + 2 < rowCols &&
                 matrix[i - 1][j] == key && matrix[i - 2][j] == key &&
                 matrix[i][j + 1] == key && matrix[i][j + 2] == key)
        {
          isMatch = true;
          score += 10;
          matrix[i][j] = 6;
          matrix[i - 1][j] = 32;
          matrix[i - 2][j] = 32;
          matrix[i][j + 1] = 32;
          matrix[i][j + 2] = 32;
        }
        // 4. Up-Left
        else if (i - 2 >= 0 && j - 2 >= 0 &&
                 matrix[i - 1][j] == key && matrix[i - 2][j] == key &&
                 matrix[i][j - 1] == key && matrix[i][j - 2] == key)
        {
          isMatch = true;
          score += 10;
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
    isMatch = true;
  if (checkTPatterns(matrix))
    isMatch = true;

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
          for (int k = 0; k < currentCount; k++)
          {
            int c = j - k;
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
        currentCount = 1;
      }
    }
    if (currentCount >= 3)
    {
      isMatch = true;
      score += (currentCount * 2);
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
    if (colCount >= 3)
    {
      isMatch = true;
      score += (colCount * 2);
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

void activateSpecialGem(int matrix[100][100], int r, int c, int val)
{
  int type = matrix[r][c];
  matrix[r][c] = 32;

  if (type == 5) // Line Blast
  {
    score += 20;
    for (int j = 0; j < rowCols; j++)
      if (matrix[r][j] != 32)
        matrix[r][j] = 32;
    for (int i = 0; i < rowCols; i++)
      if (matrix[i][c] != 32)
        matrix[i][c] = 32;
  }
  else if (type == 6) // Bomb (3x3)
  {
    score += 30;
    for (int i = r - 1; i <= r + 1; i++)
      for (int j = c - 1; j <= c + 1; j++)
        if (i >= 0 && i < rowCols && j >= 0 && j < rowCols)
          matrix[i][j] = 32;
  }
  else if (type == 7) // Color Clear
  {
    for (int i = 0; i < rowCols; i++)
      for (int j = 0; j < rowCols; j++)
        if (matrix[i][j] == val)
          matrix[i][j] = 32;
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
    // Refill top
    for (int j = 0; j < rowCols; j++)
    {
      if (matrix[0][j] == 32)
      {
        matrix[0][j] = (rand() % 4) + 1; // 1 to 4
        moved = true;
      }
    }
    if (moved)
    {
      Sleep(150);
      displayTable(matrix);
    }
  }
}

void genTableValues(int matrix[100][100])
{
  for (int i = 0; i < 8; i++)
  {
    for (int j = 0; j < 8; j++)
    {
      while (true)
      {
        // Generate 1-5
        int randomNumber = (rand() % 4) + 1;
        matrix[i][j] = randomNumber;

        if ((j >= 2 && matrix[i][j] == matrix[i][j - 1] && matrix[i][j] == matrix[i][j - 2]) ||
            (i >= 2 && matrix[i][j] == matrix[i - 1][j] && matrix[i][j] == matrix[i - 2][j]))
        {
          continue;
        }
        else
        {
          break;
        }
      }
    }
  }
}

int main()
{
  system("cls");
  srand(time(NULL));
  int matrix[100][100];

  genTableValues(matrix);

  int gridX = 0, gridY = 0;

  // Variables for selection
  bool isSelected = false;
  int selected_x = -1;
  int selected_y = -1;
  int key;

  // Initial display
  displayTable(matrix);
  // Draw initial cursor
  drawCursor(gridY, gridX, 255, 0, 0);

  while (true)
  {
    if (isCursorKeyPressed(key))
    {
      // 1. Redraw board to clear old cursors/text
      displayTable(matrix);

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
        if (gridX < rowCols - 1)
          gridX++;
        break;
      case 4: // Down
        if (gridY < rowCols - 1)
          gridY++;
        break;
      case 5: // Enter
        if (!isSelected)
        {
          // Select First Gem
          selected_x = gridX;
          selected_y = gridY;
          isSelected = true;
        }
        else
        {
          // Second Selection - Swap
          int dx = abs(gridX - selected_x);
          int dy = abs(gridY - selected_y);

          if (dx + dy == 1) // Adjacent
          {
            swapValues(matrix[selected_y][selected_x], matrix[gridY][gridX]);
            displayTable(matrix);
            Sleep(200);

            // Check Special Gems Trigger
            bool specialTriggered = false;
            if (matrix[selected_y][selected_x] >= 5)
            {
              activateSpecialGem(matrix, selected_y, selected_x, matrix[gridY][gridX]);
              specialTriggered = true;
            }
            if (matrix[gridY][gridX] >= 5)
            {
              activateSpecialGem(matrix, gridY, gridX, matrix[selected_y][selected_x]);
              specialTriggered = true;
            }

            // Check Matches
            bool matchFound = checkRowColMatch(matrix);

            if (!matchFound && !specialTriggered)
            {
              // Invalid
              swapValues(matrix[gridY][gridX], matrix[selected_y][selected_x]);
              displayTable(matrix);
            }
            else
            {
              // Valid
              userMoves--;
              while (true)
              {
                displayTable(matrix);
                Sleep(300);
                gravity(matrix);
                if (!checkRowColMatch(matrix))
                  break;
              }

              if (userMoves <= 0)
              {
                system("cls");
                gotoxy(0, 0);
                cout << "GAME OVER! Final Score: " << score << endl;
                return 0;
              }
            }
          }
          isSelected = false;
          displayTable(matrix); // Refresh view after swap attempt
        }
        break;
      }

      // 2. Draw Cursors AFTER displayTable so they stay visible
      if (isSelected)
      {
        drawCursor(selected_y, selected_x, 0, 255, 0); // Green (Selected)
      }
      drawCursor(gridY, gridX, 255, 0, 0); // Red (Hover)
    }
  }
  return 0;
}