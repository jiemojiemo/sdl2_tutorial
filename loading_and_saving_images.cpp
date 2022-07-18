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

int main()
{
    IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);

    SDL_Surface* image = IMG_Load("/Users/user/Downloads/sdl_image-pict3159-1024x768.jpeg");
    IMG_SavePNG(image, "output.png");

    SDL_FreeSurface(image);
    IMG_Quit();
    return 0;
}