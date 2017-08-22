//
// Created by hugo on 17/08/17.
//

#ifndef SOLAR_SYSTEM_WINDOW_H
#define SOLAR_SYSTEM_WINDOW_H

#include "SDL.h"

class Window {
private:
    int windowX;
    int windowY;
    SDL_Window* window;
    SDL_Surface* screenSurface;
    SDL_Event event;
public:
    int run();
    int showMenu();
    int showBackgroundColorTick();
    Window();
    ~Window();
};

#endif //SOLAR_SYSTEM_WINDOW_H
