//
// Created by user on 1/11/23.
//

#if defined(__cplusplus)
extern "C" {
#endif

#include <SDL.h>

#if defined(__cplusplus)
};
#endif

#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

std::vector<uint8_t> loadFile(const std::string &file_path) {
    std::ifstream in(file_path, std::ios::in | std::ios::binary);
    std::vector<uint8_t> file_data;
    if (in) {
        in.seekg(0, std::ios::end);
        file_data.resize(in.tellg());
        in.seekg(0, std::ios::beg);
        in.read((char *)(file_data.data()), file_data.size());
        in.close();
    }
    return file_data;
}

SDL_Texture *loadYUV420PTexture(const std::string &file_path,
                                SDL_Renderer *renderer,
                                int width, int height) {
    auto file_data = loadFile(file_path);
    auto *yuv_data = file_data.data();

    auto *y_plane = yuv_data;
    size_t y_stride = width;

    auto *u_plane = yuv_data + (width * height);
    size_t u_stride = width / 2;

    auto *v_plane = u_plane + (width * height) / 4;
    size_t v_stride = width / 2;

    SDL_Texture *texture = SDL_CreateTexture(renderer,
                                             SDL_PIXELFORMAT_IYUV,
                                             SDL_TEXTUREACCESS_STATIC,
                                             width,
                                             height);

    SDL_UpdateYUVTexture(texture,
                         nullptr,
                         y_plane, y_stride,
                         u_plane, u_stride,
                         v_plane, v_stride);

    return texture;
}

int main(int argc, char *argv[]) {
    bool quit = false;
    SDL_Event event;

    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window *window = SDL_CreateWindow("My SDL Empty window",
                                          SDL_WINDOWPOS_UNDEFINED,
                                          SDL_WINDOWPOS_UNDEFINED,
                                          640, 480, 0);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);

    int yuv_width = 700;
    int yuv_height = 700;
    auto yuv_file_path = "/Users/user/Downloads/yuv_viewer_test/rainbow-yuv420p.yuv";

    SDL_Texture *texture = loadYUV420PTexture(yuv_file_path, renderer,
                                              yuv_width, yuv_height);

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
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}