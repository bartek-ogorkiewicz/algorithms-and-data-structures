#!/bin/bash
# użycie: ./stress.sh ./roz.e ./brute.e [testów] [argumenty generatora...]
ROZ=$1; BRUTE=$2; ILE=${3:-1000}
shift $(( $# < 3 ? $# : 3 ))
for i in $(seq 1 "$ILE"); do
  ./gen.e "$i" "$@" > t.in
  if ! "$ROZ" < t.in > t.out; then echo "CRASH, ziarno = $i"; cat t.in; exit 1; fi
  "$BRUTE" < t.in > t.ok
  if ! diff -bq t.out t.ok > /dev/null; then
    echo "ZŁA ODPOWIEDŹ, ziarno = $i"; cat t.in
    echo "otrzymano:  $(cat t.out)"; echo "oczekiwano: $(cat t.ok)"; exit 1
  fi
done
echo "$ILE testów OK"
