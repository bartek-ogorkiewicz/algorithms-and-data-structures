#!/bin/bash
# ============================================================
#  STRESS TEST: porównuje wzorcówkę z brute'em na losowych testach
#
#  Użycie:   ./stress.sh WZOR BRUTE GEN [ILE_TESTÓW] [MAXN] [MAXV]
#  Przykład: ./stress.sh log.cpp brute.cpp gen.cpp
#            ./stress.sh log.cpp brute.cpp gen.cpp 5000 6 10
#
#  Pliki .cpp są kompilowane automatycznie (z sanitizerami => łapie
#  wyjście poza tablicę, przepełnienie int, użycie niezainicjalizowanych).
#  Gdy znajdzie różnicę lub crash: wypisuje test i oba wyniki,
#  zostawia go w pliku fail.in i kończy.
#
#  Jeśli nie ma uprawnień: chmod +x stress.sh   (albo: bash stress.sh ...)
# ============================================================

WZOR=${1:?"Podaj: ./stress.sh wzor.cpp brute.cpp gen.cpp [ile] [maxn] [maxv]"}
BRUTE=${2:?"Brak brute"}
GEN=${3:?"Brak generatora"}
ILE=${4:-1000}
MAXN=${5:-8}
MAXV=${6:-20}

FLAGS="-std=c++20 -O2 -g -Wall -Wextra -fsanitize=address,undefined -fno-sanitize-recover=all -DLOCAL"

compile() {   # compile plik.cpp -> ./plik.bin
    local bin="./${1%.cpp}.bin"
    if ! g++ $FLAGS "$1" -o "$bin" 2> /tmp/stress_cerr; then
        cat /tmp/stress_cerr >&2; echo "BŁĄD KOMPILACJI: $1" >&2; exit 1
    fi
    echo "$bin"
}

W=$(compile "$WZOR")  || exit 1
B=$(compile "$BRUTE") || exit 1
G=$(compile "$GEN")   || exit 1
echo "Skompilowane. Testuję $ILE testów (MAXN=$MAXN, MAXV=$MAXV)..."

for ((i = 1; i <= ILE; i++)); do
    $G $i $MAXN $MAXV > test.in
    timeout 5 $W < test.in > wzor.out 2> wzor.err;  RW=$?
    timeout 5 $B < test.in > brute.out 2> brute.err; RB=$?

    if [ $RW -ne 0 ]; then
        echo "=== CRASH/TIMEOUT wzorcówki (kod $RW) na teście $i ==="
        cat test.in; echo "--- stderr:"; head -20 wzor.err
        cp test.in fail.in; exit 1
    fi
    if [ $RB -ne 0 ]; then
        echo "=== CRASH brute'a (kod $RB) na teście $i — popraw brute ==="
        cat test.in; head -20 brute.err; exit 1
    fi
    if ! diff -w wzor.out brute.out > /dev/null; then   # -w: ignoruje różnice w spacjach
        echo "=== ZŁA ODPOWIEDŹ na teście $i (seed $i) ==="
        echo "--- wejście:";  cat test.in
        echo "--- wzorcówka:"; cat wzor.out
        echo "--- brute:";     cat brute.out
        cp test.in fail.in
        echo "(test zapisany w fail.in; odtwórz: $G $i $MAXN $MAXV)"
        exit 1
    fi
    (( i % 100 == 0 )) && echo "  ok $i"
done
echo "WSZYSTKIE $ILE TESTÓW OK"
rm -f test.in wzor.out brute.out wzor.err brute.err
