#include <bits/stdc++.h>
using namespace std;

#define all(x) (x).begin(), (x).end()
using ll = long long;

void solve() {
    set<int> nums;
    int n;
    cin >> n;
    ll sum = 0;
    for (int i = 0; i < n; i++) {
        int s;
        cin >> s;
        auto it = nums.insert(s).first;
        bool hasPrev = (it != nums.begin());
        auto nx = next(it);
        bool hasNext = (nx != nums.end());
        if (hasPrev) {
            long long p = *prev(it);
            sum += (s - p) * (s - p);
        }
        if (hasNext) {
            long long q = *nx;
            sum += (s - q) * (s - q);
        }
        if (hasNext && hasPrev) {
            long long p = *prev(it);
            long long q = *nx;
            sum -= (p - q) * (p - q);
        }
        if (i >= 1) cout << sum << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}
