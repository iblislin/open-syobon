-module(player).

-compile(export_all).


start(Count) ->
  syobon:syobon_init(),
  Score = new_population(Count),
  syobon:syobon_deinit(),
  Score.


new_population(Count) -> new_population(Count, []).

new_population(0, Acc) -> Acc;

new_population(Count, Acc) ->
  Layers = [rand:uniform(20) || _ <- lists:seq(1, rand:uniform(5))],

  error_logger:info_msg("new net: ~p~n", [Layers]),

  syobon:syobon_main(),  %% play!
  Cortex = neuron_net:new(Layers),
  ok = syobon:wait_game_end(),

  Cortex ! {self(), terminate},
  neuron_net:sync(),

  new_population(Count - 1, [{Cortex, syobon:get_fitness()}|Acc]).


play(Population) -> play(Population, []).

play([], Acc) -> Acc;

play(_Population=[Cortex|T], Acc) ->
  syobon:syobon_main(),
  play(T, [{Cortex, syobon:get_fitness()}|Acc]).
