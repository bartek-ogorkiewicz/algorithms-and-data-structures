// gen.cpp - generator małych testów: ./gen.e <ziarno>
// To samo ziarno = ten sam test, więc każdy kontrprzykład da się odtworzyć.
// Przy nowym zadaniu zmieniasz tylko część "LOSOWANIE TESTU".

#include <cstdio>
#include <cstdlib>
#include <random>
#include <vector>
using namespace std;

int main(int argc, char **argv) {
  unsigned seed = (argc > 1) ? (unsigned) atoi(argv[1]) : 0;
  mt19937 rng(seed);

  // losowa liczba z przedziału [a, b]
  auto rnd = [&](int a, int b) { return a + (int)(rng() % (b - a + 1)); };

  // LOSOWANIE TESTU - zmień pod format wejścia zadania
  int n = rnd(1, 8);                       // małe n — kontrtest ma być czytelny
  printf("%d\n", n);
  for (int i = 0; i < n; i++)
    printf("%d%c", rnd(-10, 10), i + 1 < n ? ' ' : '\n');


  return 0;
}
