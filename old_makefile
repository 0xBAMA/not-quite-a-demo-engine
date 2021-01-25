FLAGS =  -Wall -O3 -std=c++17 -lGL -lstdc++fs $(shell pkg-config sdl2 --cflags --libs) -Wno-deprecated -lGL -ldl `sdl2-config --libs`
IMGUI_FLAGS   =  -Wall -DIMGUI_IMPL_OPENGL_LOADER_GL3W `sdl2-config --cflags` 


all: msg exe clean run

msg:
		@echo
		@echo 'Compiling starts on '
		@date
		@echo

exe: resources/ocornut_imgui/imgui.o resources/VAT/mmccutchen_BigInt/*.o resources/lodev_lodePNG/lodepng.o resources/perlin/perlin.o engine.o utils.o
		g++ -o exe resources/engine_code/main.cc *.o resources/lodev_lodePNG/lodepng.o resources/ocornut_imgui/*.o resources/VAT/mmccutchen_BigInt/*.o resources/perlin/perlin.o    ${FLAGS}

resources/ocornut_imgui/imgui.o: resources/ocornut_imgui/*.cc
		g++ -c -o resources/ocornut_imgui/imgui_impl_sdl.o resources/ocornut_imgui/imgui_impl_sdl.cc         ${IMGUI_FLAGS}
		g++ -c -o resources/ocornut_imgui/imgui_impl_opengl3.o resources/ocornut_imgui/imgui_impl_opengl3.cc ${IMGUI_FLAGS}
		g++ -c -o resources/ocornut_imgui/imgui.o resources/ocornut_imgui/imgui.cc                           ${IMGUI_FLAGS}
		g++ -c -o resources/ocornut_imgui/imgui_demo.o resources/ocornut_imgui/imgui_demo.cc                 ${IMGUI_FLAGS}
		g++ -c -o resources/ocornut_imgui/imgui_draw.o resources/ocornut_imgui/imgui_draw.cc                 ${IMGUI_FLAGS}
		g++ -c -o resources/ocornut_imgui/imgui_widgets.o resources/ocornut_imgui/imgui_widgets.cc           ${IMGUI_FLAGS}
		g++ -c -o resources/ocornut_imgui/imgui_tables.o resources/ocornut_imgui/imgui_tables.cc             ${IMGUI_FLAGS}
		cc -c -o resources/ocornut_imgui/imgui_gl3w.o resources/ocornut_imgui/imgui_gl3w.c                  ${IMGUI_FLAGS}
		@echo

resources/VAT/mmccutchen_BigInt/*.o:
		g++ -c -o resources/VAT/mmccutchen_BigInt/BigUnsigned.o -O2 -Wno-deprecated             resources/VAT/mmccutchen_BigInt/BigUnsigned.cc
		g++ -c -o resources/VAT/mmccutchen_BigInt/BigInteger.o -O2 -Wno-deprecated              resources/VAT/mmccutchen_BigInt/BigInteger.cc
		g++ -c -o resources/VAT/mmccutchen_BigInt/BigIntegerAlgorithms.o -O2 -Wno-deprecated    resources/VAT/mmccutchen_BigInt/BigIntegerAlgorithms.cc
		g++ -c -o resources/VAT/mmccutchen_BigInt/BigUnsignedInABase.o -O2 -Wno-deprecated      resources/VAT/mmccutchen_BigInt/BigUnsignedInABase.cc
		g++ -c -o resources/VAT/mmccutchen_BigInt/BigIntegerUtils.o -O2 -Wno-deprecated         resources/VAT/mmccutchen_BigInt/BigIntegerUtils.cc
		@echo

utils.o: resources/engine_code/engine.h resources/engine_code/engine_utils.cc
		g++ -c -o utils.o resources/engine_code/engine_utils.cc                         ${FLAGS}

engine.o: resources/engine_code/engine.h resources/engine_code/engine.cc
		g++ -c -o engine.o resources/engine_code/engine.cc                              ${FLAGS}

resources/lodev_lodePNG/lodepng.o: resources/lodev_lodePNG/lodepng.h resources/lodev_lodePNG/lodepng.cc
		g++ -c -o resources/lodev_lodePNG/lodepng.o resources/lodev_lodePNG/lodepng.cc  ${FLAGS}

resources/perlin/perlin.o: resources/perlin/perlin.h resources/perlin/perlin.cc
		g++ -c -o resources/perlin/perlin.o resources/perlin/perlin.cc                  ${FLAGS}

clean_all:
	rm resources/ocornut_imgui/*.o resources/VAT/mmccutchen_BigInt/*.o resources/lodev_lodePNG/lodepng.o resources/perlin/perlin.o

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
