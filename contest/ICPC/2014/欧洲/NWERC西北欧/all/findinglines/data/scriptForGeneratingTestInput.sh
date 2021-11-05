#!/bin/bash

# this script needs to be executed in exactly this folder!!
generateCase(){
	echo "  $2"
	echo "$1" | ./genCases > "$2"
}


echo "compile Testcase generator"
g++ -O2 -o genCases genCases.cpp -std=gnu++0x

if [ -d secret ]
then
	sleep 0;
else
	mkdir secret;
fi
echo "generate Testcases:"
generateCase "123456781234564 line 100000 50 2 49999 49999 50" "secret/01-N100000_twoLinesNotLongEnough.in"
generateCase "123456781234564 line 100000 50 2 50000 49999 50" "secret/02-N100000_twoLinesOneLongEnough.in"
generateCase "123456781234564 line 100000 50 2 50000 50000 50" "secret/03-N100000_twoLinesBothLongEnough.in"
generateCase "123456781234564 rand large 100000 20"  "secret/04-N100000_randLarge.in"
generateCase "123456781234564 rand large 10000 20"   "secret/05-N10000_randLarge.in"
generateCase "123456781234564 rand large 1000 20"    "secret/06-N1000_randLarge.in"
generateCase "123456781234564 rand large 10 20"      "secret/07-N10_randLarge.in"
generateCase "123456781234564 rand small 100 20"     "secret/08-N100_randSmall.in"
generateCase "123456781234564 rand small 20 20"      "secret/09-N20_randSmall.in"
generateCase "123456781234564 rand small 10 20"      "secret/10-N10_randSmall.in"

for (( i = 11 ; i < 13 ; i++ ))
do
	generateCase "$i line 1000 50 2 500 499 50" "secret/$i-N1000_twoLinesOneLongEnough.in"
done

for (( i = 13 ; i < 16 ; i++ ))
do
	generateCase "$i line 100000 20 5 20000 19999 19999 19999 19999 50" "secret/$i-N100000_fiveLinesOneLongEnough.in"
done
for (( i = 16 ; i < 19 ; i++ ))
do
	generateCase "$i line 100000 20 5 19999 19999 20000 19999 19999 50" "secret/$i-N100000_fiveLinesOneLongEnough.in"
done

generateCase "19 line 100000 20 5 19999 19999 19999 19999 19999 50" "secret/19-N100000_fiveLinesNotLongEnough.in"

for (( i = 20 ; i < 30 ; i++ ))
do
	generateCase "$i line 15 20 1 3 14512346" "secret/$i-N15_P20_possible.in"
done

for (( i = 30 ; i < 40 ; i++ ))
do
	generateCase "$i line 1000 $i 3 330 330 330 63814" "secret/$i-N1000_P$i-but33works.in"
done

for (( i = 40 ; i < 44 ; i++ ))
do 
	generateCase "$i special1 $i" "secret/$i-N100000_nearLines.in"
done

generateCase "44 special2" "secret/44-N2pow16_pointsOnLineHaveIndex0mod5.in"
generateCase "45 specialfront" "secret/45-N100000_lineInFront.in"
generateCase "46 specialmid" "secret/46-N100000_lineInMiddle.in"
generateCase "47 specialend" "secret/47-N100000_lineInEnd.in"

echo ""
solutionName="alex_solution_O_N.cpp"
echo "compile reference solution ($solutionName)"
g++ -o tmp_solution ../submissions/accepted/$solutionName -O2 -std=gnu++0x
echo "generate output files with reference solution:"
for infile in secret/*.in
do
	outfile=$(echo $infile | sed "s/\.in/\.ans/")
	echo "  $outfile"
	./tmp_solution < $infile > $outfile
done

echo "remove Testcasegenerator and sample solution"
rm tmp_solution genCases

