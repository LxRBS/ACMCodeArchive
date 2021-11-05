#!/bin/zsh

javac -d . ../submissions/accepted/jeroen.java;
for i in s*/*.in; java jeroen -dump < $i 2>&1 | asy -f png visualize.asy -o $i:r.png
rm -rf jeroen*.class
