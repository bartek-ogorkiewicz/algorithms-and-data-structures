#!/bin/bash
# Stress test: porównuje wzorcówkę z brute'em na losowych testach.
# Użycie:  bash stress.sh            (2000 testów)
#          bash stress.sh 500        (500 testów)

ILE=${1:-2000}
CXX=g++-15
FLAGS="-O2 -std=c++17"

# kompilacja — przerywa, jeśli coś się nie skompiluje
$CXX $FLAGS wzo.cpp   -o wzo.e   || exit 1
$CXX $FLAGS brute.cpp -o brute.e || exit 1
$CXX $FLAGS gen.cpp   -o gen.e   || exit 1

for ((i = 1; i <= ILE; i++)); do
  echo -ne "\rtest $i/$ILE"
  ./gen.e $i > test.in
  ./wzo.e   < test.in > wzo.out
  ./brute.e < test.in > brute.out
  if ! cmp -s wzo.out brute.out; then
    echo
    echo "Różnica dla ziarna $i"
    echo "--- test.in ---"
    cat test.in
    echo "--- wzo ---"
    cat wzo.out
    echo "--- brute ---"
    cat brute.out
    exit 1
  fi
done
echo
echo "OK, $ILE testów zgodnych"
