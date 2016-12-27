-module(sensor).

-compile(export_all).

-include("records.hrl").


new(Cortex) ->
  spawn(?MODULE, loop, [#sensor{cortex=Cortex}]).


loop(S=#sensor{cortex=Cortex}) ->
  ok = syobon:check_run_state(),
  Cortex ! {self(), syobon:get_map()},

  receive
    {Cortex, ok} -> loop(S);
    {Cortex, terminate} -> ok
  end.
