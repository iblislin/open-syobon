.SUFFIXES: .erl .beam

CXXFLAGS+=	-std=c++11
ERLCFLAGS=	+native

all: SyobonAction

erl_ai: syobon_nif.so syobon.beam lnalg.beam player.beam neuron.beam \
     neuron_net.beam cortex.beam sensor.beam actuator.beam \
     benchmark.beam collector.beam

SyobonAction: main.o loadg.o DxLib.o
	clang++ ${CXXFLAGS} main.o loadg.o DxLib.o -o SyobonAction `sdl-config --libs` \
	    -lm -lpthread -lSDL_gfx -lSDL_image -lSDL_mixer -lSDL_ttf

main.o: main.cpp main.h
	clang++ ${CXXFLAGS} -c main.cpp -I /usr/local/include/

loadg.o: loadg.cpp
	clang++ ${CXXFLAGS} -c loadg.cpp -I /usr/local/include/

DxLib.o: DxLib.cpp DxLib.h
	clang++ ${CXXFLAGS} -c DxLib.cpp -I /usr/local/include/

clean:
	rm -fv *.o
	rm -fv SyobonAction
	rm -fv syobon_nif.so
	rm -fv *.beam

syobon_nif.so: main.cpp loadg.cpp DxLib.cpp
	clang++ ${CXXFLAGS} -g -o syobon_nif.so -fPIC -shared main.cpp \
	    loadg.cpp DxLib.cpp \
	    -DPP \
	    -I /usr/lib/erlang/erts-8.1.1/include/ \
	    -lm -lpthread -lSDL_gfx -lSDL_image -lSDL_mixer -lSDL_ttf \
	    `sdl-config --libs`

.erl.beam:
	erlc ${ERLCFLAGS} $<
