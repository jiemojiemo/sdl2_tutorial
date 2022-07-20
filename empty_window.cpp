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
    bool quit = false;
    SDL_Event event;

    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window *screen = SDL_CreateWindow("My SDL Empty window",
                                          SDL_WINDOWPOS_UNDEFINED,
                                          SDL_WINDOWPOS_UNDEFINED,
                                          640, 480, 0);
    for (; !quit;) {
        SDL_WaitEvent(&event);

        switch (event.type) {
        case SDL_QUIT: {
            quit = true;
            break;
        }
        }
    }

    SDL_Quit();
    return 0;
}