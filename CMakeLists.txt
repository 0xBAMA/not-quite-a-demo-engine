cmake_minimum_required(VERSION 3.16)

project(Voraldo VERSION 1.2 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)


# includes cmake/FindSDL2.cmake
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})

add_library(imgui
  resources/ocornut_imgui/imgui_impl_sdl.cc
  resources/ocornut_imgui/imgui_impl_opengl3.cc
  resources/ocornut_imgui/imgui.cc
  resources/ocornut_imgui/imgui_demo.cc
  resources/ocornut_imgui/imgui_draw.cc
  resources/ocornut_imgui/imgui_widgets.cc
  resources/ocornut_imgui/imgui_tables.cc  
  resources/ocornut_imgui/imgui_gl3w.c)

# target_compile_options(imgui PUBLIC -ldl `sdl2-config --libs`)
target_compile_definitions(imgui PUBLIC -D IMGUI_IMPL_OPENGL_LOADER_GL3W)

add_library(BigInt
  resources/VAT/mmccutchen_BigInt/BigUnsigned.cc
  resources/VAT/mmccutchen_BigInt/BigInteger.cc
  resources/VAT/mmccutchen_BigInt/BigIntegerAlgorithms.cc
  resources/VAT/mmccutchen_BigInt/BigUnsignedInABase.cc
  resources/VAT/mmccutchen_BigInt/BigIntegerUtils.cc)

target_compile_options(BigInt PUBLIC -Wno-deprecated)

add_library(CompilerFlags INTERFACE)
target_compile_options(CompilerFlags INTERFACE -Wall -O3 -std=c++17 -lGL -lstdc++fs -lSDL2 -Wno-deprecated)

add_executable(exe
  resources/engine_code/main.cc
  resources/engine_code/gpu_data.cc
  resources/engine_code/engine.cc
  resources/engine_code/engine_utils.cc
  resources/perlin/perlin.cc
  resources/lodev_lodePNG/lodepng.cc)

target_link_libraries(exe PUBLIC imgui BigInt CompilerFlags ${SDL2_LIBRARY} ${CMAKE_DL_LIBS})





# add_executable(${PROJECT_NAME} resources/engine_code/main.cc)

