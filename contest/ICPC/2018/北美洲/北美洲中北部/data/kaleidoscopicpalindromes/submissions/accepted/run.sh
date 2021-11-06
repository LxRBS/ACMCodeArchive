for file in ../../data/secret/*.in
do
    echo "running on $file"
    ./bryce_ac < "$file" > "${file%.in}.ans"
done
