#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>

using namespace std;

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 800;
const char* WINDOW_TITLE = "SDL";

SDL_Window* window = NULL;
SDL_Surface* screenSurface = NULL;
SDL_Surface* currentSurface = NULL;

//enum: shorthand to do symbolic constants instead of having to do const int KEY_PRESS_SURFACE_DEFAULT = 0. They default to start counting at 0 and go up by one for each numeration

enum keyPresses {
    KEY_PRESS_SURFACE_DEFAULT,
    KEY_PRESS_SURFACE_UP,
    KEY_PRESS_SURFACE_DOWN,
    KEY_PRESS_SURFACE_LEFT,
    KEY_PRESS_SURFACE_RIGHT,
    KEY_PRESS_SURFACE_TOTAL
};

// initialise the surface that match the key
SDL_Surface* keyPressesSurface [KEY_PRESS_SURFACE_TOTAL];

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
                screenSurface = SDL_GetWindowSurface(window);
            }
        }
    return success;
}

//to load images
SDL_Surface* image (string path) {
    SDL_Surface* loadedSurface = SDL_LoadBMP(path.c_str());
    if(loadedSurface == NULL)
        cout << "image couldnt be loaded! Error: " << SDL_GetError();
    
    SDL_Surface* optimisedSurface = SDL_ConvertSurface(loadedSurface, screenSurface->format, 0);
    if (optimisedSurface == NULL) cout << "image could not be optimised!";
    SDL_FreeSurface(loadedSurface);
    
    return optimisedSurface;
}

bool loadMedia () {
    bool success = true;
    keyPressesSurface[KEY_PRESS_SURFACE_DEFAULT] = image("press.bmp");
    if(keyPressesSurface[KEY_PRESS_SURFACE_DEFAULT] == NULL) {
        cout << "image could not be loaded!";
        success = false;
    }

    keyPressesSurface[KEY_PRESS_SURFACE_UP] = image("up.bmp");
    if(keyPressesSurface[KEY_PRESS_SURFACE_UP] == NULL) {
        cout << "image could not be loaded!";
        success = false;
    }
    
    keyPressesSurface[KEY_PRESS_SURFACE_DOWN] = image("down.bmp");
    if(keyPressesSurface[KEY_PRESS_SURFACE_DOWN] == NULL) {
        cout << "image could not be loaded!";
        success = false;
    }
    
    keyPressesSurface[KEY_PRESS_SURFACE_LEFT] = image("left.bmp");
    if(keyPressesSurface[KEY_PRESS_SURFACE_LEFT] == NULL) {
        cout << "image could not be loaded!";
        success = false;
    }
    
    keyPressesSurface[KEY_PRESS_SURFACE_RIGHT] = image("right.bmp");
    if(keyPressesSurface[KEY_PRESS_SURFACE_RIGHT] == NULL) {
        cout << "image could not be loaded!";
        success = false;
    }
    
    return success;
}

void close () {
    //Deallocate surfaces
    for( int i = 0; i < KEY_PRESS_SURFACE_TOTAL; ++i )
    {
        SDL_FreeSurface( keyPressesSurface[ i ] );
        keyPressesSurface[ i ] = NULL;
    }

    //Destroy window
    SDL_DestroyWindow( window );
    window = NULL;

    //Quit SDL subsystems
    SDL_Quit();
}

int main(int argc, char* argv[])
{
    if(!init())
        cout << "SDL could not be initialised!";
    else {
        if (!loadMedia())
            cout << "image could not be loaded!";
        
        currentSurface = keyPressesSurface[KEY_PRESS_SURFACE_DEFAULT];
        SDL_Event e;
        bool quit = false;
        while(quit == false) {
            while(SDL_PollEvent(&e)) {
                if (e.type == SDL_QUIT) quit = true;
                
                else if (e.type == SDL_KEYDOWN) {
                    switch (e.key.keysym.sym) {
                        case SDLK_UP:
                            currentSurface = keyPressesSurface[KEY_PRESS_SURFACE_UP];
                            break;
                        
                        case SDLK_DOWN:
                            currentSurface = keyPressesSurface[KEY_PRESS_SURFACE_DOWN];
                            break;
                        
                        case SDLK_LEFT:
                            currentSurface = keyPressesSurface[KEY_PRESS_SURFACE_LEFT];
                            break;
                            
                        case SDLK_RIGHT:
                            currentSurface = keyPressesSurface[KEY_PRESS_SURFACE_RIGHT];
                            break;
                            
                        default:
                            currentSurface = keyPressesSurface[KEY_PRESS_SURFACE_DEFAULT];
                            break;
                    }
                }
            }
            
            SDL_BlitScaled(currentSurface, NULL, screenSurface, NULL);
            SDL_UpdateWindowSurface(window);
        }
    }
    close();
    return 0;
}
