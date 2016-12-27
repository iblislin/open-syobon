-module(syobon).

-on_load(init/0).

-compile([export_all]).


init() ->
  erlang:load_nif("./syobon_nif", 0).


syobon_main() ->
  "NIF not load".


syobon_init() ->
  error.


syobon_deinit() ->
  error.


test() ->
  error.


key(_K) ->
  error.


send_key(K) ->
  case K of
    left -> key(1);
    right -> key(2);
    down -> key(3);
    up -> key(4);
    _ -> drop
  end.


get_map() ->
  error.


get_fitness() ->
  error.


wait_game_init() ->
  receive
    game_start -> ok
  end.


wait_game_end() ->
  receive
    game_end -> ok
  end.
