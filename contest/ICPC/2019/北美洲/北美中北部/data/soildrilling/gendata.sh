#!/bin/sh
./drillGenerator 8 25 1 > data/sample/02sample.in
echo 50 > data/sample/02sample.ans
./drillGenerator 100 45 0 > data/secret/gen100x.in
echo 90 > data/secret/gen100x.ans
./drillGenerator 100 210 1 > data/secret/gen100y.in
echo 420 > data/secret/gen100y.ans
./drillGenerator 100 21 2 > data/secret/gen100z.in
echo 42 > data/secret/gen100z.ans
./shellGenerator 100 42 0 > data/secret/shell100.in
echo 84 > data/secret/shell100.ans
./drillGenerator 200 -45 1 > data/secret/gen200.in
echo 90 > data/secret/gen200.ans
./shellGenerator 200 -412 0 > data/secret/shell200.in
echo 824 > data/secret/shell200.ans
./drillGenerator 1000 5 2 > data/secret/gen1000.in
echo 10 > data/secret/gen1000.ans
./shellGenerator 1000 12.3 1 > data/secret/shell1000.in
echo 24.6 > data/secret/shell1000.ans
./drillGenerator 5000 55 2 > data/secret/gen5000.in
echo 110 > data/secret/gen5000.ans
./shellGenerator 5000 124 1 > data/secret/shell5000.in
echo 248> data/secret/shell5000.ans
