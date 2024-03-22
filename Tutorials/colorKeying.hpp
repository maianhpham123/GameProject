//
//  colorKeying.hpp
//  MyPseudoGame
//
//  Created by mac on 3/22/24.
//

#ifndef colorKeying_hpp
#define colorKeying_hpp

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>

using namespace std;

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

class lTexture {
public:
    lTexture () {
        //initialise the variables
        texture = NULL;
        width = 0;
        height = 0;
    }
    
    ~lTexture() {
        free();
    }
    
    SDL_Texture* loadFromFile(string path) {
        free();
        SDL_Surface* loadedSurface = IMG_Load(path.c_str());
        if (loadedSurface == NULL)
            cout << "image could not be loaded! Error: " << IMG_GetError();
        
        else {
            SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));
            
            texture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
            if (texture == NULL)
                cout << "image could not be textured! Error: " << SDL_GetError();
            else {
                width = loadedSurface->w;
                height = loadedSurface->h;
            }
            SDL_FreeSurface(loadedSurface);
        }
        return texture;
    }
    
    void free() {
        SDL_DestroyTexture(texture);
        texture = NULL;
    }
    
    void render(int x, int y) {
        SDL_Rect rect = {x, y, width, height};
        SDL_RenderCopy(renderer, texture, NULL, &rect);
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

#endif /* colorKeying_hpp */
