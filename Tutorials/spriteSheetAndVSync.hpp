//
//  spriteSheetAndVSync.hpp
//  MyPseudoGame
//
//  Created by mac on 3/26/24.
//

#ifndef spriteSheetAndVSync_hpp
#define spriteSheetAndVSync_hpp

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
using namespace std;

SDL_Window* window;
SDL_Renderer* renderer;

void logErrorAndExit(const char* msg, const char* error) {
    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "%s : %s", msg, error);
    SDL_Quit();
}

class Texture {
public:
    Texture() {
        texture = NULL;
        width = 0;
        height = 0;
    }
    
    ~Texture () {
        free();
    }
    
    void free() {
        SDL_DestroyTexture(texture);
        texture = NULL;
        width = 0;
        height = 0;
    }
    
    SDL_Texture* loadFromFile (string path) {
        free();
        SDL_Surface* loadedSurface = IMG_Load(path.c_str());
        if (loadedSurface == NULL) logErrorAndExit("imageLoading", IMG_GetError());
        else {
            SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0xFF, 0xFF, 0xFF));
            
            texture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
            
            if (texture == NULL) logErrorAndExit("textureLoading", SDL_GetError());
            else {
                // take the dimensions;
                width = loadedSurface->w;
                height = loadedSurface->h;
            }
            
            SDL_FreeSurface(loadedSurface);
        }
        return texture;
    }
    
    void setColor(Uint8 red, Uint8 green, Uint8 blue) {
        SDL_SetTextureColorMod(texture, red, green, blue);
    }
    
    void setBlendMode(SDL_BlendMode blending) {
        SDL_SetTextureBlendMode(texture, blending);
    }
    
    void setAlpha (Uint8 alpha) {
        SDL_SetTextureAlphaMod(texture, alpha);
    }
    
    void render(int x, int y, SDL_Rect* clips) {
        SDL_Rect renderQuad = {x,y,width,height};
        if (clips != NULL) {
            renderQuad.w = clips->w;
            renderQuad.h = clips->h;
        }
        SDL_RenderCopy(renderer, texture, clips, &renderQuad);
    }
    
    int getWidth() {
        return width;
    }
    int getHeight() {
        return height;
    }
    
private:
    SDL_Texture* texture;
    int width;
    int height;
};
#endif /* spriteSheetAndVSync_hpp */
