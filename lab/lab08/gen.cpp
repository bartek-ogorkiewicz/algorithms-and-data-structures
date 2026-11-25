// gen.cpp — losowe wejście do inw i ros: ./gen.e <ziarno> [n] [amax]
// n elementów z [1, min(n, amax)]; małe amax daje dużo powtórzeń.
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <random>

int main(int argc, char **argv) {
  std::mt19937 rng(argc > 1 ? atoi(argv[1]) : 0);
  int n = argc > 2 ? atoi(argv[2]) : 10;
  int amax = std::min(n, argc > 3 ? atoi(argv[3]) : n);
  std::uniform_int_distribution<int> los(1, amax);
  printf("%d\n", n);
  for (int i = 1; i <= n; i++) printf("%d%c", los(rng), i == n ? '\n' : ' ');
}
