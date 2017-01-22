.SUFFIXES: .erl .beam


CXXFLAGS+=	-std=c++11 -I/usr/local/include -I/opt/local/include/ \
		-DDEBUG
LDFLAGS+=	-L/usr/local/lib \
		-L/opt/local/lib/ \
		-lpthread -lm \
		`sdl-config --libs` \
		-lSDL_gfx -lSDL_image -lSDL_mixer -lSDL_ttf \
		`pkg-config --libs UnitTest++`

ERLCFLAGS=	+native

OBJS=		main.o loadg.o DxLib.o Stage.o Player.o json/jsoncpp.o
TESTS_OBJS=	tests/Main.o tests/TestGameConfig.o \
		json/jsoncpp.o \
		tests/TestStage.o Stage.o \
		tests/TestPlayer.o Player.o

all: SyobonAction

erl_ai: syobon_nif.so syobon.beam lnalg.beam player.beam neuron.beam \
	neuron_net.beam cortex.beam sensor.beam actuator.beam \
	benchmark.beam collector.beam

SyobonAction: ${OBJS}
	${CXX} ${CXXFLAGS} ${OBJS} -o SyobonAction ${LDFLAGS}

main.o: main.cpp main.h GameConfig.h

loadg.o: loadg.cpp

DxLib.o: DxLib.cpp DxLib.h GameConfig.h

Stage.o: Stage.cpp Stage.h

clean:
	rm -fv *.o
	rm -fv SyobonAction
	rm -fv syobon_nif.so
	rm -fv *.beam
	rm -fv tests/*.o
	rm -fv tests/Main
	rm -fv *.core

tests/Main: ${TESTS_OBJS}

test: tests/Main
	./tests/Main

syobon_nif.so: ${OBJS}
	${CXX} ${CXXFLAGS} -o syobon_nif.so -fPIC -shared main.cpp \
		loadg.cpp DxLib.cpp Stage.cpp json/jsoncpp.cpp  \
		-DERL_AI \
		-I /usr/local/lib/erlang/erts-8.2/include/ \
		lm -lpthread -lSDL_gfx -lSDL_image -lSDL_mixer -lSDL_ttf \
		`sdl-config --libs`
