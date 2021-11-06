#!/usr/bin/env perl

use strict;
use warnings;

my $n = int($ARGV[0] // 1000);
my $m = int($n/2);
$n = 2*$m;
print "$n\n";

for my $i (0 ... $m-1) {
  my $size = 2000 + int rand 8000;
  print "$size 0\n";
}

my $size = 1 + int rand 1000;
print "$size 0\n";

for my $i ($m+1 ... $n-1) {
  $size = 1 + int rand 1000;
  my $j = $i - 1;
  print "$size 1 $j \n";
}