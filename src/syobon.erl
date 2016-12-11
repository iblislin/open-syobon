-module(syobon).

-on_load(init/0).

-compile([export_all]).


init() ->
  erlang:load_nif("./syobon_nif", 0),
  shell_default:cd("..").


syobon_main() ->
  "NIF not load".


test() ->
  err.
