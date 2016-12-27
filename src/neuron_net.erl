-module(neuron_net).

-compile(export_all).

-include("records.hrl").


%% Layers list: e.g [1, 3, 1]
%% Acc -> [
%%  {Pid, In_ids, Out_ids}
%% ]
new(Layers) ->
  Cortex = cortex:new(),

  Actuators = [actuator:new(Cortex, Key) || Key <- lists:seq(1, 4)],
  Cortex ! {self(), set, actuators, Actuators},
  sync(),

  %% [4] is for the actuators,
  %% [1] is for the input layer.
  Net = new_net(Cortex, [1|Layers] ++ [4]),
  Cortex ! {self(), set, net, Net},
  sync(),

  Cortex ! {self(), set, neuron_num, lists:sum(Layers) + 5},
  sync(),

  Sensor = sensor:new(Cortex),
  Cortex ! {self(), set, sensor, Sensor},
  sync(),

  Cortex.


sync() ->
  receive
    ok -> ok
  end.


new_net(Cortex, Layers) -> new_net(Cortex, Layers, 480*420, []).

new_net(_, [], _, Acc) -> lists:reverse(Acc);

new_net(Cortex, _Layers=[H|T], VecLen, Acc) ->
  Layer = new_net_layer(Cortex, VecLen, H),
  new_net(Cortex, T, H, [Layer|Acc]).


%% create a single network layer
new_net_layer(Cortex, VecLen, Count) -> new_net_layer(Cortex, VecLen, Count, []).

new_net_layer(_, _, 0, Acc) -> lists:reverse(Acc);

new_net_layer(Cortex, VecLen, Count, Acc) ->
  Neuron = neuron:new(Cortex, VecLen, Count),
  new_net_layer(Cortex, VecLen, Count- 1, [Neuron|Acc]).


mutate(Net, 0) -> ok;

mutate(Net, Count) ->
  case mutate_ops() of
    weights ->
      LayerN = rand:uniform(length(Net)),
      Layer = lists:nth(LayerN, Net),
      {Pid, _} = lists:nth(rand:uniform(length(Layer)), Layer),
      Pid ! {self(), ch_weight},
      receive
        {Pid, ok} -> ok
      end
  end,
  mutate(Net, Count - 1).


mutate_ops() -> element(rand:uniform(1), {weights}).
