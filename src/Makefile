.SUFFIXES: .erl .beam


CXXFLAGS+=	-std=c++11 -I/usr/local/include
LDFLAGS+=	-L/usr/local/lib \
		-lpthread -lm \
		`sdl-config --libs` \
		-lSDL_gfx -lSDL_image -lSDL_mixer -lSDL_ttf \
		-lUnitTest++

ERLCFLAGS=	+native

TESTS_OBJ=	tests/Main.o tests/TestGameConfig.o

all: SyobonAction

erl_ai: syobon_nif.so syobon.beam lnalg.beam player.beam neuron.beam \
	neuron_net.beam cortex.beam sensor.beam actuator.beam \
	benchmark.beam collector.beam

SyobonAction: main.o loadg.o DxLib.o
	${CXX} ${CXXFLAGS} main.o loadg.o DxLib.o -o SyobonAction ${LDFLAGS}

main.o: main.cpp main.h GameConfig.h

loadg.o: loadg.cpp

DxLib.o: DxLib.cpp DxLib.h GameConfig.h

clean:
	rm -fv *.o
	rm -fv SyobonAction
	rm -fv syobon_nif.so
	rm -fv *.beam
	rm -fv tests/*.o
	rm -fv tests/Main
	rm -fv *.core

tests/Main: ${TESTS_OBJ}

test: tests/Main
	./tests/Main

syobon_nif.so: main.cpp loadg.cpp DxLib.cpp
	${CXX} ${CXXFLAGS} -o syobon_nif.so -fPIC -shared main.cpp \
	    loadg.cpp DxLib.cpp \
	    -DPP \
	    -I /usr/lib/erlang/erts-8.1.1/include/ \
	    -lm -lpthread -lSDL_gfx -lSDL_image -lSDL_mixer -lSDL_ttf \
	    `sdl-config --libs`
