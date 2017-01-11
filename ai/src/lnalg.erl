-module(lnalg).

-compile(export_all).

-export([dot/2, outer_product/2, mat_ones/2, mat_add/2, vec_add/2]).


multiply({X, Y}) -> X * Y.


dot(U, V) -> lists:sum(lists:map(fun multiply/1, lists:zip(U, V))).


outer_product(A, B) -> outer_product(A, B, []).

outer_product([], _, M) -> lists:reverse(M);

outer_product([H|T], V, M) ->
  outer_product(T, V, [[H*X || X <- V]|M]).

%% matrix ones
mat_ones(Row, Col) ->
  lists:duplicate(Row, lists:duplicate(Col, 0)).


%% matrix add
mat_add(A, B) -> mat_add(A, B, []).

mat_add([], [], M) -> lists:reverse(M);

mat_add([Ah|At], [Bh|Bt], M) ->
  mat_add(At, Bt, [vec_add(Ah, Bh)|M]).


%% vector add
vec_add(A, B) -> vec_add(A, B, []).

vec_add([], [], V) -> lists:reverse(V);

vec_add([Ah|At], [Bh|Bt], V) ->
  vec_add(At, Bt, [Ah + Bh|V]).
