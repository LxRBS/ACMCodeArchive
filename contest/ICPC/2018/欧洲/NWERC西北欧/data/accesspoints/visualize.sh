#!/bin/bash

cd $(dirname $0)
javac submissions/accepted/ContestPass.java

for f in data/*/*.in; do
    if [ -f ${f%.in}.png ]; then
        continue
    fi
    echo $f
    cat ${f} | java -cp submissions/accepted/ ContestPass visualize | asy -f png visualize.asy -o ${f%.in}.png
done

