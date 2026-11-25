// test_segtree_gen.cpp — testy jednostkowe segtree_gen.h (cel 3), framework doctest
//
//   make test_gen
#include "doctest.h"

#include <functional>

#include "segtree_gen.h"

TEST_CASE("suma: to samo co segtree.h") {
  SegTree<long long, std::plus<long long>> s(5, 0);
  s.update(2, 7);
  s.update(4, -3);
  CHECK(s.query(1, 5) == 4);
  CHECK(s.query(5, 4) == 0);  // przedział pusty daje element neutralny
}

TEST_CASE("minimum") {
  // TODO: jaki element neutralny? Sprawdź zapytanie o przedział, w którym nikt
  // nie wykonał jeszcze update, i przedział pusty.
}

// Funkcja liniowa f(x) = (a * x + b) mod P.
const long long P = 1'000'000'007;
struct Lin {
  long long a, b;
  long long operator()(long long x) const { return (a * x + b) % P; }
};

// Złożenie: Zloz()(L, R) to funkcja „najpierw L, potem R”, czyli x -> R(L(x)).
// Łączne, element neutralny to identyczność Lin{1, 0}, ale NIE przemienne.
// Sklejenie kosztuje O(1), więc query(l, r) — funkcja „najpierw f_l, ..., na końcu f_r” —
// liczy się w O(log n), a nie przez nakładanie r - l + 1 funkcji po kolei.
struct Zloz {
  Lin operator()(Lin L, Lin R) const { return {R.a * L.a % P, (R.a * L.b + R.b) % P}; }
};

TEST_CASE("złożenie funkcji liniowych — działanie nieprzemienne") {
  SegTree<Lin, Zloz> s(2, Lin{1, 0});
  s.update(1, {2, 0});  // f_1(x) = 2x
  s.update(2, {1, 1});  // f_2(x) = x + 1
  CHECK(s.query(1, 2)(3) == 7);  // f_2(f_1(3)) = 2 * 3 + 1; odwrotna kolejność dałaby 8

  // TODO: dla wielu n wpisz losowe f_1, ..., f_n i dla WSZYSTKICH par l <= r sprawdź,
  // że query(l, r) zastosowane do kilku x daje to samo, co nałożenie f_l, ..., f_r
  // po kolei w pętli. Ustal ziarno, w INFO wypisz n, l, r.
}
