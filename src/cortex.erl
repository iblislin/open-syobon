-module(cortex).

-compile(export_all).

-include("records.hrl").

%% cortex goals:
%%
%% - maintain all PIDs
%% - maintain all message passing


new() ->
  spawn(?MODULE, loop, [#cortex{}]).


loop(C=#cortex{sensor=Sensor}) ->
  receive
    terminate -> ok;
    {From, set, nn, Val} ->
      NewC = C#cortex{net=Val},
      From ! ok,
      loop(NewC);

    {From, set, sensor, Val} ->
      NewC = C#cortex{sensor=Val},
      From ! ok,
      loop(NewC);

    {From, set, actuator, Val} ->
      NewC = C#cortex{actuator=Val},
      From ! ok,
      loop(NewC);

    {From, get} ->
      From ! C,
      loop(C);

    {Sensor, Input} ->
      %% NeuronLayer = hd(C#cortex.net),
      %% [ N ! Input || N <- NeuronLayer ],
      Sensor ! {self(), ok},
      loop(C)
  end.



