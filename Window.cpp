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
    enum State {
        exit = 0,
        menu = 42,
        solar = 1337
    };
    int loopReturnValue;

    State state = menu;
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
                while(state != exit) {
                    if (state == menu) {
                        if ((loopReturnValue = this->showMenu()) == 0)
                            state = exit;
                        else if (loopReturnValue == 1337)
                            state = solar;
                    }
                    else if (state == solar) {
                        //do solar loop here
                        if ((loopReturnValue = this->showBackgroundColorTick()) == 0)
                            state = exit;
                        else if (loopReturnValue == 42)
                            state = menu;
                    }
                }
        }
    }

}

int Window::showMenu() {
    int state = 1;

    std::cout << "Entering Menu" << std::endl;
    while (true) {
        if (SDL_PollEvent(&this->event) == 1) {
            switch (this->event.type) {
                case SDL_QUIT:
                    return (0);
                case SDL_KEYDOWN:
                    std::cout << "Key Pressed: " << this->event.key.keysym.sym << "\n";
                    if (this->event.key.keysym.sym == SDLK_ESCAPE)
                        return (0);
                    else if (this->event.key.keysym.sym == 13) {
                        return (1337);
                    }
                    break;
                default:
                    break;
            }
        }
        SDL_FillRect( this->screenSurface, NULL, SDL_MapRGB( this->screenSurface->format, 0XFF, 0xFF, 0xFF ) );
        SDL_UpdateWindowSurface( this->window );
    }
}

int Window::showBackgroundColorTick() {
    std::cout << "Entering Solar System" << std::endl;
    while (true) {
        if (SDL_PollEvent(&this->event) == 1) {
            switch (this->event.type) {
                case SDL_QUIT:
                    return (0);
                case SDL_KEYDOWN:
                    std::cout << "Key Pressed: " << this->event.key.keysym.sym << "\n";
                    if (this->event.key.keysym.sym == SDLK_ESCAPE)
                        return (0);
                    else if (this->event.key.keysym.sym == 13) {
                        return (42);
                    }
                    break;
                default:
                    break;
            }
        }
        static int colorState;
        int currentTime = SDL_GetTicks();
        static int lastTime;
        int colors[3][3] = {
                {0xFF, 0, 0} ,
                {0, 0xFF, 0} ,
                {0, 0, 0xFF}
        };

        if (currentTime > lastTime + 300) {
            SDL_FillRect( this->screenSurface, NULL, SDL_MapRGB( this->screenSurface->format, (Uint8)colors[colorState][0], (Uint8)colors[colorState][1], (Uint8)colors[colorState][2] ) );
            lastTime = currentTime;
            if (colorState == 2)
                colorState = 0;
            else
                colorState++;
        }
        SDL_UpdateWindowSurface( this->window );
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
