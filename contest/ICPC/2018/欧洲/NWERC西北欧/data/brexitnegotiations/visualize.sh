#!/bin/bash

cd $(dirname $0)

for f in data/*/*.in; do
    if [ -f ${f%.in}.png ]; then
        continue
    fi
    echo $f
    nodes=$(cat ${f} | head -n 1)
    dot="dot"
    if [ ${nodes} -gt 100 ]; then
	    dot="sfdp"
    fi
    ./visualize.py < ${f} | timeout 30 ${dot} -Tpng -o ${f%.in}.png
done

