//
//  textureRender.cpp
//  MyPseudoGame
//
//  Created by mac on 3/21/24.
//

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>

using namespace std;

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 800;
const char* WINDOW_TITLE = "SDL";

SDL_Window* window = NULL;
//where to show texture, render to the screen
SDL_Renderer* renderer = NULL;

//surface = where to show the surfaces
SDL_Texture* texture = NULL;

void logErrorAndExit( const char* msg, const char* error) {
    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "%s : %s", msg, error);
    SDL_Quit();
}

bool init() {
    bool success = true;
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        logErrorAndExit("init", SDL_GetError());
        success = false;
    }
    else {
        window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        
        if (window == NULL) {
            logErrorAndExit("WindowCreate", SDL_GetError());
            success = false;
        }
        
        else {
            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
            
            if (renderer == NULL) {
                logErrorAndExit("RendererCreate", SDL_GetError());
                success = false;
            }
            
            else {
                SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
                
                if(!IMG_Init(IMG_INIT_JPG|IMG_INIT_PNG)) {
                    logErrorAndExit("ImageLoading", IMG_GetError());
                    success = false;
                }
            }
        }
    }
    return success;
}

SDL_Texture* loadTexture (string path) {
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == NULL)
        cout << "image could not be loaded! Error: " << IMG_GetError();
    SDL_Texture* loadedTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
    SDL_FreeSurface(loadedSurface);
    return loadedTexture;
}

void close() {
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

int main(int argc, char* argv[])
{
    if(!init())
        cout << "SDL could not be created!";
    texture = loadTexture("loaded.png");
    
    SDL_Event e;
    bool quit = false;
    while (quit == false) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT)
                quit = true;
        }
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, texture, NULL, NULL);
        SDL_RenderPresent(renderer);
    }
    
    close();
    return 0;
}
