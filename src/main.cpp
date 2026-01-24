#include <SDL.h>
#include "Grid.h"

/* whenever code is changed, run:
    cmake --build build
    ./build/GameOfLife
*/
const int WINDOW_SIZE = 800;
const int CELL_SIZE = 2;

int main() {
    Grid grid(WINDOW_SIZE, CELL_SIZE);

    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window* window = SDL_CreateWindow("Game of Life",
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                          WINDOW_SIZE, WINDOW_SIZE,
                                          SDL_WINDOW_SHOWN);

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    SDL_Event event;
    bool running = true;

    while (running) {
        while (SDL_PollEvent(&event))
            if (event.type == SDL_QUIT) running = false;

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        grid.nextState();
        grid.render(renderer);

        SDL_Delay(100);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}