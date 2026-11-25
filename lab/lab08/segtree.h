// segtree.h — drzewo przedziałowe top-down, działanie: suma (cel 1)
//
// Reprezentowany ciąg a_1, ..., a_n (indeksy od 1). Węzeł v pokrywa przedział [lo, hi],
// korzeń to węzeł 1 z przedziałem [1, n], dzieci węzła v to 2v i 2v+1.
// Tak samo numeruje węzły wizualizacja (wizualizacja-drzewa.html).
//
// Interfejsu (nazw, parametrów, znaczenia) nie zmieniaj — korzystają z niego inw.cpp
// i test_segtree.cpp. Pola i funkcje pomocnicze dopisz sam(a).
#pragma once
#include <vector>

struct SegTree {
  int n;
  int N;
  std::vector<long long> a;
  // a_1 = ... = a_n = 0
  explicit SegTree(int rozmiar) : n(rozmiar) {
    int x = 1;
    while (x < n) {
      x *= 2;
    }
    a.assign(2 * x, 0);
    N = x;
  }

  // a_k = x, 1 <= k <= n
  void update(int k, long long x) {
    int id = N + k - 1;
    long long diff = x - a[id];
    while (id >= 1) {
      a[id] += diff;
      id /= 2;
    }
  }

  // a_l + ... + a_r; dla l > r (przedział pusty) zwraca 0
  long long query(int l, int r) const {
    int nl = N + l - 1;
    int np = N + r - 1;
    long long sum = 0;
    while (nl <= np) {
      if (nl % 2 == 1) {
        sum += a[nl];
        nl++;
      }
      if (np % 2 == 0) {
        sum += a[np];
        np--;
      }
      nl /= 2;
      np /= 2;
    }
    return sum;
  }
};
