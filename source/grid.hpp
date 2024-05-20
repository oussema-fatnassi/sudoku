#ifndef GRID_H
#define GRID_H
#include <vector>
using namespace std;

class Grid {
private:
    bool gridDrawn;                                         // Flag to check if the grid is drawn
public:
    struct CellPosition {                                   // Structure to store the cell position
        int row;
        int col;
    };

    static const int SIZE = 9;                              // Size of the grid (9x9)

    vector<vector<int> > cells;                             // 2D vector to store the grid
    vector<vector<int> > unsolvedGrid;                      // 2D vector to store the unsolved grid
    vector<vector<int> > solvedGrid;                        // 2D vector to store the solved grid
    vector<vector<vector<int>>> allGrids;                   // 3D vector to store all the grids
    vector<vector<vector<int>>> allSolutionGrids;           // 3D vector to store all the solution grids

    int gridCount;                                          // Number of grids in the file
    int originalRandomIndex;                                // Original random index
    int difficulty;                                         // Difficulty level

    Grid();                                                 // Constructor
    void menu();                                            // All methods written in grid.cpp
    void chooseDifficulty();
    void loadGridFromFile(const char* filename);
    void loadGridSolutionFromFile(const char* filename);
    void drawGrid();

    void printUnsolvedGrid();
    void copyUnsolvedGrid();
    CellPosition getCellPosition(int row, int col);
    void setCellValue(int row, int col, int value);
    int getCellValue(int row, int col);
    void chooseCellValue();
    void checkSolution();
    ~Grid();                                                // Destructor
};

#endif  // GRID_H