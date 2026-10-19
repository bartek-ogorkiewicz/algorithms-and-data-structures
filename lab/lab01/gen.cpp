// gen.cpp — generator małych testów: ./gen.e <ziarno>

#include <cstdio>
#include <cstdlib>
#include <random>

using namespace std;

int main(int argc, char **argv) {
  unsigned seed = (argc > 1) ? (unsigned) atoi(argv[1]) : 0;
  mt19937 rng(seed);                      // jawne ziarno = powtarzalny test
  int n = 1 + rng() % 8;                  // małe n — kontrtest ma być czytelny
  printf("%d\n", n);
  for (int i = 0; i < n; i++)
    printf("%d%c", (int) (rng() % 21) - 10, i + 1 < n ? ' ' : '\n');
  return 0;
}
