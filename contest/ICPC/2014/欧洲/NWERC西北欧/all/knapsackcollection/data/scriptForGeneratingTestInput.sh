#!/bin/bash

# script needs to be executed in exactly this folder

generateCase(){
	echo "  $2"
	echo "$1" | java GenCases > "$2"
}


echo "compile Testcase generator"
javac GenCases.java

if [ -d secret ]
then
	sleep 0;
else
	mkdir secret;
fi

echo "generate Testcases:"
generateCase "random 1000 292834123"  "secret/01-rand1000.in"
generateCase "random 2000 8472841823" "secret/02-rand2000_1.in"
generateCase "random 2000 2183746123 " "secret/03-rand2000_2.in"
generateCase "concentrate 1000  123456   20000   100000 872346124" "secret/04-concentrate1000.in"
generateCase "concentrate 2000  123456   20000   100000 123874124" "secret/05-concentrate2000.in"
generateCase "concentrate 2000 9999999       1 10000000 632918391" "secret/06-maximalResult_allSame.in"
generateCase "concentrate 2000 9999997      -1 10000000 392814512" "secret/07-largeDenominator.in"
generateCase "mixed       2000 9458193 1000000  7026128 0.60 831728213" "secret/08-mixedcase.in"

echo "compile reference solution"
g++ ../submissions/accepted/alex_pathCompression.cpp -std=gnu++0x -O2 -o tmp_solution
echo "generate output files with reference solution:"
for infile in */*.in
do
	outfile=$(echo $infile | sed "s/\.in/\.ans/")
	echo "  $outfile"
	./tmp_solution < $infile > $outfile
done

echo "remove Testcasegenerator and sample solution"
rm tmp_solution GenCases.class

