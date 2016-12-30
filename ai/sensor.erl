-module(sensor).

-compile(export_all).

-include("records.hrl").


new(Cortex) ->
  spawn(?MODULE, loop, [#sensor{cortex=Cortex}]).


loop(S=#sensor{cortex=Cortex}) ->
  receive
    {Cortex, next, Ref} ->
      Cortex ! {self(), sensor, Ref, syobon:get_map()},
      loop(S);

    {Cortex, terminate} -> exit(0)
  end.


new_rng(Cortex, DataCount) ->
  spawn(?MODULE, loop_rng, [#sensor{cortex=Cortex, data_len=DataCount}]).


loop_rng(#sensor{cortex=Cortex, data_len=0}) ->
  Cortex ! {self(), get_time},
  ok;

loop_rng(S=#sensor{cortex=Cortex, data_len=DataCount}) ->
  receive
    {Cortex, next, Ref} ->
      Cortex ! {self(), sensor, Ref, [rand:uniform() || _ <- lists:seq(1, 400)]},
      loop_rng(S#sensor{data_len=DataCount - 1});

    {Cortex, terminate} -> exit(0)
  end.
