-module(cortex).

-compile(export_all).

-include("records.hrl").

%% cortex goals:
%%
%% - maintain all PIDs
%% - maintain all message passing


new() ->
  spawn(?MODULE, loop, [#cortex{}]).


loop(C=#cortex{sensor=Sensor, actuators=Actuators, net=Net}) ->
  receive
    {From, terminate} ->
      Msg = {self(), terminate},
      Sensor ! Msg,
      %% [Actuator ! Msg || Actuator <- Actuators],
      %% [[ N ! Msg || {N, _} <- Layer] || Layer <- Net],
      From ! ok,
      loop(C);

    {From, set, net, Val} ->
      NewC = C#cortex{net=Val},
      From ! ok,
      loop(NewC);

    {From, set, neuron_num, Val} ->
      NewC = C#cortex{neuron_num=Val},
      From ! ok,
      loop(NewC);

    {From, set, sensor, Val} ->
      NewC = C#cortex{sensor=Val},
      From ! ok,
      loop(NewC);

    {From, set, actuators, Val} ->
      NewC = C#cortex{actuators=Val},
      From ! ok,
      loop(NewC);

    {From, get} ->
      From ! C,
      loop(C);

    {From, nn_mutate} ->
      neuron_net:mutate(Net, rand:uniform(C#cortex.neuron_num)),
      From ! ok,
      loop(C);

    {Sensor, Input} ->
      Actions = feed_forward(Input, Net),

      [ Actuator ! {self(), Act} ||
        {Act, Actuator} <- lists:zip(Actions, Actuators)],

      Sensor ! {self(), ok},

      loop(C)
  end.


feed_forward(Input, []) -> Input;

feed_forward(Input, Layers) ->
      NeuronLayer = hd(Layers),
      [Pid ! {self(), Input} || {Pid, _} <- NeuronLayer],
      feed_forward(collect(length(NeuronLayer)), tl(Layers)).


collect(L) -> collect(array:new(L), L).

collect(Arr, 0) -> array:to_list(Arr);

collect(Arr, Count) ->
  receive
    {Order, Val} ->
      collect(array:set(Order - 1, Val, Arr), Count - 1);
    _ -> skip
  end.
