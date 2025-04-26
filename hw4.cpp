#include <iostream>

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
index (i, j) will make all neighboring fresh oranges dirty by the next day. The
3
neighbors of any cell are the cells directly above, below, to the left, and to the
right (assuming the neighbor is in the bounds of the matrix). All dirty oranges
        will become rotten by the next day. If it is impossible to rot every orange then
        simply return -1.
 */

// constexpr to be able to determined at compile time
constexpr int M = 5; // ROWS
constexpr int N = 5; // COLS

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

void ageGridOneDay(int (&grid)[M][N]) {
    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < N; ++j) {

        }
    }
}

int main() {
    int grid[M][N] = {{0, 0, 0, 0, 0},
                      {0, 0, 0, 0, 0},
                      {0, 0, 0, 0, 0},
                      {0, 0, 0, 0, 0},
                      {0, 0, 0, 0, 0}};

    displayGrid(grid);

}
