# My Candy Crush Game

Hello! This is my simple puzzle game made with C++. It's a bit like Candy Crush. I created it to practice coding with arrays and basic logic.

## How to Play
1.  **Start the game.** You'll see a board with an 8x8 grid. It shows colorful numbers acting as gems.
2.  **Move around.** Use the **Arrow Keys** on your keyboard to move a selector box.
3.  **Choose a gem.** Press **Enter** to pick one gem.
4.  **Swap with a neighbor.** Move the selector to a gem right next to your first choice (up, down, left, or right). Press **Enter** again to swap them.
5.  **Match and clear.** If you make a line of 3 or more of the same colored numbers (either straight across or straight up/down), they will vanish.
6.  **L-shaped matches.** You can also make L-shaped groups of gems for extra points!
7.  **Get a high score!** You only have 20 moves. Try to get as many points as you can!

## Features
-   **Colors:** Different gems have different colors.
-   **Falling Gems:** When gems disappear, new ones drop from the top to fill the gaps.
-   **Special Matches:** The game can find and clear L-shaped matches, not just straight lines.
-   **Score and Moves:** The game shows your score and how many moves you have left.
-   **New Game Every Time:** Each time you play, the board is different and random.

## How to Get the Game Running
I use `g++` to turn the code into a game you can play. You'll need `gdi32` and `user32` libraries. These are special tools for Windows that help with the cursor and drawing on the screen.

To build and play the game, open your computer's terminal (command prompt) and type these lines:
```
g++ prac60.cpp -o game -lgdi32 -luser32
game
```

## About the Code
-   `prac60.cpp`: This is the main file. It has all the game's code.
-   `help.h`: This file contains useful functions, like those that help move the cursor on the screen and detect key presses.
-   `gravity()`: This function makes the gem blocks fall down.
-   `checkRowColMatch()`: This function checks for 3 or more matching gems in a row or column.
-   `checkLPatterns()`: This function checks for L-shaped matches of gems.
-   `genTableValues()`: This function creates the game board with random numbers.

Have fun playing my game!