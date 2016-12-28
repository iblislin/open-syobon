-module(collector).

-compile(export_all).

-include("records.hrl").


new(Cortex, VecLen, Output) ->
  spawn(?MODULE, loop,
        [#collector{cortex=Cortex, vec_len=VecLen, output=Output,
                    left_num=VecLen, arr=array:new(VecLen)}]).


loop(C=#collector{left_num=0, output=Output, arr=Arr, ref=Ref,
                  vec_len=VecLen}) ->
  %% forward the result
  Val = array:to_list(Arr),
  [Pid ! {input, Ref, Val}|| {Pid, _} <- Output],

  %% re-init array
  NewC = pop_refs(C#collector{left_num=VecLen, arr=array:new(VecLen)}),
  loop(NewC);

loop(C=#collector{cortex=Cortex, refs_queue=Refs, ref=Ref, arr=Arr,
                  left_num=Left}) ->
  receive
    {neuron, Ref, Order, Val} ->
      NewC = C#collector{arr=array:set(Order - 1, Val, Arr), left_num=Left - 1},
      loop(NewC);

    {Cortex, push_ref, NewRef} ->
      case Ref of
        undefined -> loop(C#collector{ref=NewRef});
        _ -> loop(C#collector{refs_queue=Refs ++ [NewRef]})
      end
  end.


pop_refs(C=#collector{refs_queue=[]}) ->
      C#collector{ref=undefined};

pop_refs(C=#collector{refs_queue=[Ref|T]}) ->
      C#collector{ref=Ref, refs_queue=T}.
