#!/bin/bash
# ============================================================
#  Uruchamia program na wszystkich testach przykładowych z katalogu
#  Testy: KATALOG/xxx.in + KATALOG/xxx.out  (np. tests/1.in, tests/1.out)
#
#  Użycie:   ./testy.sh prog.cpp [KATALOG]
#  Przykład: mkdir tests; nano tests/1.in; nano tests/1.out; ./testy.sh log.cpp tests
# ============================================================
SRC=${1:?"Użycie: ./testy.sh prog.cpp [katalog]"}
DIR=${2:-tests}
BIN="./${SRC%.cpp}.bin"
g++ -std=c++20 -O2 -Wall -Wextra -DLOCAL "$SRC" -o "$BIN" || exit 1

ok=0; zle=0
for f in "$DIR"/*.in; do
    exp="${f%.in}.out"
    start=$(date +%s%N)
    timeout 10 $BIN < "$f" > /tmp/moj.out; kod=$?
    t=$(( ($(date +%s%N) - start) / 1000000 ))ms
    if [ $kod -ne 0 ]; then echo "CRASH/TLE  $f  (kod $kod)"; zle=$((zle+1)); continue; fi
    if [ -f "$exp" ] && ! diff -w /tmp/moj.out "$exp" > /dev/null; then
        echo "ŹLE  $f  ($t)"; echo "  oczekiwane: $(head -c 200 "$exp")"; echo "  dostałem:   $(head -c 200 /tmp/moj.out)"
        zle=$((zle+1))
    else
        echo "OK   $f  ($t)"; ok=$((ok+1))
    fi
done
echo "== OK: $ok, ŹLE: $zle =="
