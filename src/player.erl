-module(player).

-compile(export_all).


start(Count, Generation) ->
  syobon:syobon_init(),
  {Cortexes, Fits} = new_population(Count),

  Final = next_gen(Count, lists:zip(Cortexes, Fits), Generation),

  syobon:syobon_deinit(),

  Final.


new_population(Count) -> new_population(Count, [], []).

new_population(0, Cortexes, Fits) -> {Cortexes, Fits};

new_population(Count, Cortexes, Fits) ->
  Layers = [rand:uniform(80) || _ <- lists:seq(1, rand:uniform(30))],

  error_logger:info_msg("new net: ~p~n", [Layers]),

  Cortex = neuron_net:new(Layers),
  Fit = play(Cortex),

  new_population(Count - 1, [Cortex|Cortexes], [Fit|Fits]).


play(Cortex) ->
  Ref = make_ref(),

  syobon:syobon_main(),  %% play!

  ok = syobon:wait_game_init(),
  Cortex ! {self(), Ref, start},
  cortex:sync(Cortex, Ref),

  ok = syobon:wait_game_end(),
  error_logger:info_msg("gname end"),
  Cortex ! {self(), Ref, stop},
  error_logger:info_msg("wait for sensor stop"),
  cortex:sync(Cortex, Ref),
  error_logger:info_msg("sensor stop"),

  syobon:get_fitness().


selection(MaxPop, OldParents) ->
  L = lists:reverse(lists:sort(fun({_, A}, {_, B}) -> A =< B end, OldParents)),
  {Parents, Kills} = lists:split(MaxPop, L),
  [Pid ! {self(), terminate}|| {Pid, _} <- Kills],
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


next_gen(MaxPop, Parents, 0) -> selection(MaxPop, Parents);

next_gen(MaxPop, Parents, Counter) ->
  error_logger:info_msg("parents to selection ~p~n", [Parents]),
  NewParents = selection(MaxPop, Parents),
  {Childs, ChildFits} = new_generation(NewParents),
  error_logger:info_msg("new born"),
  {NewPop, NewPopFits} = new_population(length(NewParents)),

  C = lists:zip(Childs, ChildFits),
  NP = lists:zip(NewPop, NewPopFits),
  next_gen(MaxPop, NewParents ++ C ++ NP, Counter - 1).
