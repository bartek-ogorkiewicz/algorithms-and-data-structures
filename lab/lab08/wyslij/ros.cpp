// ros.cpp — zadanie Rosnący podciąg. Logika zadania jest gotowa, brakuje tylko drzewa
// w segtree_gen.h.
//
// Ten sam przebieg co w inw.cpp, inne działanie. Drzewo jest indeksowane WARTOŚCIAMI 1..n:
// a_v w drzewie = długość najdłuższego rosnącego podciągu wśród dotychczas przeczytanych
// elementów, który kończy się wartością v (0, jeśli takiego nie ma).
#include <algorithm>
#include <cstdio>

// segtree_gen.h — drzewo przedziałowe top-down dla dowolnego działania (cel 3)
//
// T — typ wartości, Op — działanie, e — element neutralny działania.
// Przykłady użycia:
//   SegTree<long long, std::plus<long long>> sumy(n, 0);
//   SegTree<int, Max> maksima(n, 0);              // struct Max z ros.cpp
//   SegTree<Lin, Zloz> funkcje(n, Lin{1, 0});      // złożenie funkcji, test_segtree_gen.cpp
//
// Interfejsu nie zmieniaj — korzystają z niego ros.cpp i test_segtree_gen.cpp.
#include <vector>

template <typename T, typename Op>
struct SegTree {
  int n;
  T e;
  Op op;
  int N;
  std::vector<T> a;

  // a_1 = ... = a_n = e
  SegTree(int rozmiar, T neutralny, Op dzialanie = Op())
      : n(rozmiar), e(neutralny), op(dzialanie) {
    int x = 1;
    while (x < n) {
      x *= 2;
    }
    a.assign(2 * x, e);
    N = x;
  }

  // a_k = x, 1 <= k <= n
  void update(int k, T x) {
    int id = N + k - 1;
    a[id] = x;
    id /= 2;
    while (id >= 1) {
      a[id] = op(a[2*id], a[2*id+1]);
      id /= 2;
    }
  }

  // a_l op a_{l+1} op ... op a_r; dla l > r zwraca e
  T query(int l, int r) const {
    int nl = N + l - 1;
    int np = N + r - 1;
    T lewy = e;
    T prawy = e;
    while (nl <= np) {
      if (nl % 2 == 1) {
        lewy = op(lewy, a[nl]);
        nl++;
      }
      if (np % 2 == 0) {
        prawy = op(a[np], prawy);
        np--;
      }
      nl /= 2;
      np /= 2;
    }
    return op(lewy, prawy);
  }
};

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
