-record(neuron, {
          layer_order=1,
          weights,
          vec_len,  %% vector length
          compute=fun lnalg:dot/2,  %% computation function
          activate=fun math:tanh/1,  %% activation function
          cortex,
          collector
        }).

-record(sensor, {cortex, data_len}).
-record(actuator, {key, cortex, enabled=true}).

-record(collector, {
          cortex,
          ref,
          refs_queue=[],
          vec_len,
          output,
          arr,
          left_num
        }).

-record(cortex, {
          sensor,  %% sensor pid
          net=[],  %% the neuron network table
          actuator,
          start_time,
          stop_time,
          collectors,
          neuron_num,  %% number of neurons
          layer_num,  %% number of neuron layers
          enabled=false
        }).
