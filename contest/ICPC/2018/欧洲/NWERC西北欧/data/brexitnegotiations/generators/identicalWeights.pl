#!/usr/bin/env perl

use strict;
use warnings;

my $n = int($ARGV[0] // 1000);
my $maxM = 1000000;
print "$n\n";

my $size = 10;

for my $i (0 ... $n-1) {
  my @deps = ();
  for my $j (0 ... $i-1) {
    if ($maxM > 0 && 0 == int rand 4) {
      push @deps, $j;
      $maxM = $maxM - 1;
    }
  }
  my $ndeps = @deps;
  print "$size $ndeps @deps\n";
}