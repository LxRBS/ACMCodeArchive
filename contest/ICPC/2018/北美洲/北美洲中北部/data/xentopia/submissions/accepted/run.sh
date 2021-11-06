for file in ../../data/secret/*.in
do
    echo "running on $file"
    time java xentopia_xiaowuc1 < "$file" > "${file%.in}.ans"
done
