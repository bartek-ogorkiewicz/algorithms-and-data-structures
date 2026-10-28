// etap 2: sortuje r i t, wypisuje WSZYSTKIE optymalne przydziały f(0..n-1)
// f[i] = indeks celu w POSORTOWANYM t, do którego jedzie i-ty robot (w posortowanym r)
#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <cstdlib>
using namespace std;

int main() {
    long long n, m;
    cin >> n >> m;
    vector<long long> r(n), t(n);
    for (auto &x : r) cin >> x;
    for (auto &x : t) cin >> x;
    sort(r.begin(), r.end());
    sort(t.begin(), t.end());

    vector<int> f(n);
    for (int i = 0; i < n; i++) f[i] = i;

    long long best = LLONG_MAX;
    vector<vector<int>> opt;             // wszystkie przydziały o koszcie best
    do {
        long long sum = 0;
        for (int i = 0; i < n; i++) {
            long long d = llabs(r[i] - t[f[i]]);
            sum += min(d, m - d);
        }
        if (sum < best) { best = sum; opt.clear(); }
        if (sum == best) opt.push_back(f);
    } while (next_permutation(f.begin(), f.end()));

    cout << "m = " << m << "\n";
    cout << "r (posortowane): "; for (auto x : r) cout << x << " "; cout << "\n";
    cout << "t (posortowane): "; for (auto x : t) cout << x << " "; cout << "\n";
    cout << "minimum = " << best << ", optymalnych przydzialow: " << opt.size() << "\n";
    for (auto &g : opt) {
        cout << "  f = ";
        for (auto x : g) cout << x << " ";
        cout << "\n";
    }
}
