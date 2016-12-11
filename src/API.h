#include <iostream>
#include <thread>
#include <unistd.h>

#include <zmq.hpp>

#include "DxLib.h"

#ifndef API_HEADER
#define API_HEADER

void _APIService() {
    sleep(5);

    while (1) {
        sleep(1);
        SDL_Event sdlevent;
        sdlevent.type = SDL_KEYDOWN;
        sdlevent.key.keysym.sym = KEY_INPUT_RIGHT;

        SDL_PushEvent(&sdlevent);

        sleep(1);

        sdlevent.type = SDL_KEYUP;
        sdlevent.key.keysym.sym = KEY_INPUT_RIGHT;

        SDL_PushEvent(&sdlevent);
    }
}

std::thread* APIThread() {
    std::thread* service = new std::thread(_APIService);

    std::cout << "API Service started \n";
    return service;
}

#endif
