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

int main(int argc, char *argv[]) {
    int quit = 0;
    SDL_Event event;

    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window *screen = SDL_CreateWindow("My SDL Empty window",
                                          SDL_WINDOWPOS_UNDEFINED,
                                          SDL_WINDOWPOS_UNDEFINED,
                                          640, 480, 0);

    //    SDL_Surface *image = SDL_LoadBMP("/Users/user/Downloads/image.bmp");
    //    if (image == nullptr) {
    //        return -1;
    //    }
    for (; !quit;) {
        SDL_WaitEvent(&event);

        switch (event.type) {
        case SDL_QUIT: {
            quit = 1;
            break;
        }
        }
    }

    SDL_DestroyWindow(screen);
    SDL_Quit();
    return 0;
}