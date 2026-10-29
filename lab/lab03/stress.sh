#!/bin/bash
for ((i = 1; i <= 2000; i++)); do
  ./gen.e $i > test.in              # test dla ziarna i
  ./wzo.e   < test.in > wzo.out
  ./brute.e < test.in > brute.out
  if ! cmp -s wzo.out brute.out; then   # cmp -s: ciche porównanie plików
    echo "Różnica dla ziarna $i"
    cat test.in
    echo "wzo:   $(cat wzo.out)"
    echo "brute: $(cat brute.out)"
    exit 1
  fi
done
echo "OK, 2000 testów zgodnych"
