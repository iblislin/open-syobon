SyobonAction:main.o loadg.o DxLib.o
	clang++ main.o loadg.o DxLib.o -o SyobonAction `sdl-config --libs` \
	    -lm -lpthread -lSDL_gfx -lSDL_image -lSDL_mixer -lSDL_ttf -lzmq

main.o:main.cpp
	clang++ -c main.cpp -I /usr/local/include/

loadg.o:loadg.cpp
	clang++ -c loadg.cpp -I /usr/local/include/

DxLib.o:DxLib.cpp
	clang++ -c DxLib.cpp -I /usr/local/include/

clean:
	rm -fv *.o
