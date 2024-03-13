#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h> //đường dẫn thư viện setup trong cấu hình project
#include "file.h" // được tìm tại thư mục mã nguồn của project
#include "graphics.h"

using namespace std;

void waitUntilKeyPressed()
{
    SDL_Event e;
    while (true) {
        if (SDL_PollEvent(&e) != 0 && (e.type == SDL_KEYDOWN || e.type == SDL_QUIT))
            return;
        SDL_Delay(100);
    }
}

int main(int argc, char *argv[])
{
    Graphics graphics;
    graphics.init();
    
    SDL_Texture* background = graphics.loadTexture("hogwarts.png");
    graphics.prepareScene(background);
    
    graphics.presentScene();
    waitUntilKeyPressed();
    
    SDL_DestroyTexture(background);
    background = NULL;
    
    graphics.quit();
    return 0;
}
