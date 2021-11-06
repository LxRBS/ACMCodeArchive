#!/bin/bash

for skew in 0 1 10 100; do
    for events in 10 100 365 1000 36500; do
        ./gen_random.py --overwrite --skew $skew $events
    done;
done
