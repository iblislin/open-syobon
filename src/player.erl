-module(player).

-compile(export_all).


start() ->
  syobon:syobon_init(),
  Population = new_population(2),
  Score = play(Population),
  syobon:syobon_deinit(),
  Score.


new_population(Count) -> new_population(Count, []).

new_population(0, Acc) -> Acc;

new_population(Count, Acc) ->
  Layers = [rand:uniform(20) || _ <- lists:seq(1, rand:uniform(5))],

  error_logger:info_msg("new net: ~p~n", [Layers]),

  Cortex = neuron_net:new(Layers),
  new_population(Count - 1, [Cortex|Acc]).


play(Population) -> play(Population, []).

play([], Acc) -> Acc;

play(_Population=[Cortex|T], Acc) ->
  syobon:syobon_main(),
  play(T, [{Cortex, syobon:get_fitness()}|Acc]).
