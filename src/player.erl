-module(player).

-compile(export_all).


start(Count) ->
  syobon:syobon_init(),
  {Cortexes, Fits} = new_population(Count),
  Parents = selection(lists:zip(Cortexes, Fits)),
  Childs = new_generation(Parents),
  error_logger:info_msg("child ~n~p", [Childs]),

  syobon:syobon_deinit(),

  {{parents, Parents}, {children, Childs}}.


new_population(Count) -> new_population(Count, [], []).

new_population(0, Cortexes, Fits) -> {Cortexes, Fits};

new_population(Count, Cortexes, Fits) ->
  Layers = [rand:uniform(20) || _ <- lists:seq(1, rand:uniform(5))],

  error_logger:info_msg("new net: ~p~n", [Layers]),

  Cortex = neuron_net:new(Layers),
  Fit = play(Cortex),

  new_population(Count - 1, [Cortex|Cortexes], [Fit|Fits]).


play(Cortex) ->
  Ref = make_ref(),

  syobon:syobon_main(),  %% play!

  ok = syobon:wait_game_init(),
  Cortex ! {self(), Ref, start_sensor},
  cortex:sync(Cortex, Ref),
  error_logger:info_msg("sensor start"),

  ok = syobon:wait_game_end(),
  error_logger:info_msg("gname end"),
  Cortex ! {self(), Ref, stop_sensor},
  error_logger:info_msg("wait for sensor stop"),
  cortex:sync(Cortex, Ref),
  error_logger:info_msg("sensor stop"),

  syobon:get_fitness().


selection(Score) ->
  L = lists:sort(fun({_, A}, {_, B}) -> A =< B end, Score),
  Size = length(L) div 2,
  {_, Parents} = lists:split(Size, L),
  Parents.


new_generation(Parents) -> new_generation(Parents, [], []).

new_generation([], Childs, Fits) -> {Childs, Fits};

new_generation([{P, _}|T], Childs, Fits) ->
  Ref = make_ref(),
  C = neuron_net:copy(P),
  C ! {self(), Ref, nn_mutate},
  cortex:sync(C, Ref),
  error_logger:info_msg("new child ~p from ~p~n", [C, P]),
  Fit = play(C),
  new_generation(T, [C|Childs], [Fit|Fits]).
