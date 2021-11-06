#!/usr/bin/env perl

use strict;
use warnings;

my $n = 10000;
my @values = sort {$b <=> $a} map {1 + int rand 1000000000000000} (1 ... $n);
print "$n\n@values\n";
