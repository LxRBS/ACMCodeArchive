#!/bin/bash

cd $(dirname $0)

mkdir -p visualize-tmp

for f in */*.in; do
    if [ -f ${f%.in}.png ]; then
        continue
    fi
    echo $f
    cat $f ${f%.in}.ans | ./visualize.py ${f%.in}.png
    if [ $? == 0 ]; then
        cd visualize-tmp
        pdflatex fig.tex
        pdftoppm -png -rx 300 -ry 300 fig.pdf fig
        cd ..
        convert visualize-tmp/fig-1.png ${f%.in}.png
    fi
done

rm -rf visualize-tmp
