#!/usr/bin/env python3

import argparse
import os
import random
import sys

def clamp(x):
    return min(x, 100)

def main():
    p = argparse.ArgumentParser()
    p.add_argument('--seed', default=42, type=int)
    p.add_argument('--skew', default=0, type=float, help='Amount of skew in the distribution used to generate examples')
    p.add_argument('--overwrite', default=False, action='store_true')
    p.add_argument('events', type=int)
    args = p.parse_args()

    random.seed(args.seed)

    # parameters for the beta distribution
    alpha = 1.0 / (1.0 + args.skew)
    beta = 1.0

    x = [int(365 * random.betavariate(alpha, beta)) + 1 for _ in range(args.events)]
    #import matplotlib.pyplot
    #matplotlib.pyplot.hist(x, 30)
    #matplotlib.pyplot.show()

    data = [clamp(x.count(z)) for z in set(x)]
    random.shuffle(data)

    actual_events = sum(data)

    output_filename = 'random_seed_{}_events_{}_skew_{}.in'.format(args.seed, actual_events, args.skew)
    if os.path.exists(output_filename) and not args.overwrite:
        print('refusing to overwrite {}'.format(output_filename))
        return

    with open(output_filename, 'w') as out:
        out.write('{}\n'.format(len(data)))
        out.write(' '.join(map(str, data)) + '\n')

if __name__ == '__main__':
    main()

