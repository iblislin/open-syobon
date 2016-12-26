-record(neuron, {
          layer_order=1,
          weights,
          vec_len,  %% vector length
          compute=fun lnalg:dot/2,  %% computation function
          activate=fun math:tanh/1,  %% activation function
          output_list=[]
        }).

-record(sensor, {cortex}).


-record(cortex, {
          sensor,  %% sensor pid
          net=[],  %% the neuron network table
          actuator
        }).
