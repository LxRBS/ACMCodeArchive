for file in ../../data/secret/*
do
    ./bryce < "$file" >> "${file%.in}.ans"
done
