-module(actuator).

-compile(export_all).

-include("records.hrl").


new(Cortex, Key) ->
  spawn(?MODULE, loop, [#actuator{key=Key, cortex=Cortex}]).


loop(A=#actuator{key=Key, cortex=Cortex}) ->
  Input =
    receive
      {Cortex, terminate} -> exit(ok);
      {Cortex, X} -> X
    end,

  case Input >= 0 of
    true -> syobon:key(Key);
    false -> release
  end,

  loop(A).
