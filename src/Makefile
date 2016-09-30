SyobonAction:main.o loadg.o DxLib.o
	clang++ main.o loadg.o DxLib.o -o SyobonAction `sdl-config --libs` -lm -lSDL_gfx -lSDL_image -lSDL_mixer -lSDL_ttf

main.o:main.cpp
	clang++ -c main.cpp -I /usr/local/include/

loadg.o:loadg.cpp
	clang++ -c loadg.cpp -I /usr/local/include/

DxLib.o:DxLib.cpp
	clang++ -c DxLib.cpp -I /usr/local/include/
