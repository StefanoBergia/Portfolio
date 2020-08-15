#!/bin/sh

if [ "$#" -eq 1 ]; then
    f="$1"
else
    echo "insert file name"
    read f
fi
if [ -f "$f" ]; then
    tmp="$(dirname $1)/tmp.txt"
    n=0
    for word in $(more "$f")
    do
        if [ "$n" -eq 0 ]; then
            n=$((n+1))
            words[0]="$word"
            count[0]=1
        else
            found=0
            j=0
            while [ "$j" -lt "$n" -a "$found" -eq 0 ]
            do
                if [ "$word" = "${words[j]}" ]; then
                    count["$j"]=$((${count[j]}+1))
                    found=1
                fi
                j=$((j+1))
            done
            if [ "$found" -eq 0 ]; then
                words["$n"]="$word"
                count["$n"]=1
                
                n=$((n+1))
            fi
        fi
    done

    j=0
    while [ "$j" -lt "$n" ]
    do
        echo "${words[j]}" "${count[j]}" 
        j=$((j+1))
    done >> "$tmp"
    sort -n -k 1 "$tmp"
    more "$tmp"
    rm "$tmp"
else
    echo "you must inserti a valid file name"
fi