#include <unistd.h>
#include <SDL2/SDL.h>
#include "board.h"

const double FPS = 60;
const double FRAMETIME_MICROSECONDS = 1000000 / FPS;

bool quit = false;

SDL_Event e;

int main() {
    SDL_Window* window = NULL;
    
    //The surface contained by the window
    SDL_Surface* screenSurface = NULL;

    SDL_Surface* XOut = NULL;

    //Initialize SDL
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
    }
    else
    {
        //Create window
        window = SDL_CreateWindow( "Conway's Game Of Life", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
        if( window == NULL )
        {
            printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
        }
    }

    // Create renderer
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);

    //Game boards
    Board board;

    while (!quit)
    {
        //Handle events on queue
        while( SDL_PollEvent( &e ) != 0 )
        {
            //User requests quit
            if( e.type == SDL_QUIT )
            {
                quit = true;
            }

            if(e.type == SDL_KEYDOWN) {
                if(e.key.keysym.sym == SDLK_ESCAPE) {
                    quit = true;
                }
                if(e.key.keysym.sym == SDLK_r) {
                    board.reset();
                }
            }
        }

        //update board;
        board.update_board();

        //draw board;
        board.render_board(renderer);

        SDL_RenderPresent(renderer);
    
        //Update the surface
        SDL_UpdateWindowSurface(window);

        //enforce framerate
        usleep(FRAMETIME_MICROSECONDS);
    }

    //Destroy window
    SDL_DestroyWindow( window );

    //Quit SDL subsystems
    SDL_Quit();

    return 0;
}