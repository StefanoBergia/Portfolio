#!/bin/bash

if [ -d "$1" ]; then
    for l in $(ls "$1");
    do 
        if [ -d "$1/$l" ]; then
            continue
        else
            for j in $(grep -n "$2" "$1/$l" | cut -f1 -d:)
            do
                echo $l $j $(sed "${j}q;d" "$1/$l")
            done
        fi 
    done >> "$3.txt"
    sort -k 1,2 "$3.txt" > $3
    rm "$3.txt"
else
    echo "$1 is not a directory"
fi

exit 0