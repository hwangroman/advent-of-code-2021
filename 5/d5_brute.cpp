#include <stdio.h>
#include <cstring>
#include <algorithm>
#include <cassert>

const int GRID_SIZE = 1024;

int solve(FILE* file, bool diagonals) {
    char* grid = new char [GRID_SIZE*GRID_SIZE]();

    int x1,y1,x2,y2;
    while ( fscanf(file, "%d,%d -> %d,%d\n", &x1, &y1, &x2, &y2) != EOF ) {

        assert (x1 < GRID_SIZE && y1 < GRID_SIZE && x2 < GRID_SIZE && y2 < GRID_SIZE);

        if (y1 == y2) {
            int y = y1;
            int _x1 = std::min(x1, x2);
            int _x2 = std::max(x1, x2);
            for (int x = _x1; x <= _x2; ++x) {
                grid[y*GRID_SIZE + x]++;
            }
        } else if (x1 == x2) {
            int x = x1;
            int _y1 = std::min(y1, y2);
            int _y2 = std::max(y1, y2);
            for (int y = _y1; y <= _y2; ++y) {
                grid[y*GRID_SIZE + x]++;
            }
        } else if (diagonals) {
            int x_inc = x2 - x1 >= 0 ? 1 : -1;
            int y_inc = y2 - y1 >= 0 ? 1 : -1;
            for (int x = x1, y = y1; x != (x2 + x_inc); x += x_inc, y += y_inc) {
                grid[y*GRID_SIZE + x]++;
            }
        }
    }

    int result = 0;
    for (int y = 0; y < GRID_SIZE; ++y) {
        for (int x = 0; x < GRID_SIZE; ++x) {
            result += (grid[y*GRID_SIZE + x] >= 2) ? 1 : 0;
        }
    }

    delete grid;

    return result;
}

int main(int argc, char* argv[]) {
    FILE* file = fopen("input.txt", "r");
    printf("Result: %d\n", solve(file, true));
    fclose(file);
    return 1;
}