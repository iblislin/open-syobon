-module(syobon).

-on_load(init/0).

-compile([export_all]).


init() ->
  erlang:load_nif("./syobon_nif", 0),
  shell_default:cd("..").


syobon_main() ->
  "NIF not load".


test() ->
  error.


key(_K) ->
  error.


send_key(K) ->
  case K of
    left -> key(1);
    right -> key(2);
    down -> key(3);
    up -> key(4)
  end.
