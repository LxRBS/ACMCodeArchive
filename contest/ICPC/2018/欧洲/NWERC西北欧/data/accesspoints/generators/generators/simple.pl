#!/usr/bin/env perl

use strict;
use warnings;

my $n = 10;
my @x = map {1 + int rand 10} (1 ... $n);
my @y = map {1 + int rand 10} (1 ... $n);
print "$n\n";
for my $i (0 ... $n-1) {
  print "$x[$i] $y[$i]\n";
}
