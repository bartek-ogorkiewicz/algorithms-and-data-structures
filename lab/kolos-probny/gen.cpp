#include <bits/stdc++.h>
using namespace std;

mt19937 rng;
long long losuj(long long a, long long b) {        // liczba z [a, b], OBA końce włącznie
  return uniform_int_distribution<long long>(a, b)(rng);
}

int main(int argc, char **argv) {
  rng.seed(argc > 1 ? atoi(argv[1]) : 0);           // argv[1] = ziarno
  int nmax       = argc > 2 ? atoi(argv[2])  : 8;   // argv[2] = max n
  long long vmax = argc > 3 ? atoll(argv[3]) : 20;  // argv[3] = max wartość
  long long wmax = argc > 4 ? atoll(argv[4]) : 10;
  // --- od tej linii: format wejścia konkretnego zadania ---
  int n = losuj(1, nmax);
  cout << n << " ";
  int w = losuj(0, wmax);
  cout << w << "\n";
  for (int i = 0; i < n; i++) {
    cout << losuj(0, vmax) << "\n";
  }

}
