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
