-module(benchmark).

-compile(export_all).


ffnn_test(Layers) ->
  Ref = make_ref(),
  Cortex = neuron_net:new_ffnn(Layers),
  Cortex ! {self(), Ref, start_sensor},
  cortex:sync(Cortex, Ref).
