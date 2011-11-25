#!/bin/bash
touch ../data/mushroom.arff
cat ../data/mushroom.meta.header > ../data/mushroom.arff
cat ../data/mushroom.data.csv >> ../data/mushroom.arff
a=0
while read line
do a=$(($a+1));
done < ../data/mushroom.data.csv
echo "The number of mushroom is: $a in the dataset";
