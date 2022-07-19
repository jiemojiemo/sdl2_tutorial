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
#include <sstream>

using namespace std;

int main() {
    bool quit = false;
    SDL_Event event;
    const int window_width = 640;
    const int window_height = 480;
    int x = 288;
    int y = 208;

    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG);

    SDL_Window *window = SDL_CreateWindow("SDL2 Keyboard/Mouse events",
                                          SDL_WINDOWPOS_UNDEFINED,
                                          SDL_WINDOWPOS_UNDEFINED,
                                          window_width,
                                          window_height,
                                          0);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_Surface *image = IMG_Load("/Users/user/Downloads/spaceship.png");
    if (image == nullptr) {
        cerr << "load image failed\n";
        return -1;
    }
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, image);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    for (; !quit;) {
        while (SDL_PollEvent(&event)) { // poll until all events are handled!// decide what to do with this event.
            switch (event.type) {
                case SDL_QUIT: {
                    quit = true;
                    break;
                }
                case SDL_KEYDOWN: {
                    switch (event.key.keysym.sym) {
                        case SDLK_LEFT:
                            --x;
                            break;
                        case SDLK_RIGHT:
                            ++x;
                            break;
                        case SDLK_UP:
                            --y;
                            break;
                        case SDLK_DOWN:
                            ++y;
                            break;
                    }
                }
                case SDL_MOUSEBUTTONDOWN: {
                    switch (event.button.button) {
                        case SDL_BUTTON_LEFT:
                            SDL_ShowSimpleMessageBox(0, "Mouse", "Left button was pressed!", window);
                            break;
                        case SDL_BUTTON_RIGHT:
                            SDL_ShowSimpleMessageBox(0, "Mouse", "Left button was pressed!", window);
                            break;
                        default:
                            SDL_ShowSimpleMessageBox(0, "Mouse", "Some other button was pressed!", window);
                            break;
                    }
                }

                case SDL_MOUSEMOTION: {
                    int mouse_y = event.motion.y;
                    int mouse_x = event.motion.x;

                    std::stringstream ss;
                    ss << "X: " << mouse_x << " Y: " << mouse_y;

                    SDL_SetWindowTitle(window, ss.str().c_str());
                    break;
                }
            }
        }

        SDL_Rect dstrect = {x, y, 64, 64};
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, texture, nullptr, &dstrect);
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
    return 0;
}