#!/bin/bash
# ./stress.sh roz.e brute.e [liczba_testów] [maxn] [maxm]
for i in $(seq 1 "${3:-1000}"); do
  ./gen.e "$i" "${4:-7}" "${5:-12}" > t.in
  ./"$1" < t.in > t.out
  ./"$2" < t.in > t.ok
  if ! diff -q t.out t.ok > /dev/null; then
    echo "ZNALEZIONE, ziarno = $i"; cat t.in
    echo "otrzymano: $(cat t.out), oczekiwano: $(cat t.ok)"; exit 1
  fi
done
echo "OK"
