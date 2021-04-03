cmake_minimum_required(VERSION 3.16)

project(Voraldo VERSION 1.2 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_FLAGS "-std=c++17 -lstdc++fs -O4")
set(CMAKE_REQUIRED_FLAGS -lstdc++fs)

# this makes SDL2 work
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

find_package(SDL2 REQUIRED)
add_library(sdl2 INTERFACE)
target_include_directories(sdl2
    INTERFACE
        ${SDL2_INCLUDE_DIR}
)
target_link_libraries(sdl2
    INTERFACE
        ${SDL2_LIBRARY}
        ${CMAKE_DL_LIBS}
)

# this makes OpenGL work
set(OpenGL_GL_PREFERENCE "GLVND")
find_package(OpenGL REQUIRED)
add_library(opengl INTERFACE)
target_link_libraries(opengl INTERFACE OpenGL::GL)


# FastNoise2 
add_subdirectory(${PROJECT_SOURCE_DIR}/resources/FastNoise2)

# this is for ImGUI
add_library(imgui
  resources/ocornut_imgui/imgui_impl_sdl.cc
  resources/ocornut_imgui/imgui_impl_opengl3.cc
  resources/ocornut_imgui/imgui.cc
  resources/ocornut_imgui/imgui_demo.cc
  resources/ocornut_imgui/imgui_draw.cc
  resources/ocornut_imgui/imgui_widgets.cc
  resources/ocornut_imgui/imgui_tables.cc  
  resources/ocornut_imgui/imgui_gl3w.c
  resources/ocornut_imgui/TextEditor.cpp)

target_link_libraries(imgui PUBLIC sdl2 opengl)

target_compile_options(imgui PUBLIC -I/usr/include/SDL2)
target_compile_definitions(imgui PUBLIC -D IMGUI_IMPL_OPENGL_LOADER_GL3W -D_REENTRANT)

# this is the bigint library to suppor the VAT code
add_library(BigInt
  resources/VAT/mmccutchen_BigInt/BigUnsigned.cc
  resources/VAT/mmccutchen_BigInt/BigInteger.cc
  resources/VAT/mmccutchen_BigInt/BigIntegerAlgorithms.cc
  resources/VAT/mmccutchen_BigInt/BigUnsignedInABase.cc
  resources/VAT/mmccutchen_BigInt/BigIntegerUtils.cc)

target_compile_options(BigInt PUBLIC -Wno-deprecated)

add_library(CompilerFlags INTERFACE)
target_compile_options(CompilerFlags INTERFACE -Wall -O3 -std=c++17 -lGL -lstdc++fs -lSDL2 -ldl)

# this builds the final executable
add_executable(exe
  resources/engine_code/main.cc
  resources/engine_code/gpu_data.cc
  resources/engine_code/engine.cc
  resources/engine_code/engine_utils.cc
  resources/perlin/perlin.cc
  resources/lodev_lodePNG/lodepng.cc)

target_link_libraries(exe PUBLIC imgui BigInt opengl sdl2 stdc++fs FastNoise CompilerFlags)
