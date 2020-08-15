#!/bin/bash

if [ "$#" -ge 2 ]; then
    i=0
    while [ "$i" -lt 5 ]
    do
         echo "Checking $1 status..."
        state=$( ps -el |  awk '{ print $2,$4}' | grep "$1" | cut -d ' ' -f1) 
        echo -n $state
        if [ "$state" = "Z" ];then
            i=$((i+1))
            echo $i
        else
            i=0
        fi
        sleep $2
    done 
    kill -9 $1
else
    echo "insert pid and time interval"
fi