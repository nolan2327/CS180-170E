#include <iostream>
#include <set>

using namespace std;

/*
You are given a matrix of dimension M * N, where each cell in the matrix is
initialized with values 0, 1, 2, or 3 which has the following meaning:
- 0: This cell contains no orange.
- 1: Cell has a fresh orange.
- 2: Cell has a dirty orange.
- 3: Cell has a rotten orange.
The input matrix represents the state of all cells at day 0. The task is
to find the first day all oranges become rotten. A dirty or rotten orange at
index (i, j) will make all neighboring fresh oranges dirty by the next day.

The 3 neighbors of any cell are the cells directly above, below, to the left,
and to the right (assuming the neighbor is in the bounds of the matrix). All dirty
oranges will become rotten by the next day. If it is impossible to rot every orange
then simply return -1.
 */

// TODO: You could multithread a lot of this to make it quicker

// constexpr to be able to determined at compile time
constexpr int M = 5; // ROWS
constexpr int N = 5; // COLS
/*
 *   C O L U M N
 * R
 * O
 * W
 */

// stages of fruits
constexpr int NONE = 0;
constexpr int FRESH = 1;
constexpr int DIRTY = 2;
constexpr int ROTTEN = 3;


void displayGrid(int (&grid)[M][N]) {
    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < N; ++j) {
            cout << grid[i][j] << " ";
        }
        cout << endl;
    }
}

bool checkAdjacentToInfect(const int (&grid)[M][N], int row, int col) {
    int dRow[] = {-1, 1, 0, 0}; // Used to protect from memory violations
    int dCol[] = {0, 0, -1, 1};

    for (int d = 0; d < 4; ++d) {
        int newRow = row + dRow[d];
        int newCol = col + dCol[d];
        if (newRow >= 0 && newRow < M && newCol >= 0 && newCol < N) {
            if (grid[newRow][newCol] == DIRTY || grid[newRow][newCol] == ROTTEN) {
                return true;
            }
        }
    }
    return false;
}

void ageOneDay(int (&grid)[M][N]) {
    std::vector<pair<int, int>> effect_cells; // Fix error of infecting multiple times

    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < N; ++j) {
            if(grid[i][j] == FRESH && checkAdjacentToInfect(grid, i, j)) {
                // Check if adjacent fruit is infected, if so, increment
                effect_cells.push_back(pair(i, j));
            }
            else if(grid[i][j] == DIRTY) {
                grid[i][j]++;
            }
        }
    }

    for(int i = 0; i < effect_cells.size(); i++) {
        int row = effect_cells[i].first;
        int col = effect_cells[i].second;

        grid[row][col]++;
    }
}

bool checkInbounds(int row, int col) {
    return (row >= 0 && row < M && col >= 0 && col < N);
}

bool isSlotLegal(const int (&grid)[M][N], int row, int col) {
    if (!checkInbounds(row, col)) {
        return true; // Consider out-of-bounds slots as legal
    }
    return grid[row][col] != NONE;
}

bool areAllSlotsLegal(const int (&grid)[M][N]) {
    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < N; ++j) {
            if (!isSlotLegal(grid, i, j)) {
                return false;
            }
        }
    }
    return true;
}


int main() {

    int grid[M][N] = {
            {DIRTY, FRESH, FRESH, FRESH, FRESH},
            {FRESH, FRESH, FRESH, FRESH, FRESH},
            {FRESH, FRESH, FRESH, FRESH, FRESH},
            {FRESH, FRESH, FRESH, FRESH, NONE},
            {FRESH, FRESH, FRESH, NONE, FRESH}
    };

    displayGrid(grid);

    if(areAllSlotsLegal(grid)) {
        cout << "All legal!" << endl;
    }

    cout << endl;
    ageOneDay(grid);
    displayGrid(grid);

    cout << endl;
    ageOneDay(grid);
    displayGrid(grid);

    cout << endl;
    ageOneDay(grid);
    displayGrid(grid);

    cout << endl;
    ageOneDay(grid);
    displayGrid(grid);

    cout << endl;
    ageOneDay(grid);
    displayGrid(grid);

    cout << endl;
    ageOneDay(grid);
    displayGrid(grid);

    cout << endl;
    ageOneDay(grid);
    displayGrid(grid);
}
