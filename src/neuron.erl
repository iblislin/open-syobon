-module(neuron).

-compile(export_all).

-include("records.hrl").

-import(error_logger, [info_msg/2]).


%% new -> {Pid, #neuron}. create new process
%% VL -> VectorLength
%% Type can be `neuron`, `sensor`
new(Cortex, VecLen, LayOrd) ->
  R = fun() -> rand:uniform() - 0.5 end,
  W = [R() || _ <- lists:seq(1, VecLen)],
  Neuron = #neuron{weights=W, vec_len=VecLen, layer_order=LayOrd,
                   cortex=Cortex},
  {spawn(?MODULE, loop, [Neuron]), Neuron}.


%% W -> Weights
%% C -> Computing function
%% A -> Activation function
loop(N=#neuron{weights=W,
               activate=A,
               compute=C,
               cortex=Cortex,
               layer_order=LO}) ->
  Input =
    receive
      {Cortex, terminate} -> exit(ok);
      {Cortex, X} -> X
    end,

  Result = A(C(Input, W)),
  Cortex ! {LO, Result},

  loop(N).
