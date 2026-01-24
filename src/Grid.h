#ifndef GRID_H
#define GRID_H

#include <SDL.h>
#include <cstdlib>  

class Grid {
private:
    int** grid;
    int** nextGridState;
    int gridSize;
    int rowSize;
    int cellSize;

    bool inBounds(int x, int y);
    int getNeighbors(int x, int y);

public:
    Grid(int windowSize, int cell);
    ~Grid();

    void nextState();
    void render(SDL_Renderer* renderer);
};

#endif