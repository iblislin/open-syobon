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


loop(C=#cortex{sensor=Sensor, actuator=Actuator, net=Net,
               layer_num=LayerNum, collectors=Collectors,
               enabled=Enabled}) ->
  receive
    {Sensor, sensor, Ref, Input} ->
      Layer1 = hd(Net),
      [N ! {input, Ref, Input} || {N, _} <- Layer1],
      loop(C);

    {Actuator, fin, Time} ->
      Ref = make_ref(),
      case Enabled of
        true -> ok;
        false -> loop(C)
      end,
      Sensor ! {self(), next, Ref},
      [Collector ! {self(), push_ref, Ref} || Collector <- Collectors],
      NewC = C#cortex{stop_time=Time},
      loop(NewC);

    {From, Ref, set, layer_num, Val} ->
      NewC = C#cortex{layer_num=Val},
      res_ok(From, Ref),
      loop(NewC);

    {From, Ref, set, collectors, Val} ->
      NewC = C#cortex{collectors=Val},
      [[Pid ! {self(), set, collector, Collector} ||
        {Pid, _} <- Layer] ||
       {Layer, Collector} <- lists:zip(Net, Val)],
      res_ok(From, Ref),
      loop(NewC);

    {From, Ref, start} ->
      NewC = C#cortex{start_time=erlang:timestamp(), enabled=true},

      Refs = [make_ref() || _ <- lists:seq(1, LayerNum)],
      [Sensor ! {self(), next, R} || R <- Refs],
      [Collector ! {self(), push_ref, R} || Collector <- Collectors, R <- Refs],

      res_ok(From, Ref),
      loop(NewC);

    {From, Ref, stop} ->
      NewC = C#cortex{enabled=false},

      %% terminate neurons
      [[ N ! {self(), terminate} || {N, _} <- L] || L <- Net],

      %% terminate collectors
      [Collector ! {self(), terminate} || Collector <- Collectors],

      %% terminate actuator
      Actuator ! {self(), terminate},

      %% terminate sensor
      Sensor ! {self(), terminate},

      res_ok(From, Ref),
      loop(NewC);

    {From, Ref, stop_sensor} ->
      Sensor ! {self(), disable},
      res_ok(From, Ref),
      loop(C);

    {From, Ref, set, net, Val} ->
      NewC = C#cortex{net=Val},
      %% TODO: link to all of neuron PIDs
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

    {From, Ref, set, actuator, Val} ->
      NewC = C#cortex{actuator=Val},
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

    {Sensor, get_time} ->
      error_logger:info_msg("time: ~p s",
                            [timer:now_diff(C#cortex.stop_time, C#cortex.start_time) / 1000000]),
      loop(C);

    {Sensor, stop_time, Time} ->
      NewC = C#cortex{stop_time=Time},
      T0 = C#cortex.start_time,
      error_logger:info_msg("time: ~p s~n",
                            [timer:now_diff(Time, T0)/1000000]),
      loop(NewC);

    {_From, terminate} ->  %% destory and none of data will be held
      exit(ok)
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
