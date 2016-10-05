SyobonAction:main.o loadg.o DxLib.o
	clang++ main.o loadg.o DxLib.o -o SyobonAction `sdl-config --libs` -lm -lSDL_gfx -lSDL_image -lSDL_mixer -lSDL_ttf

main.o:main.cpp
	clang++ -c main.cpp -I /opt/local/include/

loadg.o:loadg.cpp
	clang++ -c loadg.cpp -I /opt/local/include/

DxLib.o:DxLib.cpp
	clang++ -c DxLib.cpp -I /opt/local/include/

clean:
	rm -f main.o loadg.o DxLib.o SyobonAction
