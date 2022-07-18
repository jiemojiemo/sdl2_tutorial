//
// Created by user on 7/18/22.
//
#if defined(__cplusplus)
extern "C" {
#endif
#include <SDL.h>
#include <SDL_image.h>
#if defined(__cplusplus)
};
#endif

#include <iostream>
using namespace std;

int main() {
    bool quit = false;

    SDL_Event event;

    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_JPG);

    SDL_Window *window = SDL_CreateWindow("My SDL Empty window",
                                          SDL_WINDOWPOS_UNDEFINED,
                                          SDL_WINDOWPOS_UNDEFINED,
                                          640, 480, 0);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_Surface *image = IMG_Load("/Users/user/Downloads/sdl_image-pict3159-1024x768.jpeg");
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
        SDL_RenderCopy(renderer, texture, nullptr, nullptr);
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyTexture(texture);
    SDL_FreeSurface(image);
    SDL_DestroyRenderer(renderer);
    IMG_Quit();
    SDL_Quit();
    return 0;
}