#!/bin/sh

if [ -f "$1" ]; then
    echo "number of lines:" $(wc -l "$1" | cut -f1 -d ' ')
    max=0;
    id=0;
    for i in $(more "$1");
    do
        sup=$(echo -n $i | wc -c)
        if [ $sup -gt $max ]; then
            max=$((sup))
        fi
        id=$((id+1))
    done
    echo "longest line has $max characters"
else
    echo "$1 must be a file"
fi


