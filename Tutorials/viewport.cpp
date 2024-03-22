//
//  viewport.cpp
//  MyPseudoGame
//
//  Created by mac on 3/22/24.
//

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>

using namespace std;

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 800;
const char* WINDOW_TITLE = "SDL";

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
SDL_Texture* texture = NULL;

void logErrorAndExit(const char* msg, const char* error) {
    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "%s : %s", msg, error);
    SDL_Quit();
}

bool init() {
    bool success = true;
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        logErrorAndExit("initSDL", SDL_GetError());
    }
    else {
        window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        
        if (window == NULL) {
            logErrorAndExit("createWindow", SDL_GetError());
            success = false;
        }
        
        else {
            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);
            
            if (renderer == NULL) {
                logErrorAndExit("createRenderer", SDL_GetError());
                success = false;
            }
        }
    }
    return success;
}


