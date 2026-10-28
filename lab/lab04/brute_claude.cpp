// brute force do zadania rob: sprawdza wszystkie n! przydziałów, dla n <= 8
#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <cstdlib>
#include <random>
using namespace std;

int main() {
    long long n, m;
    cin >> n >> m;                       // najpierw n, potem m (jak w treści)
    vector<long long> r(n), t(n);
    for (auto &x : r) cin >> x;
    for (auto &x : t) cin >> x;

    vector<int> f(n);                    // f[i] = numer celu dla robota i
    for (int i = 0; i < n; i++) f[i] = i; // start od 0,1,...,n-1 = najmniejsza permutacja

    long long best = LLONG_MAX;
    do {
        long long sum = 0;               // suma może dojść do 10^14 -> long long
        for (int i = 0; i < n; i++) {
            long long d = llabs(r[i] - t[f[i]]);
            sum += min(d, m - d);        // krótsza droga po okręgu
        }
        best = min(best, sum);
    } while (next_permutation(f.begin(), f.end()));

    cout << best << "\n";
}
