-module(cortex).

-compile(export_all).

-include("records.hrl").

%% cortex goals:
%%
%% - maintain all PIDs
%% - maintain all message passing


new() ->
  spawn(?MODULE, loop, [#cortex{}]).


res_ok(To, Ref) ->  %% response ok
  To ! {self(), Ref, ok}.


loop(C=#cortex{sensor=Sensor, actuators=Actuators, net=Net}) ->
  receive
    {Sensor, sensor, Input} ->
      Actions = feed_forward(Input, Net),

      [Actuator ! {self(), Act} ||
        {Act, Actuator} <- lists:zip(Actions, Actuators)],

      Sensor ! {self(), ok},

      loop(C);

    {From, Ref, terminate} ->
      Msg = {self(), terminate},
      Sensor ! Msg,
      %% [Actuator ! Msg || Actuator <- Actuators],
      %% [[ N ! Msg || {N, _} <- Layer] || Layer <- Net],
      res_ok(From, Ref),
      loop(C);

    {From, Ref, start_sensor} ->
      Sensor ! {self(), enable},
      res_ok(From, Ref),
      loop(C);

    {From, Ref, stop_sensor} ->
      Sensor ! {self(), disable},
      res_ok(From, Ref),
      loop(C);

    {From, Ref, stop_actuator} ->
      Msg = {self(), terminate},
      [Actuator ! Msg || Actuator <- Actuators],
      res_ok(From, Ref),
      loop(C);

    {From, Ref, set, net, Val} ->
      NewC = C#cortex{net=Val},
      res_ok(From, Ref),
      loop(NewC);

    {From, Ref, set, neuron_num, Val} ->
      NewC = C#cortex{neuron_num=Val},
      res_ok(From, Ref),
      loop(NewC);

    {From, Ref, set, sensor, Val} ->
      NewC = C#cortex{sensor=Val},
      res_ok(From, Ref),
      loop(NewC);

    {From, Ref, set, actuators, Val} ->
      NewC = C#cortex{actuators=Val},
      res_ok(From, Ref),
      loop(NewC);

    {From, Ref, get, net} ->
      From ! {self(), Ref, Net, C#cortex.neuron_num},
      loop(C);

    {From, Ref, get} ->
      From ! {self(), Ref, C},
      loop(C);

    {From, Ref, nn_mutate} ->
      neuron_net:mutate(Net, rand:uniform(C#cortex.neuron_num)),
      res_ok(From, Ref),
      loop(C);

    {Sensor, start_time, Time} ->
      NewC = C#cortex{start_time=Time},
      loop(NewC);

    {Sensor, stop_time, Time} ->
      NewC = C#cortex{stop_time=Time},
      T0 = C#cortex.start_time,
      error_logger:info_msg("time: ~p s~n",
                            [timer:now_diff(Time, T0)/1000000]),
      loop(NewC)
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
    {neuron, Order, Val} ->
      collect(array:set(Order - 1, Val, Arr), Count - 1)
  end.


sync(Cortex, Ref) ->
  receive
    {Cortex, Ref, ok} -> ok
  end.
