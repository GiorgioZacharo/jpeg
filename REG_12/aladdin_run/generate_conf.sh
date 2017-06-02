#!/bin/bash

# This file is used to generate multiversioning  configurations for Regions

# Original Version - Default Configuration

	#partition cyclic,ARRAY,2048,4,1
	#unrolling,FUNC,TAG,1
	#pipelining,0
	#cycle_time,10
MODE=${1:-"cyclic"}

rm conf_*
cp conf-$MODE conf_temp 
sed -i -- 's/,/ /g' conf_temp


while read PART TYPE ARRAY ARRAY_SIZE WORD_SIZE PART_FACTOR ; do

	if [ $PART = "partition"  ]; then
		echo  "$PART,$TYPE,$ARRAY,$ARRAY_SIZE,$WORD_SIZE,2" >> conf_ap_2
	else
		echo  "$PART,$TYPE,$ARRAY,$ARRAY_SIZE" >> conf_ap_2
	fi

done<conf_temp

while read UNROLL FUN TAG UNROLL_FACTOR ARG_5  ARG_6; do

	if [ $UNROLL = "unrolling"  ]; then
		echo  "$UNROLL,$FUN,$TAG,2" >> conf_lu_2
		echo  "$UNROLL,$FUN,$TAG,4" >> conf_lu_4
		echo  "$UNROLL,$FUN,$TAG,8" >> conf_lu_8
	else
		echo  "$UNROLL,$FUN,$TAG,$UNROLL_FACTOR,$ARG_5,$ARG_6" >> conf_lu_2
		echo  "$UNROLL,$FUN,$TAG,$UNROLL_FACTOR,$ARG_5,$ARG_6" >> conf_lu_4
		echo  "$UNROLL,$FUN,$TAG,$UNROLL_FACTOR,$ARG_5,$ARG_6" >> conf_lu_8
	fi

done<conf_temp

for version in 2 4 8 ; do
	cp conf_lu_"$version" conf_lu_"$version"_temp
	sed -i -- 's/,/ /g' conf_lu_"$version"_temp
done


for version in 2 4 8 ; do

	while read ARG_1 ARG_2 ARG_3 ARG_4 ARG_5 ARG_6; do

	if [ $ARG_1 = "pipelining"  ]; then
			echo  "$ARG_1,1" >> conf_lu_"$version"_lp
		else
			echo  "$ARG_1,$ARG_2,$ARG_3,$ARG_4,$ARG_5,$ARG_6" >> conf_lu_"$version"_lp
		fi

	done<conf_lu_"$version"_temp

done

rm conf*temp*

exit 0;
