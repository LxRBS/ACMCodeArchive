for i in {3..15}
do
  ./g1 $i > $i.in
  ./sol < $i.in > $i.out
done

for i in {16..30}
do
  ./g2 $i > $i.in
  ./sol < $i.in > $i.out
done

for i in {31..45}
do
  ./g3 $i > $i.in
  ./sol < $i.in > $i.out
done
