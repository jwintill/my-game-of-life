#include <SDL.h>
#include "Grid.h"

const int NEIGHBORHOOD = 7; // side length of neighborhood square (should be odd number)
Grid::Grid(int windowSize, int cellSize){
    this->cellSize = cellSize;
    this->rowSize = windowSize/cellSize;
    this->gridSize = rowSize*rowSize;

    grid = new int*[rowSize];
    nextGridState = new int*[rowSize];

    for (int i = 0; i < rowSize; i++) {
        grid[i] = new int[rowSize]();
        nextGridState[i] = new int[rowSize]();
    }

    for (int x = 0; x < this->rowSize; x++){
        for (int y = 0; y < this->rowSize; y++){    
            grid[x][y] = rand() % 1530;
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

int Grid::getNeighbors(int x, int y){
    int neighbors = 0;
    for(int i = -1*(NEIGHBORHOOD-1)/2; i <= (NEIGHBORHOOD-1)/2; i++){
        for(int j = -1*(NEIGHBORHOOD-1)/2; j <= (NEIGHBORHOOD-1)/2; j++){
            if (i == 0 && j == 0)
                continue;
            
            int neighborX = x + i;
            int neighborY = y + j;
            if(inBounds(neighborX, neighborY)){
                neighbors += grid[neighborX][neighborY];
            }
        }
    }

    return neighbors;
}

void Grid::nextState(){
    for(int x = 0; x < this->rowSize; x++){
        for(int y = 0; y < this->rowSize; y++){    
            int neighbors = this->getNeighbors(x, y);
            int possibleNeighbors = NEIGHBORHOOD * NEIGHBORHOOD - 1;
            //setting state to an average of neighbors scaled to 1530(6*255)
            nextGridState[x][y] = (static_cast<int>((static_cast<double>(neighbors)/possibleNeighbors)*1529) % 1530)*.05 + grid[x][y]*.95;
    
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
            int currState = grid[x][y];
            int color[3] = {0, 0, 0};
            int transitionPhase = currState / 255;
            switch (transitionPhase) {
                case 0:
                    color[0] = 255;
                    color[1] = currState % 255;
                    color[2] = 0;
                    break;
                case 1:
                    color[0] = 255 - (currState % 255);
                    color[1] = 255;
                    color[2] = 0;
                    break;
                case 2:
                    color[0] = 0;
                    color[1] = 255;
                    color[2] = currState % 255;
                    break;
                case 3: 
                    color[0] = 0;
                    color[1] = 255 - (currState % 255);
                    color[2] = 255;
                    break;
                case 4:
                    color[0] = currState % 255;
                    color[1] = 0;
                    color[2] = 255;
                    break;
                case 5:
                    color[0] = 255;
                    color[1] = 0;
                    color[2] = 255 - (currState % 255);
                    break;
            }
            
            SDL_SetRenderDrawColor(renderer, color[0], color[1], color[2], 255);
            SDL_Rect rect = {x*cellSize, y*cellSize, cellSize, cellSize};
            SDL_RenderFillRect(renderer, &rect);
        }
    }

    SDL_RenderPresent(renderer);
}