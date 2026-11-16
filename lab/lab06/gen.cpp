#include <bits/stdc++.h>
using namespace std;

mt19937 rng;
long long losuj(long long a, long long b) {        // liczba z [a, b], OBA końce włącznie
  return uniform_int_distribution<long long>(a, b)(rng);
}

int main(int argc, char **argv) {
  rng.seed(argc > 1 ? atoi(argv[1]) : 0);           // argv[1] = ziarno
  int nmax       = argc > 2 ? atoi(argv[2])  : 10;   // argv[2] = max n
  long long amax = argc > 3 ? atoll(argv[3]) : 1000000000;  // argv[3] = max wartość
  // --- od tej linii: format wejścia konkretnego zadania ---
  int n = losuj(1, nmax);
  cout << n << "\n";
  for (int i = 0; i < n; i++) {
    cout << losuj(1, amax) << " ";
  }

}
