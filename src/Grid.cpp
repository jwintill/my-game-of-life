#include <SDL.h>
#include "Grid.h"

const int INNERNEIGHBORHOOD = 7; // side length of neighborhood square (should be odd number)
const int OUTERNEIGHBORHOOD = 21;
Grid::Grid(int windowSize, int cellSize, double b1, double b2, double d1, double d2) {
    this->cellSize = cellSize;
    this->rowSize = windowSize/cellSize;
    this->gridSize = rowSize*rowSize;
    this->b1 = b1;
    this->b2 = b2;
    this->d1 = d1;
    this->d2 = d2;

    grid = new double*[rowSize];
    nextGridState = new double*[rowSize];

    for (int i = 0; i < rowSize; i++) {
        grid[i] = new double[rowSize]();
        nextGridState[i] = new double[rowSize]();
    }

    for (int x = 0; x < rowSize; x++){
        for (int y = 0; y < rowSize; y++){    
            grid[x][y] = 0;
        }
    }

    for (int x = 3*rowSize/8; x < 5*rowSize/8; x++){
        for (int y = 3*rowSize/8; y < 5*rowSize/8; y++){    
            grid[x][y] = 1.0;
        }
    }
    
}

Grid::~Grid() {
    for (int i = 0; i < rowSize; i++) {
        delete[] grid[i];
        delete[] nextGridState[i];
    }
    delete[] grid;
    delete[] nextGridState;
}

bool Grid::inBounds(int x, int y) {
    return (x >= 0 && x < rowSize) && (y >= 0 && y < rowSize);
}

double Grid::getInnerNeighbors(int x, int y){
    double sum = 0;
    int count = 0;
    int neighborhoodRadius = (INNERNEIGHBORHOOD - 1) / 2;
    for(int i = -1 * neighborhoodRadius; i <= neighborhoodRadius; i++){
        int dx = sqrt(neighborhoodRadius * neighborhoodRadius - i * i);
        for(int j = -1 * dx; j <= dx; j++){
            if (i == 0 && j == 0)
                continue;
            
            if(inBounds(x+i, y+j)){
                sum += grid[x+i][y+j];
                count++;
            }
        }
    }

    return sum/count;
}

double Grid::getOuterNeighbors(int x, int y){
    double sum = 0;
    int count = 0;
    int outerNeighborhoodRadius = (OUTERNEIGHBORHOOD - 1) / 2;
    int innerNeighborhoodRadius = (INNERNEIGHBORHOOD - 1) / 2;
    for(int i = -1 * outerNeighborhoodRadius; i <= outerNeighborhoodRadius; i++){
        int dx = sqrt(outerNeighborhoodRadius * outerNeighborhoodRadius - i * i);
        for(int j = -1 * dx; j <= dx; j++){
            if ((i == 0 && j == 0)|| (abs(i) <= innerNeighborhoodRadius && abs(j) <= innerNeighborhoodRadius))
                continue;
            
            if(inBounds(x+i, y+j)){
                sum += grid[x+i][y+j];
                count++;
            }
        }
    }

    return sum/count;
}

double Grid::sigmoid1(double x, double a, double alpha){
    double eulers = 2.71828182845904523536;
    return (1 / (1 + pow(eulers,(-(x-a)*4/alpha))));
}

double Grid::sigmoid2(double x, double a, double b, double alpha){
    return (sigmoid1(x, a, alpha) * (1 - sigmoid1(x, b, alpha)));
}

double Grid::sigmoid3(double x, double y, double m, double alpha){
    return (x * (1 - sigmoid1(m, 0.5, alpha)) + (y * sigmoid1(m, 0.5, alpha)));
}

// m and n are the inner and outer "fillings"
// uses the transition function to determine the next state
double Grid::transitionFunction(int x, int y){
    double m = this->getInnerNeighbors(x, y);
    double n = this->getOuterNeighbors(x, y);

    double alpha_m = 0.147;
    double alpha_n = 0.028;

    double threshold_low  = sigmoid3(b1, d1, m, alpha_n); 
    double threshold_high = sigmoid3(b2, d2, m, alpha_n);

    return sigmoid2(n, threshold_low, threshold_high, alpha_m);
}

void Grid::nextState(){
    for(int x = 0; x < this->rowSize; x++){
        for(int y = 0; y < this->rowSize; y++){    
            nextGridState[x][y] = transitionFunction(x,y) * .05 + grid[x][y] * .95;
        }
    }

    for(int x = 0; x < this->rowSize; x++){
        for(int y = 0; y < this->rowSize; y++){    
            grid[x][y] = nextGridState[x][y];
        }
    }
}

void Grid::render(SDL_Renderer* renderer){
    for(int x = 0; x < this->rowSize; x++){
        for(int y = 0; y < this->rowSize; y++){
            // colors range from black -> red-> green -> blue -> white
            int currState = grid[x][y] * 1785; // 1785 = 255 * 7
            int color[3] = {0, 0, 0};
            int transitionPhase = currState / 255;
            switch (transitionPhase) {
                case 0: //black to red
                    color[0] = currState % 255;
                    color[1] = 0;
                    color[2] = 0;
                    break;
                case 1: //red to yellow
                    color[0] = 255;
                    color[1] = 255 - (currState % 255);
                    color[2] = 0;
                    break;
                case 2: //yellow to green
                    color[0] = currState % 255;
                    color[1] = 255;
                    color[2] = 0;
                    break;
                case 3: //green to cyan
                    color[0] = 0;
                    color[1] = 255;
                    color[2] = 255 - (currState % 255);
                    break;
                case 4: //cyan to blue
                    color[0] = 0;
                    color[1] = currState % 255;
                    color[2] = 255;
                    break;
                case 5: //blue to magenta
                    color[0] = 255 - (currState % 255);
                    color[1] = 0;
                    color[2] = 255;
                    break;
                case 6: //magenta to white
                    color[0] = 255;
                    color[1] = currState % 255;
                    color[2] = 255;
                    break;
            }
            
            SDL_SetRenderDrawColor(renderer, color[0], color[1], color[2], 255);
            SDL_Rect rect = {x*cellSize, y*cellSize, cellSize, cellSize};
            SDL_RenderFillRect(renderer, &rect);
        }
    }

    SDL_RenderPresent(renderer);
}