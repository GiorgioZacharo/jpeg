#!/bin/bash

# This file is used to run all  configurations for Regions with aladdin HW simulator

# Original Version - Default Configuration

	#partition cyclic,ARRAY,2048,4,1
	#unrolling,FUNC,TAG,1
	#pipelining,0
	#cycle_time,10

MODE=${1:-"cyclic"}

./generate_conf.sh $MODE

for conf in  $(ls conf*); do
        timeout 2s      ./run.sh $conf
done

rename "s/_summary//g" *
mkdir results_$MODE; mv  res_* results_$MODE/.

exit 0;
