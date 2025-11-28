# My Candy Crush Game

Hello! This is my simple puzzle game made with C++. It's like Candy Crush. I built it to learn about arrays and basic programming.

## How to Play
1.  **Start the game.** You'll see a board with an 8x8 grid. It has colorful numbers that look like gems.
2.  **Move the cursor.** Use the **Arrow Keys** to move a square selector around the board.
3.  **Pick a gem.** Press **Enter** to choose a gem.
4.  **Swap with a neighbor.** Move the cursor to a gem next to your first choice (up, down, left, or right). Press **Enter** again to swap them.
5.  **Make matches.** If you swap gems and create a line of 3 or more of the same colored numbers (horizontally or vertically), they will disappear.
6.  **L-shaped matches.** You can also match gems in an L-shape for extra points!
7.  **Score high!** You get 20 moves in total. Try to get the highest score you can!

## Features
-   **Colors:** Different gem types are shown with different colors.
-   **Gravity:** When gems disappear, new gems fall from the top to fill the empty spaces.
-   **Special Matches:** The game finds and removes L-shaped matches, not just straight lines.
-   **Score & Moves:** The game keeps track of your score and how many moves you have left.
-   **New Board Every Time:** Each time you play, the game board is random and different.

## How to Get the Game Running
I use `g++` to compile this code. You will need `gdi32` and `user32` libraries. These are for Windows functions that help with the cursor and screen display.

To build and run, open your terminal and type these commands:
```
g++ prac60.cpp -o game -lgdi32 -luser32
game
```

## About the Code
-   `prac60.cpp`: This is the main file with all the game's code.
-   `help.h`: This file has helper functions for things like moving the cursor on the screen and checking key presses.
-   `gravity()`: This function makes the blocks fall down.
-   `checkRowColMatch()`: This function looks for 3 or more matching gems in a row or column.
-   `checkLPatterns()`: This function checks if there are any L-shaped matches.
-   `genTableValues()`: This function sets up the game board with random numbers.

Have fun playing my game!
