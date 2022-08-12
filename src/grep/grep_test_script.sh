#/bin/bash

options=(-e -i -v -c -l -n -h -s)
index=1

templates=(123 In Don fd)
rm checkGrep.diff checkGrep1 checkGrep2


for tmp in ${templates[*]};
do
    echo "Grep Test $index -e $tmp";
    for file in ../test_example/grep_test/my_tests/*;
    do
        ./s21_grep -e $tmp $file > checkGrep1;
        grep -e $tmp $file > checkGrep2;
        echo "Grep Test $index -e $tmp" >> checkGrep.diff;
        echo $file >> checkGrep.diff;
        diff checkGrep1 checkGrep2 >> checkGrep.diff;
    done
    index=$((index+1));
done

echo "One -e option is DONE"

for tmp1 in ${templates[*]};
do
    for tmp2 in ${templates[*]};
    do
        echo "Grep Test $index -e $tmp1 -e $tmp2";
        for file in ../test_example/grep_test/my_tests/*;
        do
            ./s21_grep -e $tmp1 -e $tmp2 $file > checkGrep1;
            grep -e $tmp1 -e $tmp2 $file > checkGrep2;
            echo "Grep Test $index -e $tmp1 -e $tmp2" >> checkGrep.diff;
            echo $file >> checkGrep.diff;
            diff checkGrep1 checkGrep2 >> checkGrep.diff;
        done
        index=$((index+1));
    done
done

echo "Double -e option is DONE"


for tmp in ${templates[*]};
do
    echo "Grep Test $index -e $tmp";
    for file1 in ../test_example/grep_test/my_tests/*;
    do
        for file2 in ../test_example/grep_test/my_tests/*;
        do
            ./s21_grep -e $tmp $file1 $file2 > checkGrep1;
            grep -e $tmp $file1 $file2 > checkGrep2;
            echo "Grep Test $index -e $tmp" >> checkGrep.diff;
            echo $file $file2 >> checkGrep.diff;
            diff checkGrep1 checkGrep2 >> checkGrep.diff;
        done
        index=$((index+1));
    done
done

echo "One -e option and double file is DONE"

for tmp in ${templates[*]};
do
    echo "Grep Test $index -i $tmp";
    for file in ../test_example/grep_test/my_tests/*;
    do
        ./s21_grep -i $tmp $file > checkGrep1;
        grep -i $tmp $file > checkGrep2;
        echo "Grep Test $index -i $tmp" >> checkGrep.diff;
        echo $file >> checkGrep.diff;
        diff checkGrep1 checkGrep2 >> checkGrep.diff;
    done
    index=$((index+1))
done

echo "-i option and solo file is DONE"

for tmp in ${templates[*]};
do
    echo "Grep Test $index -v $tmp";
    for file in ../test_example/grep_test/my_tests/*;
    do
        ./s21_grep -v $tmp $file > checkGrep1;
        grep -v $tmp $file > checkGrep2;
        echo "Grep Test $index -v $tmp" >> checkGrep.diff;
        echo $file >> checkGrep.diff;
        diff checkGrep1 checkGrep2 >> checkGrep.diff;
    done
    index=$((index+1))
done

echo "-v option and solo file is DONE"

for tmp in ${templates[*]};
do
    echo "Grep Test $index -c $tmp";
    for file in ../test_example/grep_test/my_tests/*;
    do
        ./s21_grep -c $tmp $file > checkGrep1;
        grep -c $tmp $file > checkGrep2;
        echo "Grep Test $index -c $tmp" >> checkGrep.diff;
        echo $file >> checkGrep.diff;
        diff checkGrep1 checkGrep2 >> checkGrep.diff;
    done
    index=$((index+1))
done

echo "-c option and solo file is DONE"

for tmp in ${templates[*]};
do
    echo "Grep Test $index -l $tmp";
    for file in ../test_example/grep_test/my_tests/*;
    do
        ./s21_grep -l $tmp $file > checkGrep1;
        grep -l $tmp $file > checkGrep2;
        echo "Grep Test $index -l $tmp" >> checkGrep.diff;
        echo $file >> checkGrep.diff;
        diff checkGrep1 checkGrep2 >> checkGrep.diff;
    done
    index=$((index+1))
done
echo "-l option and solo file is DONE"

for tmp in ${templates[*]};
do
    echo "Grep Test $index -n $tmp";
    for file in ../test_example/grep_test/my_tests/*;
    do
        ./s21_grep -n $tmp $file > checkGrep1;
        grep -n $tmp $file > checkGrep2;
        echo "Grep Test $index -n $tmp" >> checkGrep.diff;
        echo $file >> checkGrep.diff;
        diff checkGrep1 checkGrep2 >> checkGrep.diff;
    done
    index=$((index+1))
done
echo "-n option and solo file is DONE"

for tmp in ${templates[*]};
do
    echo "Grep Test $index -h $tmp";
    for file in ../test_example/grep_test/my_tests/*;
    do
        ./s21_grep -h $tmp $file > checkGrep1;
        grep -h $tmp $file > checkGrep2;
        echo "Grep Test $index -h $tmp" >> checkGrep.diff;
        echo $file >> checkGrep.diff;
        diff checkGrep1 checkGrep2 >> checkGrep.diff;
    done
    index=$((index+1))
done
echo "-h option and solo file is DONE"

for tmp in ${templates[*]};
do
    echo "Grep Test $index -s $tmp";
    for file in ../test_example/grep_test/my_tests/*;
    do
        ./s21_grep -s $tmp $file > checkGrep1;
        grep -s $tmp $file > checkGrep2;
        echo "Grep Test $index -s $tmp" >> checkGrep.diff;
        echo $file >> checkGrep.diff;
        diff checkGrep1 checkGrep2 >> checkGrep.diff;
    done
    index=$((index+1))
done
echo "-s option and solo file is DONE"























for tmp in ${templates[*]};
do
    echo "Grep Test $index -i $tmp";
    for file in ../test_example/grep_test/my_tests/*;
    do
        for file1 in ../test_example/grep_test/my_tests/*;
        do

            ./s21_grep -i $tmp $file $file1 > checkGrep1;
            grep -i $tmp $file $file1 > checkGrep2;
            echo "Grep Test $index -i $tmp" >> checkGrep.diff;
            echo $file $file1 >> checkGrep.diff;
            diff checkGrep1 checkGrep2 >> checkGrep.diff;
        done
    done
    index=$((index+1))
done

echo "-i option and double file is DONE"

for tmp in ${templates[*]};
do
    echo "Grep Test $index -v $tmp";
    for file in ../test_example/grep_test/my_tests/*;
    do
        for file1 in ../test_example/grep_test/my_tests/*;
        do

            ./s21_grep -v $tmp $file $file1 > checkGrep1;
            grep -v $tmp $file $file1 > checkGrep2;
            echo "Grep Test $index -v $tmp" >> checkGrep.diff;
            echo $file $file1 >> checkGrep.diff;
            diff checkGrep1 checkGrep2 >> checkGrep.diff;
        done
    done
    index=$((index+1))
done

echo "-v option and double file is DONE"

for tmp in ${templates[*]};
do
    echo "Grep Test $index -c $tmp";
    for file in ../test_example/grep_test/my_tests/*;
    do
        for file1 in ../test_example/grep_test/my_tests/*;
        do

            ./s21_grep -c $tmp $file $file1 > checkGrep1;
            grep -c $tmp $file $file1 > checkGrep2;
            echo "Grep Test $index -c $tmp" >> checkGrep.diff;
            echo $file $file1 >> checkGrep.diff;
            diff checkGrep1 checkGrep2 >> checkGrep.diff;
        done
    done
    index=$((index+1))
done

echo "-c option and double file is DONE"

for tmp in ${templates[*]};
do
    echo "Grep Test $index -l $tmp";
    for file in ../test_example/grep_test/my_tests/*;
    do
        for file1 in ../test_example/grep_test/my_tests/*;
        do

            ./s21_grep -l $tmp $file $file1 > checkGrep1;
            grep -l $tmp $file $file1 > checkGrep2;
            echo "Grep Test $index -l $tmp" >> checkGrep.diff;
            echo $file $file1 >> checkGrep.diff;
            diff checkGrep1 checkGrep2 >> checkGrep.diff;
        done
    done
    index=$((index+1))
done
echo "-l option and double file is DONE"

for tmp in ${templates[*]};
do
    echo "Grep Test $index -n $tmp";
    for file in ../test_example/grep_test/my_tests/*;
    do
        for file1 in ../test_example/grep_test/my_tests/*;
        do

            ./s21_grep -n $tmp $file $file1 > checkGrep1;
            grep -n $tmp $file $file1 > checkGrep2;
            echo "Grep Test $index -n $tmp" >> checkGrep.diff;
            echo $file $file1 >> checkGrep.diff;
            diff checkGrep1 checkGrep2 >> checkGrep.diff;
        done
    done
    index=$((index+1))
done
echo "-n option and double file is DONE"

for tmp in ${templates[*]};
do
    echo "Grep Test $index -h $tmp";
    for file in ../test_example/grep_test/my_tests/*;
    do
        for file1 in ../test_example/grep_test/my_tests/*;
        do

            ./s21_grep -h $tmp $file $file1 > checkGrep1;
            grep -h $tmp $file $file1 > checkGrep2;
            echo "Grep Test $index -h $tmp" >> checkGrep.diff;
            echo $file $file1 >> checkGrep.diff;
            diff checkGrep1 checkGrep2 >> checkGrep.diff;
        done
    done
    index=$((index+1))
done
echo "-h option and double file is DONE"

for tmp in ${templates[*]};
do
    echo "Grep Test $index -s $tmp";
    for file in ../test_example/grep_test/my_tests/*;
    do
        for file1 in ../test_example/grep_test/my_tests/*;
        do

            ./s21_grep -s $tmp $file $file1 > checkGrep1;
            grep -s $tmp $file $file1 > checkGrep2;
            echo "Grep Test $index -s $tmp" >> checkGrep.diff;
            echo $file $file1 >> checkGrep.diff;
            diff checkGrep1 checkGrep2 >> checkGrep.diff;
        done
    done
    index=$((index+1))
done
echo "-s option and double file is DONE"


for tmp in ${templates[*]};
do
    echo "Custom Grep Test $index -cl $tmp";
    for file in ../test_example/grep_test/my_tests/*;
    do
        for file1 in ../test_example/grep_test/my_tests/*;
        do

            ./s21_grep -cl $tmp $file $file1 > checkGrep1;
            grep -cl $tmp $file $file1 > checkGrep2;
            echo "Grep Test $index -cl $tmp" >> checkGrep.diff;
            echo $file $file1 >> checkGrep.diff;
            diff checkGrep1 checkGrep2 >> checkGrep.diff;
        done
    done
    index=$((index+1))
done
