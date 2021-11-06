sub sqr {
   my $v = shift ;
   my $i ;
   my $j ;
   my @r ;
   for ($i=0; $i<length($v); $i++) {
      for ($j=0; $j<length($v); $j++) {
         $r[$i+$j] += substr($v, $i, 1) * substr($v, $j, 1) ;
      }
   }
   $v = '' ;
   for ($i=0; $i<@r; $i++) {
      $v .= $r[$i] % 10 ;
   }
   return $v ;
}
if (int rand 2) {
   my $dc = 1 + int rand 25 ;
   $v = 1 + int rand 9 ;
   for ($i=1; $i<$dc; $i++) {
      $v .= int rand 10 ;
   }
} else {
   $dc = 1 + int rand 13 ;
   $v = 1 + int rand 9 ;
   for ($i=1; $i<$dc; $i++) {
      $v .= int rand 10 ;
   }
   $v = sqr($v) ;
}
print "$v\n" ;
