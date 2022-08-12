#/bin/bash

options=(-b -e -n -s -t)
index=1

echo "Start Tests"

rm check.diff check1 check2

for first in ${options[*]};
do
    for sec in ${options[*]};
    do
        for third in ${options[*]};
        do
            for fourth in ${options[*]};
            do
                echo "Cat Test $index $first $sec $third $fourth"
                for file in ../test_example/cat_test/*/*;
                do
                    ./s21_cat $first $sec $third $fourth $file > check1;
                    cat $first $sec $third $fourth $file > check2;
                    echo "Cat Test $index $first $sec $third $fourth" >> check.diff
                    echo $file >> check.diff
                    diff check1 check2 >> check.diff;
                done
                index=$((index+1))
            done
        done
    done
done

echo "Cat Test $index -bents"
for file in ../test_example/cat_test/*/*;
do
    ./s21_cat -bents $file > check1;
    cat -bents $file > check2;
    echo "Cat Test $index $first $sec $third $fourth" >> check.diff
    echo $file >> check.diff
    diff check1 check2 >> check.diff;
done
index=$((index+1))


echo "DONE"
