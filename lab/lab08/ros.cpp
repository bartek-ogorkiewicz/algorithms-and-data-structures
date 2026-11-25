// ros.cpp — zadanie Rosnący podciąg. Logika zadania jest gotowa, brakuje tylko drzewa
// w segtree_gen.h.
//
// Ten sam przebieg co w inw.cpp, inne działanie. Drzewo jest indeksowane WARTOŚCIAMI 1..n:
// a_v w drzewie = długość najdłuższego rosnącego podciągu wśród dotychczas przeczytanych
// elementów, który kończy się wartością v (0, jeśli takiego nie ma).
#include <algorithm>
#include <cstdio>

#include "segtree_gen.h"

struct Max {
  int operator()(int x, int y) const { return std::max(x, y); }
};

int main() {
  int n;
  if (scanf("%d", &n) != 1) return 1;
  SegTree<int, Max> drzewo(n, 0);  // 0 jest neutralne dla max na liczbach >= 0
  int wynik = 0;
  for (int j = 1; j <= n; j++) {
    int a;
    if (scanf("%d", &a) != 1) return 1;
    // dp_j = 1 + max{dp_i : i < j, a_i < a_j}; wartości 1..a-1 (dla a = 1 przedział pusty)
    int dp = drzewo.query(1, a - 1) + 1;
    // jeśli wartość a już wystąpiła, nowe dp jest nie mniejsze od starego, więc nadpisujemy
    drzewo.update(a, dp);
    wynik = std::max(wynik, dp);
  }
  printf("%d\n", wynik);
}
