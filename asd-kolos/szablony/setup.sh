#!/bin/bash
# ============================================================
#  Uruchom NA POCZĄTKU KOLOSA:   source ~/asd-kolos/szablony/setup.sh
#  (source, nie ./ — inaczej funkcje nie zostaną w terminalu)
#  Żeby działało też w nowych terminalach:
#     echo "source ~/asd-kolos/szablony/setup.sh" >> ~/.bashrc
# ============================================================

ASD=~/asd/asd-kolos
chmod +x $ASD/szablony/*.sh 2>/dev/null

# c zad      -> szybka kompilacja jak na Szkopule (-O2), binarka ./zad
c()  { g++ -std=c++20 -O2 -Wall -Wextra -Wshadow -DLOCAL "$1.cpp" -o "$1"; }

# d zad      -> kompilacja DEBUG: sanitizery (wyjście poza tablicę, przepełnienie
#               int, use-after-free), sprawdzanie zakresów w vector, symbole do gdb
d()  { g++ -std=c++20 -O1 -g -Wall -Wextra -Wshadow -DLOCAL \
         -fsanitize=address,undefined -fno-sanitize-recover=all \
         -D_GLIBCXX_DEBUG -D_GLIBCXX_DEBUG_PEDANTIC "$1.cpp" -o "$1"; }

# r zad      -> kompiluje (c) i uruchamia na pliku zad.in (albo na wpisywanym wejściu)
r()  { c "$1" && if [ -f "$1.in" ]; then ./"$1" < "$1.in"; else ./"$1"; fi; }

# nowe zad   -> tworzy zad.cpp z szablonu (nie nadpisuje istniejącego)
nowe() { [ -f "$1.cpp" ] && { echo "$1.cpp już istnieje"; return 1; }
         cp $ASD/szablony/szablon.cpp "$1.cpp" && echo "utworzono $1.cpp"; }

# stres zad brute [ile] [maxn] [maxv]  -> stress test z gen.cpp z bieżącego katalogu
stres() { [ -f gen.cpp ] || cp $ASD/szablony/gen.cpp .
          bash $ASD/szablony/stress.sh "$1.cpp" "$2.cpp" gen.cpp "${@:3}"; }

# czas zad plik.in -> czas i maksymalna pamięć (MB)
czas() { if [ -x /usr/bin/time ]; then /usr/bin/time -f "czas: %es   pamięć: %M KB" ./"$1" < "$2" > /dev/null
         else time ./"$1" < "$2" > /dev/null; fi; }   # bez /usr/bin/time: sam czas (patrz "real")

ulimit -s unlimited 2>/dev/null   # duży stos => głęboka rekurencja (DFS) nie wywali się lokalnie
echo "ASD: funkcje c, d, r, nowe, stres, czas gotowe."
