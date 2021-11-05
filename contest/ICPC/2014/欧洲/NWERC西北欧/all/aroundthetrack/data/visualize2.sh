#!/bin/sh

if [ ! -f "$1" ]; then
	echo "Usage: ./visualize2.sh <inputfile>"
	exit 1
fi

javac -d . ../submissions/accepted/jeroen.java;
OUTNAME=${1%.in}.pdf
java jeroen -dump < $1 2>&1 >/dev/null | ps2pdf -dNOSAFER visualize2.ps $OUTNAME;
echo "$OUTNAME has been generated."
