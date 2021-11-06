set terminal png size 1600,900
set output 'tmp.png'
unset key
plot 'tmp.data' using 1:2:($3-$1):($4-$2) with vectors nohead lw 3
