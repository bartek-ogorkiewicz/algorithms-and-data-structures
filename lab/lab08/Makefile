# Lab 8 — drzewo przedziałowe.
#
#   make test        testy jednostkowe segtree.h (cel 2); pierwsza kompilacja trwa ok. 15 s
#                    (doctest_main.o), kolejne już tylko kilka sekund
#   make test_gen    testy jednostkowe segtree_gen.h (cel 3)
#   make inw.e       zadanie Inwersje,   ./inw.e < wejscie.txt
#   make ros.e       zadanie Rosnący podciąg
#   make wyslij      wyslij/inw.cpp i wyslij/ros.cpp — jeden plik z wklejonym nagłówkiem,
#                    gotowy do wysłania na Szkopuł
#   make szybko      inw i ros bez sanitizerów, z -O2 (do mierzenia czasu)
#
# Domyślne flagi włączają sanitizery i tryb debug biblioteki standardowej: wyjście poza
# tablicę albo przepełnienie kończy program z komunikatem, zamiast dawać losowy wynik.

CXX      ?= g++
CXXFLAGS ?= -std=c++20 -Wall -Wextra -O1 -g -fsanitize=address,undefined -D_GLIBCXX_DEBUG
FAST      = -std=c++20 -Wall -Wextra -O2

all: test_segtree.e test_segtree_gen.e inw.e ros.e gen.e

test: test_segtree.e
	./test_segtree.e

test_gen: test_segtree_gen.e
	./test_segtree_gen.e

# Testy linkujemy z doctest_main.o: main() doctesta kompiluje się raz, a nie przy każdej zmianie.
test_segtree.e: test_segtree.o doctest_main.o
	$(CXX) $(CXXFLAGS) $^ -o $@
test_segtree_gen.e: test_segtree_gen.o doctest_main.o
	$(CXX) $(CXXFLAGS) $^ -o $@

test_segtree.o inw.e: segtree.h
test_segtree_gen.o ros.e: segtree_gen.h
test_segtree.o test_segtree_gen.o doctest_main.o: doctest.h

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

%.e: %.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

szybko: inw_szybko.e ros_szybko.e gen.e

%_szybko.e: %.cpp
	$(CXX) $(FAST) $< -o $@
inw_szybko.e: segtree.h
ros_szybko.e: segtree_gen.h

# Wkleja treść segtree*.h w miejsce #include "segtree*.h" (bez #pragma once).
wyslij: wyslij/inw.cpp wyslij/ros.cpp

wyslij/inw.cpp: inw.cpp segtree.h
wyslij/ros.cpp: ros.cpp segtree_gen.h
wyslij/%.cpp: %.cpp
	@mkdir -p wyslij
	awk '/^#include "segtree(_gen)?\.h"/ { f = substr($$2, 2, length($$2) - 2); \
	  while ((getline l < f) > 0) if (l !~ /^#pragma once/) print l; close(f); next } \
	  { print }' $< > $@
	$(CXX) $(FAST) -fsyntax-only $@
	@echo "gotowe: $@"

clean:
	rm -rf *.e *.o *.dSYM wyslij

.PHONY: all test test_gen szybko wyslij clean
