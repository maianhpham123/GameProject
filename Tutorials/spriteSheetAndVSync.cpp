//
//  spriteSheetAndVSync.cpp
//  MyPseudoGame
//
//  Created by mac on 3/26/24.
//

#include "spriteSheetAndVSync.hpp"

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 800;
const char* WINDOW_TITLE = "SDL2";

const int WALKING_ANIMATION_FRAMES = 4;
SDL_Rect SpriteClips[ WALKING_ANIMATION_FRAMES ];
Texture SpriteSheetTexture;

bool init() {
    bool success = true;
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        logErrorAndExit("SDLinitialisation", SDL_GetError());
        success = false;
    }
    else {
        window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (window == NULL) {
            logErrorAndExit("CreateWindow", SDL_GetError());
            success = false;
        }
        
        else {
            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
            if (renderer == NULL) {
                logErrorAndExit("CreateRenderer", SDL_GetError());
            }
            
            else {
                SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
                
                if (!IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG)) {
                    logErrorAndExit("ImageLoading", IMG_GetError());
                    success = false;
                }
            }
        }
    }
    return success;
}

bool loadMedia() {
    bool success = true;
    
    if (!SpriteSheetTexture.loadFromFile("foo.png")) {
        logErrorAndExit("spriteuploading", SDL_GetError());
        success = false;
    }
    
    else {
        SpriteClips[ 0 ].x =   0;
        SpriteClips[ 0 ].y =   0;
        SpriteClips[ 0 ].w =  64;
        SpriteClips[ 0 ].h = 205;

        SpriteClips[ 1 ].x =  64;
        SpriteClips[ 1 ].y =   0;
        SpriteClips[ 1 ].w =  64;
        SpriteClips[ 1 ].h = 205;
        
        SpriteClips[ 2 ].x = 128;
        SpriteClips[ 2 ].y =   0;
        SpriteClips[ 2 ].w =  64;
        SpriteClips[ 2 ].h = 205;

        SpriteClips[ 3 ].x = 192;
        SpriteClips[ 3 ].y =   0;
        SpriteClips[ 3 ].w =  64;
        SpriteClips[ 3 ].h = 205;
    }
    return success;
}

void close()
{
    //Free loaded images
    SpriteSheetTexture.free();

    //Destroy window
    SDL_DestroyRenderer( renderer );
    SDL_DestroyWindow( window );
    window = NULL;
    renderer = NULL;

    //Quit SDL subsystems
    IMG_Quit();
    SDL_Quit();
}

int main(int argc, char* argv[])
{
    if (!init()) {
        cout << "failed to initialise!";
    }
    
    if (!loadMedia()) {
        cout << "failed to load media!";
    }
    
    SDL_Event e;
    bool quit = false;
    int frame = 0;
    while (quit == false) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) quit = true;
        }
        
        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(renderer); //reset the color of the renderer
        
        SDL_Rect* currentClip = &SpriteClips[ frame / 4 ];
        SpriteSheetTexture.render( ( SCREEN_WIDTH - currentClip->w ) / 2, ( SCREEN_HEIGHT - currentClip->h ) / 2, currentClip );
        
        SDL_RenderPresent(renderer);
        ++frame;
        
        if( frame / 4 >= WALKING_ANIMATION_FRAMES )
        {
            frame = 0;
        }
    }
    
    close();
    return 0;
}
