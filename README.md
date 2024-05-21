<p align="center">
  <img src="assets/images/logo.png" alt="Sudoku logo" width="200" height="200"/>
</p>

Sudoku game project in C++
It's popular form of number game. In its simplest and most common configuration, sudoku consists of a 9 × 9 grid with numbers appearing in some of the squares. The object of the puzzle is to fill the remaining squares.

# DESCRIPTION
Sudoku is based entirely on logic, without any arithmetic involved, and the level of difficulty is determined by the quantity and positions of the original numbers.

# SUDOKU RULES
While solving the puzzle, you need to follow one sudoku rule only. You have to fill in the blank cells with numbers from 1 to 9, so that:
- in any row, 
- in any column,
- in any 3x3 subgrid
numbers were used only once without any repetitions.

# PROJECT
We developped two different versions of the sudoku game, one in the terminal and the second with a GUI.
Terminal: 
- In the source folder you can launch the game using the terminal and compiling the sudoku exe
- You will be able to choose the difficulty level of the sudoku and play.
- The sudokus are loaded from a file
GUI:
- In the src folder you can launch the game from the main.cpp using F5
- You can choose the difficulty level and start to play.
- The sudoku grids are generated with an algorithm. Based on the chosen difficulty you will have a sudoku grid with more or less empty cells

# ALGORITHM
- To resolve the sudoku grid we used a backtracking algorithm (it changes the cell values and if the resulting cell does not follow the game rules it goes back ad tries with another value)
- We create a fully solved sudoku grid that follows the rules
- We delete some values to have as a result a sudoku grid with one unique solution
- Based on the difficulty we change the number of unknowns (empty cells)

# INSTALLATION
Clone this repository: git clone https://github.com/oussema-fatnassi/sudoku.git 
Navigate to the game directory: cd sudoku

# CREDITS
Developed by Baptiste APPRIOU, Oussema Fatnassi and Ali Abakar Issa