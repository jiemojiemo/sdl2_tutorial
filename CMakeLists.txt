cmake_minimum_required(VERSION 3.10)

project(sdl2_tutorial)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

if (ENABLE_ASAN)
    message(STATUS "build with ASAN")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address")
endif ()

add_executable(empty_window empty_window.cpp lsan_suppressions.cpp)
target_link_libraries(empty_window PRIVATE ${CONAN_LIBS})

add_executable(display_image display_image.cpp lsan_suppressions.cpp)
target_link_libraries(display_image PRIVATE ${CONAN_LIBS})

add_executable(loading_image_with_sdl_image loading_image_with_sdl_image.cpp)
target_link_libraries(loading_image_with_sdl_image PRIVATE ${CONAN_LIBS})

add_executable(loading_and_saving_images loading_and_saving_images.cpp)
target_link_libraries(loading_and_saving_images PRIVATE ${CONAN_LIBS})

add_executable(saving_screenshots saving_screenshots.cpp)
target_link_libraries(saving_screenshots PRIVATE ${CONAN_LIBS})

add_executable(handing_events handing_events.cpp)
target_link_libraries(handing_events PRIVATE ${CONAN_LIBS})

add_executable(display_yuv_file display_yuv_file.cpp)
target_link_libraries(display_yuv_file PRIVATE ${CONAN_LIBS})

add_executable(test test.c lsan_suppressions.cpp)
target_link_libraries(test PRIVATE ${CONAN_LIBS})
