-module(neuron).

-compile(export_all).

-include("records.hrl").

-import(error_logger, [info_msg/2]).


%% new -> {Pid, #neuron}. create new process
%% VL -> VectorLength
%% Type can be `neuron`, `sensor`
new(Cortex, VecLen, LayOrd) ->
  W = rand_weights(VecLen),
  Neuron = #neuron{weights=W, vec_len=VecLen, layer_order=LayOrd,
                   cortex=Cortex},
  {spawn(?MODULE, loop, [Neuron]), Neuron}.


new(N=#neuron{}) ->
  {spawn(?MODULE, loop, [N]), N}.


%% W -> Weights
%% C -> Computing function
%% A -> Activation function
loop(N=#neuron{weights=W,
               activate=A,
               compute=C,
               cortex=Cortex,
               layer_order=LO}) ->
  receive
    {Cortex, terminate} -> exit(ok);

    {From, ch_weight} ->
      NewW = rand_weights(length(W)),
      From ! {self(), ok},
      loop(N#neuron{weights=NewW});

    {Cortex, Input} ->
      Result = A(C(Input, W)),
      Cortex ! {neuron, LO, Result},
      loop(N)
  end.


rand_weights(Len) ->
  R = fun() -> rand:uniform() - 0.5 end,
  [R() || _ <- lists:seq(1, Len)].
