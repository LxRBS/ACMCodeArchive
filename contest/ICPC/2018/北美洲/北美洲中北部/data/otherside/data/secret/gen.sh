for i in {1..30}
do
  ./g1 $i > $i.in
  ./sol < $i.in > $i.out
done

for i in {31..40}
do
  ./g2 $i > $i.in
  ./sol < $i.in > $i.out
done
