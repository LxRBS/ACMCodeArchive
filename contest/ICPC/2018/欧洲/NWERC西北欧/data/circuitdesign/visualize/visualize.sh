#!/bin/bash
# call this script only from this folder
# call this script with two parameters the input file of the problem (specifying the graph) and the output file (specifying the positions)
# creates the visualization in 'tmp.png'
make gen-gnuplot-input
echo $1 $2 tmp.data | ./gen-gnuplot-input
gnuplot draw_segments.gp
