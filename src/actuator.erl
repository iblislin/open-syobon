-module(actuator).

-compile(export_all).

-include("records.hrl").


new(Cortex, Key) ->
  spawn(?MODULE, loop, [#actuator{key=Key, cortex=Cortex}]).


loop(A=#actuator{key=Key, cortex=Cortex}) ->
  Input =
    receive
      {Cortex, terminate} ->
        error_logger:info_msg("actuator stop signal"),
        exit(ok);
      {Cortex, X} -> X
    end,

  case Input >= 0 of
    true -> syobon:key(Key);
    false -> release
  end,

  loop(A).


new_pts(Cortex) ->
  spawn(?MODULE, loop_pts, [#actuator{cortex=Cortex}]).


loop_pts(A=#actuator{cortex=Cortex}) ->
  receive
    {Cortex, terminate} ->
      ok;
    {Cortex, Output} ->
      %% io:format("Ouput val ~p~n", [Output]),
      loop_pts(A)
  end.
