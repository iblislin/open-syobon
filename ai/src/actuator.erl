-module(actuator).

-compile(export_all).

-include("records.hrl").


new(Cortex) ->
  spawn(?MODULE, loop, [#actuator{cortex=Cortex}]).


loop(A=#actuator{cortex=Cortex}) ->
  receive
    {input, _Ref, Val} ->
      Cortex ! {self(), fin, erlang:timestamp()},
      [syobon:key(Key) || {Key, V} <- lists:zip([1, 2, 3, 4], Val), V >= 0],
      loop(A);

    {Cortex, terminate} ->
      error_logger:info_msg("actuator stop signal"),
      ok
  end.


new_pts(Cortex) ->
  spawn(?MODULE, loop_pts, [#actuator{cortex=Cortex}]).


loop_pts(A=#actuator{cortex=Cortex}) ->
  receive
    {input, _Ref, Val} ->
      Cortex ! {self(), fin, erlang:timestamp()},
      io:format("Output: ~p~n", [Val]),
      loop_pts(A);

    {Cortex, terminate} -> ok
  end.
