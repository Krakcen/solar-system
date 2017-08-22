//
// Created by hugo on 17/08/17.
//

#include "Window.h"
#include <iostream>
#include "SDL.h"

const int SCREEN_WIDTH = 1024;
const int SCREEN_HEIGHT = 768;

int Window::run() {
    bool quit = false;
    this->windowX = SCREEN_WIDTH;
    this->windowY = SCREEN_HEIGHT;
    this->window = NULL;
    this->screenSurface = NULL;

    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
    else
    {
        this->window = SDL_CreateWindow( "Solar System", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, this->windowX, this->windowY, SDL_WINDOW_SHOWN );
        if( this->window == NULL )
            printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
        else
        {
            this->screenSurface = SDL_GetWindowSurface( window );
                while(!quit) {
                    if (SDL_PollEvent(&this->event) != 1);
                    switch (this->event.type) {
                        case SDL_QUIT:
                            quit = true;
                            break;
                        case SDL_KEYDOWN:
                            if (this->event.key.keysym.sym == SDLK_ESCAPE)
                                quit = true;
                            break;
                        default:
                            break;
                    }
                    //loop
                    this->showBackgroundColorTick();
                    SDL_UpdateWindowSurface( this->window );
                }
        }
    }

}

int Window::showBackgroundColorTick() {
    int colors[3][3] = {
            {0xFF, 0, 0} ,
            {0, 0xFF, 0} ,
            {0, 0, 0xFF}
    };
    static int colorState;

    if (colorState == 2)
        colorState = 0;
    else
        colorState++;

    int currentTime = SDL_GetTicks();
    static int lastTime;
    std::cout << "cur: " << currentTime << "\n";
    std::cout << "las: " << lastTime << "\n";
    if (currentTime > lastTime + 1000) {
        SDL_FillRect( this->screenSurface, NULL, SDL_MapRGB( this->screenSurface->format, (Uint8)colors[colorState][0], (Uint8)colors[colorState][1], (Uint8)colors[colorState][2] ) );
        lastTime = currentTime;
    }
    return (0);
}

Window::Window() {

}

Window::~Window() {
    SDL_FreeSurface(this->screenSurface);
    SDL_DestroyWindow(this->window);
    SDL_Quit();
    std::cout << "bye" << std::endl;
}
