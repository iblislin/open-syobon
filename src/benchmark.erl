-module(benchmark).

-compile(export_all).

-import(neuron, [rand_weights/1]).


ffnn_test(Layers) ->
  Ref = make_ref(),
  Cortex = neuron_net:new_ffnn(Layers),
  Cortex ! {self(), Ref, start_sensor},
  cortex:sync(Cortex, Ref).


ffnn_serial(Layers) ->
  NN = ffnn_serial_new(Layers),
  %% compute
  StartTime = erlang:timestamp(),
  Input = rand_weights(400),
  ok = ffnn_serial_loop(Input, NN, 10000),
  StopTime = erlang:timestamp(),
  timer:now_diff(StopTime, StartTime)/1000000.

ffnn_serial_new(Layers) ->
  Sensor = rand_weights(400),
  Net = ffnn_serial_new_net(Layers, []),
  Actuator = rand_weights(50),
  [[Sensor]] ++ Net ++ [[Actuator]].

ffnn_serial_new_net(0, Acc) -> Acc;
ffnn_serial_new_net(1, Acc) ->
  ffnn_serial_new_net(0, [[rand_weights(1) || _ <- lists:seq(1, 50)] | Acc]);
ffnn_serial_new_net(Count, Acc) ->
  ffnn_serial_new_net(Count - 1, [[rand_weights(50) || _ <- lists:seq(1, 50)] | Acc]).


ffnn_serial_loop(_, _, 0) -> ok;
ffnn_serial_loop(Input, NN, DataCount) ->
  ok = ffnn_serial_forward(Input, NN),
  ffnn_serial_loop(Input, NN, DataCount - 1).

ffnn_serial_forward(_, []) -> ok;
ffnn_serial_forward(Input, [N|T]) ->
  ffnn_serial_forward([math:tanh(lnalg:dot(X, Input)) || X <- N], T).
