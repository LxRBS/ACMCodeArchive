for file in *.out
do
    mv "$file" "${file%.out}.ans"
done
