// test_segtree.cpp — testy jednostkowe segtree.h (cel 2), framework doctest
//
//   make test                 # kompiluje i uruchamia wszystkie testy
//   ./test_segtree.e -s       # wypisuje też udane sprawdzenia
//   ./test_segtree.e -tc="*brzeg*"   # tylko testy, których nazwa pasuje do wzorca
//
// CHECK(w)    — sprawdza w, przy porażce wypisuje obie strony porównania i idzie dalej;
// REQUIRE(w)  — to samo, ale przerywa bieżący TEST_CASE;
// INFO(x)     — dopisuje x do komunikatu o porażce (np. ziarno, n, l, r);
// SUBCASE("…") — wariant wewnątrz TEST_CASE, każdy uruchamiany osobno od początku przypadku.
#include "doctest.h"

#include <vector>

#include "segtree.h"

TEST_CASE("przykład: kilka operacji na n = 5") {
  SegTree s(5);
  CHECK(s.query(1, 5) == 0);
  s.update(2, 7);
  s.update(4, -3);
  CHECK(s.query(1, 5) == 4);
  CHECK(s.query(3, 5) == -3);
  s.update(2, 1);  // update nadpisuje, nie dodaje
  CHECK(s.query(1, 2) == 1);
}

TEST_CASE("losowe operacje kontra naiwna tablica") {
  // TODO: dla wielu n (także małych) wykonaj na przemian losowe update i query na drzewie
  // i na zwykłym std::vector; po każdym query porównaj wynik z sumą policzoną pętlą.
  // Ustal ziarno generatora, żeby porażkę dało się powtórzyć, i dopisz INFO z n, l, r.
}

TEST_CASE("przypadki brzegowe") {
  // TODO: n = 1; n niebędące potęgą dwójki (sprawdź WSZYSTKIE przedziały);
  // przedział jednoelementowy; przedział pusty (l > r); wartości, które nie mieszczą się w int.
}
