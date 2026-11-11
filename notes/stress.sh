#!/bin/bash
# Stress test: porównuje wzorcówkę z brute'em na losowych testach.
# Użycie:  bash stress.sh            (2000 testów)
#          bash stress.sh 500        (500 testów)
# chmod +x stress.sh
ILE=${1:-2000}
CXX=${CXX:-g++}          # na Linuksie (students) zwykłe g++ to prawdziwe GCC
FLAGS="-O2 -std=c++17"
LIMIT=2                  # sekundy na jedno uruchomienie, potem uznajemy, że program się zawiesił

# kompilacja — przerywa, jeśli coś się nie skompiluje
for p in wzo brute gen; do
  $CXX $FLAGS $p.cpp -o $p.e || { echo "Nie kompiluje się: $p.cpp"; exit 1; }
done

pokaz_test() {
  echo "--- test.in (ziarno $1) ---"
  cat test.in
}

for ((i = 1; i <= ILE; i++)); do
  echo -ne "\rtest $i/$ILE"
  ./gen.e $i > test.in || { echo; echo "gen.e się wywalił dla ziarna $i"; exit 1; }

  for p in wzo brute; do
    timeout $LIMIT ./$p.e < test.in > $p.out
    kod=$?
    if [ $kod -eq 124 ]; then
      echo; echo "$p.e: przekroczony czas (${LIMIT} s)"; pokaz_test $i; exit 1
    elif [ $kod -ne 0 ]; then
      echo; echo "$p.e: błąd wykonania (kod wyjścia $kod)"; pokaz_test $i; exit 1
    fi
  done

  # -b: ignoruje różnice w ilości spacji (np. spacja na końcu linii)
  if ! diff -bq wzo.out brute.out > /dev/null; then
    echo
    echo "Różnica dla ziarna $i"
    pokaz_test $i
    echo "--- wzo ---"
    cat wzo.out
    echo "--- brute ---"
    cat brute.out
    exit 1
  fi
done
echo
echo "OK, $ILE testów zgodnych"