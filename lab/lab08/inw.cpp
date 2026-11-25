// inw.cpp — zadanie Inwersje. Logika zadania jest gotowa, brakuje tylko drzewa w segtree.h.
//
// Idziemy po ciągu od lewej. Drzewo jest indeksowane WARTOŚCIAMI 1..n:
// a_v w drzewie = ile razy wartość v wystąpiła wśród dotychczas przeczytanych elementów.
#include <cstdio>
#include <vector>

#include "segtree.h"

int main() {
  int n;
  if (scanf("%d", &n) != 1) return 1;
  SegTree drzewo(n);
  std::vector<long long> ile(n + 1, 0);
  for (int j = 1; j <= n; j++) {
    int a;
    if (scanf("%d", &a) != 1) return 1;
    // wcześniejsze elementy ostro większe od a: wartości a+1..n (dla a = n przedział pusty)
    printf("%lld%c", drzewo.query(a + 1, n), j == n ? '\n' : ' ');
    ile[a]++;
    drzewo.update(a, ile[a]);
  }
}
