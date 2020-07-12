FLAGS =  -Wall -O3 -std=c++17 -lGLEW -lGL -lstdc++fs $(shell pkg-config sdl2 --cflags --libs)
IMGUI_FLAGS   =  -Wall -lGLEW -DIMGUI_IMPL_OPENGL_LOADER_GLEW `sdl2-config --cflags`

all: msg exe clean run

msg:
		@echo
		@echo 'Compiling starts on '
		@date
		@echo

exe: resources/imgui/imgui.o resources/code/lodepng.o resources/code/perlin.o rttnw.o utils.o
		g++ -o exe resources/code/main.cc *.o resources/imgui/*.o resources/code/*.o       ${FLAGS}

resources/imgui/imgui.o: resources/imgui/*.cc
		g++ -c -o resources/imgui/imgui_impl_sdl.o resources/imgui/imgui_impl_sdl.cc         ${IMGUI_FLAGS}
		g++ -c -o resources/imgui/imgui_impl_opengl3.o resources/imgui/imgui_impl_opengl3.cc ${IMGUI_FLAGS}
		g++ -c -o resources/imgui/imgui.o resources/imgui/imgui.cc                           ${IMGUI_FLAGS}
		g++ -c -o resources/imgui/imgui_demo.o resources/imgui/imgui_demo.cc                 ${IMGUI_FLAGS}
		g++ -c -o resources/imgui/imgui_draw.o resources/imgui/imgui_draw.cc                 ${IMGUI_FLAGS}
		g++ -c -o resources/imgui/imgui_widgets.o resources/imgui/imgui_widgets.cc           ${IMGUI_FLAGS}
		@echo


utils.o: resources/code/rttnw.h resources/code/rttnw_utils.cc
		g++ -c -o utils.o resources/code/rttnw_utils.cc               ${FLAGS}

rttnw.o: resources/code/rttnw.h resources/code/rttnw.cc
		g++ -c -o rttnw.o resources/code/rttnw.cc                  ${FLAGS}

resources/code/debug.o: resources/code/debug.cc
		g++ -c -o resources/code/debug.o resources/code/debug.cc                        ${FLAGS}

resources/code/lodepng.o: resources/code/lodepng.h resources/code/lodepng.cc
		g++ -c -o resources/code/lodepng.o resources/code/lodepng.cc                    ${FLAGS}

resources/code/perlin.o: resources/code/perlin.h resources/code/perlin.cc
		g++ -c -o resources/code/perlin.o resources/code/perlin.cc                      ${FLAGS}

clean_all:
	rm resources/imgui/*.o resources/code/lodepng.o resources/code/perlin.o *.o

clean:
		@echo
		@echo 'Compiling ends on '
		@date
		@echo
		@rm *.o
		@echo 'executable size:'
		@stat --printf "%s bytes\n" exe
		@echo

run:
		@./exe
