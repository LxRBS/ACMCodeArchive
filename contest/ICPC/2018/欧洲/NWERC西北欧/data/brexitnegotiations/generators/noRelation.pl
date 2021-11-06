#!/usr/bin/env perl

use strict;
use warnings;

my $n = int($ARGV[0] // 1000);
print "$n\n";

for my $i (0 ... $n-1) {
  my $size = 1 + int rand 10000;
  print "$size 0\n";
}
