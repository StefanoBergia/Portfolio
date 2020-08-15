#!/bin/sh

if [ -d "$1" ]; then
    for i in $(ls $1);
    do
       sup=$(echo "$i" | tr '[:upper:]' '[:lower:]')
       mv "$1/$i" "$1/$sup"
    done
else
    echo "$1 must be a directory"
fi