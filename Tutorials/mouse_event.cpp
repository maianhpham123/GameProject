#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include "file.h" //from ProjectsToSmallFiles
#include "graphics.h" //from ProjectsToSmallFiles

using namespace std;

//lay toa do chuot trong di chuyen
int main(int argc, char* argv[])
{
    Graphics graphics;
    graphics.init();
    
    //how to draw a rectangle in SDL2
    SDL_Rect rect;
    rect.x = 100;
    rect.y = 100;
    rect.h = 100;
    rect.w = 100;
    SDL_SetRenderDrawColor(graphics.renderer, 255, 255, 255, 0);
    SDL_RenderFillRect(graphics.renderer, &rect);
    SDL_RenderPresent(graphics.renderer);
    
    SDL_Event e;
    int x, y;
    while(true) {
        SDL_GetMouseState(&x, &y);
        cerr << x << ", " << y << endl;
        // cerr << ((x > 100 && y > 100 && x < 200 && y < 200) ? "In\n" : "Out\n");
        //cerr: là lệnh in ra cho màn hình, gần giống với cout
        //cerr là luồng output dành riêng cho báo lỗi và debug (err la từ error)
        //đổ lập tức nội dung ra màn hìn và chỉ đổ ra màn hình
        
        SDL_PollEvent(&e);
        switch(e.type) {
            case SDL_QUIT:
                exit(0);
                break;
                
                //cach lay event nhap tha chuot
            case SDL_MOUSEBUTTONDOWN:
                cerr << "down at (" << x << ", " << y << ")\n";
            case SDL_MOUSEBUTTONUP:
                cerr << "up at (" << x << ", " << y << ")\n";
        }
        SDL_Delay(100);
    }
    graphics.quit();
    return 0;
}
