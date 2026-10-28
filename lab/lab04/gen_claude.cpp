// generator testów do rob: ./gen.e seed maxn maxm
#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <cstdlib>
#include <random>
using namespace std;

int main(int argc, char **argv) {
    long long seed = atoll(argv[1]), maxn = atoll(argv[2]), maxm = atoll(argv[3]);
    mt19937_64 rng(seed);                // ziarno z argumentu, nie z time(0)
    auto rnd = [&](long long a, long long b) { return a + (long long)(rng() % (b - a + 1)); };

    long long n = rnd(1, maxn);
    long long m = rnd(1, maxm);
    if (rng() % 3 == 0) m = rnd(1, min(maxm, n)); // czasem m < n -> dużo powtórzeń

    // czasem losujemy z małej puli sektorów, żeby wymusić powtórzenia
    vector<long long> pool;
    bool fewSectors = (rng() % 3 == 0);
    if (fewSectors) {
        long long k = rnd(1, min(m, 3LL));
        for (int i = 0; i < k; i++) pool.push_back(rnd(1, m));
    }
    auto sector = [&]() { return fewSectors ? pool[rng() % pool.size()] : rnd(1, m); };

    cout << n << " " << m << "\n";
    for (int i = 0; i < n; i++) cout << sector() << (i + 1 < n ? " " : "\n");
    for (int i = 0; i < n; i++) cout << sector() << (i + 1 < n ? " " : "\n");
}
