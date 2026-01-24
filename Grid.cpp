#include <SDL.h>
#include "Grid.h"

const int NEIGHBORHOOD = 3; // side length of neighborhood square (should be odd number)
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
            grid[x][y] = rand() % 2;
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
            nextGridState[x][y] = grid[x][y]; // default to current state
            if(grid[x][y] == 1){
                if(neighbors < 2 || neighbors > 3){
                    nextGridState[x][y] = 0;
                }
            }else if(neighbors == 3)
                nextGridState[x][y] = 1;
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
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // black        
            if(grid[x][y] == 1)
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // white

            SDL_Rect rect = {x*cellSize, y*cellSize, cellSize, cellSize};
            SDL_RenderFillRect(renderer, &rect);
        }
    }

    SDL_RenderPresent(renderer);
}