for file in ../../data/secret/*.in
do
    echo "running on $file"
    ./menghui < "$file" > "${file%.in}.ans"
done
