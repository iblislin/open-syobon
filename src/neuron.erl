-module(neuron).

-compile(export_all).

-import(error_logger, [info_msg/2]).


%% new -> Pid.
%% VL -> VectorLength
new(VL, {out, O}, {layer_order, LO}) ->
  R = fun() -> rand:uniform() - 0.5 end,
  W = [R() || _ <- lists:seq(1, VL)],
  spawn(?MODULE, loop, [W, O, LO]).


%% W -> Weights
%% C -> Computing function
%% A -> Activation function
loop(W, O, LO) ->
  C = fun lnalg:dot/2,
  A = fun math:tanh/1,

  InputSize = length(W),
  Input = collect(array:new(InputSize), InputSize),

  info_msg('Neuro Weights ~p~n', [W]),
  Result = A(C(Input, W)),

  case O of
    [] -> info_msg("Output Node[~p]: ~p~n", [LO, Result]);
    _ -> [Next ! {input, LO, Result} || Next <- O]
  end,

  loop(W, O, LO).

%% collecting the input
collect(Arr, 0) -> array:to_list(Arr);
collect(Arr, Count) ->
  receive
    {input, Num, Val} ->
      collect(array:set(Num - 1, Val, Arr), Count - 1);
    _ -> error_logger:info_msg("Weird input")
  end.
