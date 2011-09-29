make clean
make
j=0
for((i=3; i<10; i++))
do
  j=$(($j+1))
  echo test $j:
  cat setup
  sed -i /150/c"$i 0.3 4 150" setup
  ./dbscan
  cat result | grep SSE  
  echo
  echo
  echo
done
