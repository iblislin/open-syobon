#ifdef ERL_AI  /* enable ai or not */

#ifndef ERL_AI_H

#define ERL_AI_H
#define DISABLE_SAVE_FLAG

#include <unistd.h>
#include <iostream>
#include <string>
#include <cstdlib>

#include "erl_nif.h"

int run_state = 0;
Uint32 last_time = 0;

struct worker_args {
    ErlNifPid* caller;
};

void debug_screen() {
    setcolor(0, 0, 0);
    char c[100];

    sprintf(c, "time: %ld", stime - last_time);
    str(c, 10, 10);

    sprintf(c, "fitness: %d", fx);
    str(c, 10, 10 + 14);
}

void* worker(void* args) {
    ErlNifEnv* worker_env = enif_alloc_env();

    run_state = 1; // start the game
    zxon = 0;  // make game reinit
    // main window
    while (!CheckHitKey(KEY_INPUT_ESCAPE))
    {
        UpdateKeys();
        maint = 0;
        Mainprogram();

        if(run_state) {
            ERL_NIF_TERM msg = enif_make_atom(worker_env, "game_start");
            enif_send(NULL, ((worker_args *)args)->caller, worker_env, msg);
            run_state = 0;
        }

        // timeout rules
        Uint32 time_delta = stime - last_time;
        if (fx <= 34301 && time_delta >= 20000)
            break;
        else if (fx <= 163400 && time_delta >= 40000)
            break;
        else if (time_delta >= 70000) // global timeout
            break;

        if (maint == 3)
            break;
    }
    last_time = stime;
    run_state = 0;

    ERL_NIF_TERM msg = enif_make_atom(worker_env, "game_end");
    enif_send(NULL, ((worker_args *)args)->caller, worker_env, msg);

    enif_free_env(worker_env);
    return NULL;
}


static ERL_NIF_TERM
syobon_init(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[])
{
    DxLib_Init();
    loadg();
    SetFontSize(16);
    return enif_make_int(env, 0);
}


static ERL_NIF_TERM
syobon_deinit(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[])
{
    deinit();
    return enif_make_int(env, 0);
}


static ERL_NIF_TERM
syobon_main(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[])
{
    run_state = -1;
    ErlNifTid thread_id;
    worker_args *wargs = new worker_args;
    ErlNifPid *self_pid = new ErlNifPid;

    wargs->caller = enif_self(env, self_pid);

    enif_thread_create(
        "syobon_main_thread",
        &thread_id,
        worker,
        (void *)wargs,
        NULL);
    return enif_make_int(env, 0);
}


static ERL_NIF_TERM
test(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[])
{
    return enif_make_string(env, "Hello world!", ERL_NIF_LATIN1);
}


void _hit_key(SDLKey k){
    SDL_Event sdlevent;
    sdlevent.type = SDL_KEYDOWN;
    sdlevent.key.keysym.sym = k;

    SDL_PushEvent(&sdlevent);

    usleep(100000);

    sdlevent.type = SDL_KEYUP;
    sdlevent.key.keysym.sym = k;

    SDL_PushEvent(&sdlevent);
}


static ERL_NIF_TERM
erl_key(ErlNifEnv* env, int args, const ERL_NIF_TERM argv[])
{
    int i;
    if (!enif_get_int(env, argv[0], &i)) {
        return enif_make_badarg(env);
    }

    switch(i) {
        case 1:
            _hit_key(KEY_INPUT_LEFT);
            break;
        case 2:
            _hit_key(KEY_INPUT_RIGHT);
            break;
        case 3:
            _hit_key(KEY_INPUT_DOWN);
            break;
        case 4:
            _hit_key(KEY_INPUT_UP);
            break;
    }

    return enif_make_atom(env, "ok");
}

#define MAPSIZE 480 * 420
ERL_NIF_TERM map_buffer[MAPSIZE];

static ERL_NIF_TERM
get_map(ErlNifEnv *env, int args, const ERL_NIF_TERM argv[])
{
    SDL_LockSurface(screen);
    for (int i = 0; i < 480 * 420; i++) {
        map_buffer[i] = enif_make_uint(env, *((Uint32*)screen->pixels + i));
    }
    SDL_UnlockSurface(screen);

    return enif_make_list_from_array(env, map_buffer, 480*420);
}

static ERL_NIF_TERM
get_fitness(ErlNifEnv *env, int args, const ERL_NIF_TERM argv[])
{
    return enif_make_int(env, fx);
}

static ErlNifFunc nif_funcs[] = {
    {"syobon_init", 0, syobon_init},
    {"syobon_deinit", 0, syobon_deinit},
    {"syobon_main", 0, syobon_main},
    {"test", 0, test},
    {"key", 1, erl_key},
    {"get_map", 0, get_map},
    {"get_fitness", 0, get_fitness},
};


ERL_NIF_INIT(syobon, nif_funcs, NULL, NULL, NULL, NULL);

#endif  /* ifndef ERL_AI_H */
#endif  /* ifdef ERL_AI */
