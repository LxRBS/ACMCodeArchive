#!/bin/bash

cd $(dirname $0)

for f in */*.in; do
    if [ -f ${f%.in}.png ]; then
        continue
    fi
    echo $f
    cat $f ${f%.in}.ans | asy -f png visualize.asy -o ${f%.in}.png
done
