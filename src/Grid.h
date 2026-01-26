#ifndef GRID_H
#define GRID_H

#include <SDL.h>
#include <cstdlib>  

class Grid {
private:
    double** grid;
    double** nextGridState;
    int gridSize;
    int rowSize;
    int cellSize;
    double b1, b2, d1, d2;

    bool inBounds(int x, int y);
    double getInnerNeighbors(int x, int y);
    double getOuterNeighbors(int x, int y);
    double sigmoid1(double x, double a, double alpha);
    double sigmoid2(double x, double a, double b, double alpha);
    double sigmoid3(double x, double y, double m, double alpha);
    double transitionFunction(int x, int y);

public:
    Grid(int windowSize, int cellSize, double b1, double b2, double d1, double d2);
    ~Grid();

    void nextState();
    void render(SDL_Renderer* renderer);
};

#endif