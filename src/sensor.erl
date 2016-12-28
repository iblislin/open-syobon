-module(sensor).

-compile(export_all).

-include("records.hrl").


new(Cortex) ->
  spawn(?MODULE, loop, [#sensor{cortex=Cortex}]).


loop(S=#sensor{cortex=Cortex, enabled=true}) ->
  Cortex ! {self(), sensor, syobon:get_map()},

  receive
    {Cortex, disable} ->
      error_logger:info_msg("sensor receive stop signal"),
      loop(S#sensor{enabled=false});

    {Cortex, ok} -> loop(S)
  end;


loop(S=#sensor{cortex=Cortex, enabled=false}) ->
  receive
    {Cortex, enable} ->
      error_logger:info_msg("sensor receive start signal"),
      loop(S#sensor{enabled=true})
  end.


new_rng(Cortex, DataCount) ->
  spawn(?MODULE, loop_rng, [#sensor{cortex=Cortex, data_len=DataCount}]).


loop_rng(S=#sensor{cortex=Cortex, enabled=true, data_len=0}) ->
  Cortex ! {self(), stop_time, erlang:timestamp()},
  loop_rng(S#sensor{enabled=false});

loop_rng(S=#sensor{cortex=Cortex, enabled=true, data_len=DataCount}) ->
  Cortex ! {self(), sensor, [rand:uniform() || _ <- lists:seq(1, 400)]},

  receive
    {Cortex, disable} ->
      loop_rng(S#sensor{enabled=false});

    {Cortex, ok} -> loop_rng(S#sensor{data_len=DataCount - 1})
  end;


loop_rng(S=#sensor{cortex=Cortex, enabled=false}) ->
  receive
    {Cortex, enable} ->
      Cortex ! {self(), start_time, erlang:timestamp()},
      loop_rng(S#sensor{enabled=true})
  end.
