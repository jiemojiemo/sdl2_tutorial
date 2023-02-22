//
// Created by user on 1/11/23.
//

#if defined(__cplusplus)
extern "C" {
#endif

#include <SDL.h>
#include <libyuv.h>

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

SDL_Texture *loadAndScaleYUV420PTexture(const std::string &file_path,
                                        SDL_Renderer *renderer,
                                        int src_width, int src_height,
                                        int dst_width, int dst_height) {
    auto file_data = loadFile(file_path);
    auto *yuv_data = file_data.data();
    auto *y_plane = yuv_data;
    size_t y_stride = src_width;
    auto *u_plane = yuv_data + (src_width * src_height);
    size_t u_stride = src_width / 2;
    auto *v_plane = u_plane + (src_width * src_height) / 4;
    size_t v_stride = src_width / 2;

    SDL_Texture *texture = SDL_CreateTexture(renderer,
                                             SDL_PIXELFORMAT_IYUV,
                                             SDL_TEXTUREACCESS_STATIC,
                                             dst_width,
                                             dst_height);

    int aligned_dst_width = (src_width + 1) & ~1;
    auto scale_data_size = dst_width * aligned_dst_width * 3 / 2;
    std::vector<uint8_t> scale_data(scale_data_size);

    auto *dst_y_plane = scale_data.data();
    size_t dst_y_stride = aligned_dst_width;
    auto *dst_u_plane = dst_y_plane + (aligned_dst_width * dst_height);
    size_t dst_u_stride = aligned_dst_width / 2;
    auto *dst_v_plane = dst_u_plane + (aligned_dst_width * dst_height) / 4;
    size_t dst_v_stride = aligned_dst_width / 2;

    libyuv::I420Scale(y_plane, y_stride, u_plane, u_stride, v_plane, v_stride,
                      src_width, src_height, dst_y_plane, dst_y_stride,
                      dst_u_plane, dst_u_stride, dst_v_plane, dst_v_stride,
                      aligned_dst_width, dst_height,
                      libyuv::FilterMode::kFilterLinear);

    SDL_Rect rect;
    rect.x = 0;
    rect.y = 0;
    rect.w = dst_width;
    rect.h = dst_height;
    SDL_UpdateYUVTexture(texture,
                         &rect,
                         dst_y_plane, dst_y_stride,
                         dst_u_plane, dst_u_stride,
                         dst_v_plane, dst_v_stride);

    return texture;
}

SDL_Texture *loadAndCropRotateYUV420PTexture(const std::string &file_path,
                                             SDL_Renderer *renderer,
                                             int src_width, int src_height,
                                             int dst_width, int dst_height,
                                             int crop_x, int crop_y,
                                             int crop_width, int crop_height,
                                             int rotate) {
    auto file_data = loadFile(file_path);
    auto *yuv_data = file_data.data();

    SDL_Texture *texture = SDL_CreateTexture(renderer,
                                             SDL_PIXELFORMAT_IYUV,
                                             SDL_TEXTUREACCESS_STATIC,
                                             crop_width,
                                             crop_height);

    int aligned_dst_width = (crop_width + 1) & ~1;
    auto output_data_size = crop_height * aligned_dst_width * 3 / 2;
    std::vector<uint8_t> output_data(output_data_size);

    auto *dst_y_plane = output_data.data();
    size_t dst_y_stride = aligned_dst_width;
    auto *dst_u_plane = dst_y_plane + (aligned_dst_width * crop_height);
    size_t dst_u_stride = aligned_dst_width / 2;
    auto *dst_v_plane = dst_u_plane + (aligned_dst_width * crop_height) / 4;
    size_t dst_v_stride = aligned_dst_width / 2;

    libyuv::ConvertToI420(yuv_data, file_data.size(),
                          dst_y_plane, dst_y_stride,
                          dst_u_plane, dst_u_stride, dst_v_plane, dst_v_stride,
                          crop_x,
                          crop_y,
                          src_width,
                          src_height,
                          crop_width,
                          crop_height,
                          libyuv::RotationMode(rotate),
                          libyuv::FOURCC_I420);

    SDL_Rect rect;
    rect.x = 0;
    rect.y = 0;
    rect.w = aligned_dst_width;
    rect.h = crop_height;
    SDL_UpdateYUVTexture(texture,
                         &rect,
                         dst_y_plane, dst_y_stride,
                         dst_u_plane, dst_u_stride,
                         dst_v_plane, dst_v_stride);

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

    int dst_width = 300;
    int dst_height = 100;
    int crop_x = 50;
    int crop_y = 80;
    int crop_width = 200;
    int crop_height = 300;
    int rotate = 0;
    SDL_Texture *texture = loadAndCropRotateYUV420PTexture(yuv_file_path, renderer,
                                                           yuv_width, yuv_height,
                                                           dst_width, dst_height,
                                                           crop_x, crop_y,
                                                           crop_width, crop_height,
                                                           rotate);

    for (; !quit;) {
        SDL_WaitEvent(&event);

        switch (event.type) {
        case SDL_QUIT: {
            quit = true;
            break;
        }
        }

        SDL_Rect rect;
        rect.x = 0;
        rect.y = 0;
        rect.w = crop_width;
        rect.h = crop_height;
        SDL_RenderCopy(renderer, texture, nullptr, &rect);
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}