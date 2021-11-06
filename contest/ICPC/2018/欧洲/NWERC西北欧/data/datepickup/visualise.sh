#!/bin/bash

cd $(dirname $0)

for f in data/*/*.in; do
    if [ -f ${f%.in}.png ]; then
        continue
    fi
    echo $f
    python convert-to-dot.py < ${f} | sfdp -x -Goverlap=scale -Tpng -o ${f%.in}.png
done
