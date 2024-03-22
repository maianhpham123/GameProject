#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>

using namespace std;

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 800;
const char* WINDOW_TITLE = "SDL";

SDL_Window* window = NULL;
SDL_Surface* surface = NULL;
SDL_Surface* background = NULL;

bool init () {
    bool success = true;
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
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
                surface = SDL_GetWindowSurface(window);
            }
        }
    return success;
}

bool loadMedia () {
    bool success = true;
    background = SDL_LoadBMP("hello_world.bmp");
    if (background == NULL) {
        cout << "Image could not be loaded! Error: " << SDL_GetError();
        success = false;
    }
    return success;
}

void close () {
    SDL_FreeSurface(background);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

int main(int argc, char* argv[])
{
    if(!init())
        cout << "failed to initialise!";
    else {
        if(!(loadMedia()))
            cout << "failed to load media!";
        else {
            SDL_BlitSurface(background, NULL, surface, NULL);
            SDL_UpdateWindowSurface(window);
            SDL_Event e;
            bool quit = false;
            while(quit == false) {
                while(SDL_PollEvent(&e)) {
                    if (e.type == SDL_QUIT) quit = true;
                }
            }
        }
    }
    close();
}
