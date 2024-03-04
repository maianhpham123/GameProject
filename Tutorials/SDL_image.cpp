#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
using namespace std;

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const char* WINDOW_TITLE = "Hello World!";

void logErrorAndExit(const char* msg, const char* error)
{
    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "%s: %s", msg, error);
    SDL_Quit();
}

//create window
SDL_Window* InitSDL(int SCREEN_WIDTH, int SCREEN_HEIGHT, const char* WINDOW_TITLE)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        logErrorAndExit("SDL_Init", SDL_GetError());
    
    SDL_Window *window = SDL_CreateWindow (WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN)

    //fullscreen
    //SDL_Window *window = SDL_CreateWindow (WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_FULLSCREEN_DESKTOP);

    if (window == nullptr) logErrorAndExit("CreateWindow", SDL_GetError());

    if (!IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG))
        logErrorAndExit("SDL_image error:", IMG_GetError());
    
    return window;
}

//create render
SDL_Renderer* createRenderer(SDL_Window* window)
{
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    
    //khi chay trong may ao
    // renderer = SDL_CreateSoftwareRenderer(SDL_GetWindowSurface(window));

    if (renderer == nullptr) logErrorAndExit("CreateRenderer", SDL_GetError());

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);

    return renderer;
}

void quitSDL(SDL_Window* window, SDL_Renderer* renderer)
{
    IMG_Quit();

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void renderTexture(SDL_Texture *texture, int x, int y, SDL_Renderer* renderer)
{
    SDL_Rect dest;

    dest.x = x;
    dest.y = y;
    SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);
    SDL_RenderCopy(renderer, texture, NULL, &dest);
}



int main(argc, char *argv[])
{

}