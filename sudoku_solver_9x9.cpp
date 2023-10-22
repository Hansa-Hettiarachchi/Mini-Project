#include <iostream>
#include <fstream>
#include <vector>
#include <chrono> // For measuring execution time

const int N = 9; // Grid size for 9x9 Sudoku

bool isSafe(int grid[N][N], int row, int col, int num)
{
    // Check if 'num' is not present in current row, current column, and current 3x3 subgrid
    for (int x = 0; x < N; x++)
    {
        if (grid[row][x] == num || grid[x][col] == num || grid[row - row % 3 + x / 3][col - col % 3 + x % 3] == num)
        {
            return false;
        }
    }
    return true;
}

bool findEmptyLocation(int grid[N][N], int &row, int &col)
{
    for (row = 0; row < N; row++)
    {
        for (col = 0; col < N; col++)
        {
            if (grid[row][col] == 0)
            {
                return true;
            }
        }
    }
    return false;
}

bool solveSudoku(int grid[N][N])
{
    int row, col;
    if (!findEmptyLocation(grid, row, col))
    {
        return true; // Puzzle is solved
    }
    for (int num = 1; num <= 9; num++)
    {
        if (isSafe(grid, row, col, num))
        {
            grid[row][col] = num;
            if (solveSudoku(grid))
            {
                return true;
            }
            grid[row][col] = 0; // If num doesn't lead to a solution, reset and try the next number
        }
    }
    return false; // No solution for this configuration
}

void printGrid(int grid[N][N])
{
    for (int row = 0; row < N; row++)
    {
        for (int col = 0; col < N; col++)
        {
            std::cout << grid[row][col] << " ";
        }
        std::cout << std::endl;
    }
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cerr << "Usage: " << argv[0] << " <input_file.txt>" << std::endl;
        return 1;
    }

    int grid[N][N];

    // Read the Sudoku puzzle from the input file into the 'grid' array
    std::ifstream input(argv[1]);
    if (!input)
    {
        std::cerr << "Failed to open input file." << std::endl;
        return 1;
    }

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (!(input >> grid[i][j]))
            {
                std::cerr << "Invalid input file format." << std::endl;
                return 1;
            }
        }
    }

    input.close();

    // Measure the execution time
    auto start = std::chrono::high_resolution_clock::now();

    if (solveSudoku(grid))
    {
        // Puzzle is solvable
        std::cout << "Solution:\n";
        printGrid(grid);
    }
    else
    {
        // Puzzle has no solution
        std::cout << "No Solution\n";
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;

    std::cout << "Execution time: " << duration.count() << " seconds" << std::endl;

    return 0;
}
