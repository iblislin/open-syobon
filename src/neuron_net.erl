-module(neuron_net).

-compile(export_all).


%% Layers list: e.g [1, 3, 1]
%% Acc -> [
%%  {Pid, In_ids, Out_ids}
%% ]
new(Layers) -> new(lists:reverse(Layers), [], []).

new([], _, Acc) -> Acc;

new([L|T], OutPids, Acc) ->
  VL =
  case T of  %% vector length
    [] -> 1;  %% map size
    _ -> hd(T)
  end,
  Pids = [neuron:new(VL, {out, OutPids}, {layer_order, I}) || I <- lists:seq(1, L)],
  Layer = [{neuron, P, {out, OutPids}} || P <- Pids],
  new(T, Pids, [Layer|Acc]).
