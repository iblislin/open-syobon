-module(sensor).

-compile(export_all).

-include("records.hrl").


new(Cortex) ->
  spawn(?MODULE, loop, [#sensor{cortex=Cortex}]).


loop(S=#sensor{cortex=Cortex}) ->
  ok = check_hp(),
  Cortex ! {self(), syobon:get_map()},
  receive
    {Cortex, ok} -> ok
  end,

  loop(S).


check_hp() ->
  case syobon:get_hp() of
    1 -> ok;
    _ ->
      timer:sleep(300),
      check_hp()
  end.

