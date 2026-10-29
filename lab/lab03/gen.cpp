// gen.cpp — generator testów do din: ./gen.e <ziarno>
#include <cstdio>
#include <cstdlib>
#include <random>
#include <vector>
using namespace std;

int main(int argc, char **argv) {
  unsigned seed = (argc > 1) ? (unsigned) atoi(argv[1]) : 0;
  mt19937 rng(seed);

  int n = 1 + rng() % 100;      // do 100, żeby trafiały się przerwy dłuższe niż K
  int p = rng() % 100;          // gęstość pułapek w tym teście (0–99%)

  vector<int> trap;
  for (int i = 1; i <= n; i++)
    if ((int)(rng() % 100) < p) trap.push_back(i);

  printf("%d %d\n", n, (int) trap.size());
  if (!trap.empty())            // przy m = 0 drugiego wiersza nie ma
    for (size_t i = 0; i < trap.size(); i++)
      printf("%d%c", trap[i], i + 1 < trap.size() ? ' ' : '\n');
  return 0;
}
