#!/bin/bash

cd $(dirname $0)
javac submissions/accepted/jeroen_sort_once.java

# Max image size: 8000x8000 (80in * 100dpi)
for f in data/*/*.in; do
    if [ -f ${f%.in}.png ]; then
        continue
    fi
    echo $f
    cat ${f} \
        | java -Xss64m -Xmx1g -cp submissions/accepted/ jeroen_sort_once visualize \
        | timeout 15 dot -T png -Gsize=80,80\! -Gdpi=100 -o ${f%.in}.png \
            || ( echo "  (not generated)" && touch ${f%.in}.png )
done

