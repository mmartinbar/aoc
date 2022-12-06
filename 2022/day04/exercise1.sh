#!/bin/bash

let i=0;
for line in `cat input.txt`; do
    IFS=',' read -r -a sections <<< "$line"
    IFS='-' read -r -a is0 <<< "${sections[0]}"
    IFS='-' read -r -a is1 <<< "${sections[1]}"
    if (( ${is1[0]} >= ${is0[0]} && ${is1[1]} <= ${is0[1]} )); then
        i=$((i+1))
    elif (( ${is0[0]} >= ${is1[0]} && ${is0[1]} <= ${is1[1]} )); then
        i=$((i+1))
    fi
done

echo "num pairs: $i"
