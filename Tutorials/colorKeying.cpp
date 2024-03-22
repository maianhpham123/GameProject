//
//  colorKeying.cpp
//  MyPseudoGame
//
//  Created by mac on 3/22/24.
//

#include "colorKeying.hpp"

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 800;
const char* WINDOW_TITLE = "SDL";

lTexture background;
lTexture foo;

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
            
            if (!IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG)) {
                logErrorAndExit("imageloading", IMG_GetError());
                success = false;
            }
        }
    }
    return success;
}

bool loadMedia()
{
    //Loading success flag
    bool success = true;

    //Load Foo' texture
    if( !foo.loadFromFile( "foo.png" ) )
    {
        printf( "Failed to load Foo' texture image!\n" );
        success = false;
    }
    
    //Load background texture
    if( background.loadFromFile( "background.png" ) )
    {
        printf( "Failed to load background texture image!\n" );
        success = false;
    }

    return success;
}

void close() {
    background.free();
    foo.free();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
}

int main(int argc, char* argv[])
{
    if(!init())
        cout << "SDL could not be initialised!";
    if (!loadMedia())
        cout << "images could not be loaded!";
    SDL_Event e;
    bool quit = false;
    while (quit == false) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) quit = true;
        }
        
        //clear screen
        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(renderer);
        
        background.render(0, 0);
        foo.render(240, 190);
        
        SDL_RenderPresent(renderer);
    }
    close();
    return 0;
}
