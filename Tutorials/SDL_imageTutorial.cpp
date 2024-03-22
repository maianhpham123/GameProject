//
//  SDL_imageTutorial.cpp
//  MyPseudoGame
//
//  Created by mac on 3/20/24.
//

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>

using namespace std;

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 800;
const char* WINDOW_TITLE = "SDL";

SDL_Window* window = NULL;
SDL_Surface* screenSurface = NULL;

bool init () {
    bool success = true;
    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        cout << "SDL could not be initialised! Error: " << SDL_GetError();
        success = false;
    }
    
    else {
        window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        
        if (window == NULL) {
            cout << "Window could not be created! Error: " << SDL_GetError();
            success = false;
        }
        else {
            if(!IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG)) {
                cout << "Image could not be loaded! Error: " << IMG_GetError();
                success = false;
        }
            else {
                // get window surface
                screenSurface = SDL_GetWindowSurface(window);
            }
        }
    }
    return success;
}

SDL_Surface* loadedSurface (string path) {
    SDL_Surface* optimisedSurface = NULL;
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == NULL)
        cout << "Image could not be loaded! Error: " << IMG_GetError();
    else {
        optimisedSurface = SDL_ConvertSurface(loadedSurface, screenSurface->format, 0);
        if (optimisedSurface == NULL)
            cout << "surface could not be converted! Error: " << SDL_GetError();
        SDL_FreeSurface(loadedSurface);
    }
    return optimisedSurface;
}

void close() {
    IMG_Quit();
    SDL_DestroyWindow(window);
    SDL_Quit();
}

int main(int argc, char* argv[])
{
    if(!init())
        cout << "SDL could not be created!";
    SDL_Surface* png_Surface = loadedSurface("loaded.png");
    
    SDL_Event e;
    bool quit = false;
    while(quit == false) {
        while(SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT)
                quit = true;
        }
        SDL_BlitScaled(png_Surface, NULL, screenSurface, NULL); //blitscaled
        SDL_UpdateWindowSurface(window);
    }
    close();
    return 0;
}
