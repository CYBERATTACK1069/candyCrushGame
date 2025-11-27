# My Candy Crush Game

Hi! This is my simple puzzle game written in C++. It works like Candy Crush. I made this to practice arrays and logic.

## How to Play
1. Run the game. You will see an 8x8 grid with colorful gems.
2. Use **Arrow Keys** to move the cursor around the board.
3. Press **Enter** to select a gem.
4. Move to a neighbor gem (up, down, left, or right) and press **Enter** again to swap them.
5. If you match 3 or more same gems, they will disappear (turn to 0).
6. The gravity function will make the zeros go up and gems come down.

## Features
- **Colors:** I used different ANSI colors for gems.
- **Shapes:** Each color has a shape like Circle, Square, or Triangle.
- **Gravity:** When gems match, empty space is filled by gems falling from above.
- **Random Board:** Every time you start, the board is different.

## How to Compile and Run
I use `g++` to run this code. You need these libraries: `gdi32` and `user32` because I used some Windows functions for the cursor.

Type this in your terminal:
```
g++ prac60.cpp -o game -lgdi32 -luser32
game
```

## Code details
- `prac60.cpp`: This is the main file with all the code.
- `gravity()`: This function moves the blocks down.
- `checkRowColMatch()`: This checks if 3 gems are same in a row.
- `genTableValues()`: This fills the table with random numbers.

Enjoy my game!
