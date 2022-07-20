//
// Created by user on 7/17/22.
//

#if defined(__cplusplus)
extern "C" {
#endif

#include <SDL.h>

#if defined(__cplusplus)
};
#endif

#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
    bool quit = false;
    SDL_Event event;

    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window *window = SDL_CreateWindow("My SDL Empty window",
                                          SDL_WINDOWPOS_UNDEFINED,
                                          SDL_WINDOWPOS_UNDEFINED,
                                          640, 480, 0);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_Surface *image = SDL_LoadBMP("/Users/user/Downloads/image.bmp");
    if (image == nullptr) {
        cerr << "SDL_LoadBMP failed\n";
        return -1;
    }
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, image);

    for (; !quit;) {
        SDL_WaitEvent(&event);

        switch (event.type) {
        case SDL_QUIT: {
            quit = true;
            break;
        }
        }
        SDL_Rect rect = {5, 5, 300, 200};
        SDL_RenderCopy(renderer, texture, nullptr, &rect);
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyTexture(texture);
    SDL_FreeSurface(image);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    return 0;
}