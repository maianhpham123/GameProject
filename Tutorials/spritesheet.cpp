//
//  spritesheet.cpp
//  MyPseudoGame
//
//  Created by mac on 3/25/24.
//
#include "spritesheet.hpp"
using namespace std;

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 800;
const char* WINDOW_TITLE = "SPRITESHEET";

SDL_Rect SpriteClips[ 4 ];
lTexture SpriteSheetTexture;

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
            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_ACCELERATED);
            
            if (renderer == NULL) {
                logErrorAndExit("CreateRenderer", SDL_GetError());
                success = false;
            }
            
            else {
                SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
                if (!IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG)) {
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
    if (!SpriteSheetTexture.loadFromFile("dots.png")) {
        logErrorAndExit("dotsLoading", IMG_GetError());
        success = false;
    }
    
    else {
        //Set top left sprite
        SpriteClips[ 0 ].x =   0;
        SpriteClips[ 0 ].y =   0;
        SpriteClips[ 0 ].w = 100;
        SpriteClips[ 0 ].h = 100;

        //Set top right sprite
        SpriteClips[ 1 ].x = 100;
        SpriteClips[ 1 ].y =   0;
        SpriteClips[ 1 ].w = 100;
        SpriteClips[ 1 ].h = 100;
        
        //Set bottom left sprite
        SpriteClips[ 2 ].x =   0;
        SpriteClips[ 2 ].y = 100;
        SpriteClips[ 2 ].w = 100;
        SpriteClips[ 2 ].h = 100;

        //Set bottom right sprite
        SpriteClips[ 3 ].x = 100;
        SpriteClips[ 3 ].y = 100;
        SpriteClips[ 3 ].w = 100;
        SpriteClips[ 3 ].h = 100;
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
    //Start up SDL and create window
    if(!init() )
    {
        cout << "Failed to initialize!";
    }
    else
    {
        //Load media
        if( !loadMedia() )
        {
            cout << "Failed to load media!";
        }
        else
        {
            //Main loop flag
            bool quit = false;

            //Event handler
            SDL_Event e;

            //While application is running
            while( !quit )
            {
                //Handle events on queue
                while( SDL_PollEvent( &e ) != 0 )
                {
                    //User requests quit
                    if( e.type == SDL_QUIT )
                    {
                        quit = true;
                    }
                }

                //Clear screen
                SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );
                SDL_RenderClear( renderer );

                //Render top left sprite
                SpriteSheetTexture.render( 0, 0, &SpriteClips[ 0 ] );

                //Render top right sprite
                SpriteSheetTexture.render( SCREEN_WIDTH - SpriteClips[ 1 ].w, 0, &SpriteClips[ 1 ] );

                //Render bottom left sprite
                SpriteSheetTexture.render( 0, SCREEN_HEIGHT - SpriteClips[ 2 ].h, &SpriteClips[ 2 ] );

                //Render bottom right sprite
                SpriteSheetTexture.render( SCREEN_WIDTH - SpriteClips[ 3 ].w, SCREEN_HEIGHT - SpriteClips[ 3 ].h, &SpriteClips[ 3 ] );

                //Update screen
                SDL_RenderPresent( renderer );
            }
        }
    }

    //Free resources and close SDL
    close();

    return 0;
}



