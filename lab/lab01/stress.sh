#!/bin/bash
# stress.sh — szuka testu, na którym ./lan.e różni się od ./lans1.e
for i in $(seq 1 1000); do
  ./gen.e $i > t.in
  ./lan.e   < t.in > t.out
  ./lans1.e < t.in > t.ok
  if ! diff -q t.out t.ok > /dev/null; then
    echo "ZNALEZIONE, ziarno = $i"
    cat t.in
    echo "otrzymano: $(cat t.out), oczekiwano: $(cat t.ok)"
    exit 1
  fi
done
echo "1000 testów OK"
