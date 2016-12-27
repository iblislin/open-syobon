-record(neuron, {
          layer_order=1,
          weights,
          vec_len,  %% vector length
          compute=fun lnalg:dot/2,  %% computation function
          activate=fun math:tanh/1,  %% activation function
          cortex
        }).

-record(sensor, {cortex}).
-record(actuator, {key, cortex}).


-record(cortex, {
          sensor,  %% sensor pid
          net=[],  %% the neuron network table
          actuators,
          neuron_num  %% number of neurons
        }).
