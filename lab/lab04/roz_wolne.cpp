
#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <cstdlib>
#include <random>
using namespace std;

int main() {
    long long n, m;
    cin >> n >> m;
    vector<long long> r(n), t(n);
    for (auto &x : r) cin >> x;
    for (auto &x : t) cin >> x;

    sort(r.begin(), r.end());
    sort(t.begin(), t.end());

    long long sum;

    long long best = LLONG_MAX;
    for (int k = 0; k < n; k++) {
        sum = 0;
        for (int i = 0; i < n; i++) {
            long long d = llabs(r[i] - t[(i + k) % n]);
            sum += min(m - d, d);
        }
        best = min(best, sum);
    }

    cout << best << "\n";
}
