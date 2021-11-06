my @onelane = () ;
for ($i=1; $i<8; $i++) {
   $s = '' ;
   $s .= 'L' if $i & 1 ;
   $s .= 'S' if $i & 2 ;
   $s .= 'R' if $i & 4 ;
   push @onelane, $s ;
}
sub okay {
   my $a = shift ;
   my $b = shift ;
   return 0 if $a =~ /S/ && $b =~ /L/ ;
   return 0 if $a =~ /R/ && $b =~ /S/ ;
   return 0 if $a =~ /R/ && $b =~ /L/ ;
   return 1 ;
}
sub recur {
   my $sofar = shift ;
   my $togo = shift ;
   if ($togo == 0) {
      push @a, $sofar ;
      return ;
   }
   my $i ;
   for ($i=0; $i<@onelane; $i++) {
      if (okay($sofar, $onelane[$i])) {
         recur($sofar eq '' ? $onelane[$i] : $sofar . ' ' . $onelane[$i], $togo-1) ;
      }
   }
}
my $r = shift || 15 ;
my $c = shift || 15 ;
my $w = shift || 3 ;
my $p = shift || 50 ;
@a = () ;
recur("", $w) ;
@threelane = @a ;
my $s = 4 * $r * $c - 2 * ($r + $c) ;
print "$r $c $w\n$s\n" ;
my @curbs = () ;
sub getcost {
   my $r = (2 + int rand 99) & -2 ;
   return $r ;
}
for ($i=0; $i<$r; $i++) {
   for ($j=0; $j<$c; $j++) {
      if ($i+1 < $r) {
         $cost = getcost() ;
         print "$i $j ", $i+1, " $j $cost " ;
         while (1) {
            $t = $threelane[int rand @threelane] ;
            next if $i+2 == $r && $t =~ /S/ ;
            next if $j == 0 && $t =~ /R/ ;
            next if $j+1 == $c && $t =~ /L/ ;
            last ;
         }
         push @curbs, "$i $j " . ($i + 1) . " $j" ;
         print "$t\n" ;
      }
      if ($i > 0) {
         $cost = getcost() ;
         print "$i $j ", $i-1, " $j $cost " ;
         while (1) {
            $t = $threelane[int rand @threelane] ;
            next if $i == 1 && $t =~ /S/ ;
            next if $j == 0 && $t =~ /L/ ;
            next if $j+1 == $c && $t =~ /R/ ;
            last ;
         }
         push @curbs, "$i $j " . ($i - 1) . " $j" ;
         print "$t\n" ;
      }
      if ($j+1 < $c) {
         $cost = getcost() ;
         print "$i $j $i ", $j+1, " $cost " ;
         while (1) {
            $t = $threelane[int rand @threelane] ;
            next if $j+2 == $c && $t =~ /S/ ;
            next if $i == 0 && $t =~ /L/ ;
            next if $i+1 == $r && $t =~ /R/ ;
            last ;
         }
         push @curbs, "$i $j $i " . ($j + 1) ;
         print "$t\n" ;
      }
      if ($j > 0) {
         $cost = getcost() ;
         print "$i $j $i ", $j-1, " $cost " ;
         while (1) {
            $t = $threelane[int rand @threelane] ;
            next if $j == 1 && $t =~ /S/ ;
            next if $i == 0 && $t =~ /R/ ;
            next if $i+1 == $r && $t =~ /L/ ;
            last ;
         }
         push @curbs, "$i $j $i " . ($j - 1) ;
         print "$t\n" ;
      }
   }
}
print "$p\n" ;
for ($i=0; $i<$p; $i++) {
   $s = $curbs[int rand @curbs] ;
   $d = $curbs[int rand @curbs] ;
   $x = int rand 5 ;
   $y = int rand 5 ;
   print "$s $d $x $y\n" ;
}
