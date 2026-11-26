//
//
#include <bits/stdc++.h>
using namespace std;

#define all(x) (x).begin(), (x).end()
using ll = long long;

void YES() { cout << "YES" << "\n"; }
void NO()  { cout << "NO" << "\n"; }
void answer(bool b) { b ? YES() : NO(); }

void solve() {
    int n;
    cin >> n;
    vector<int> a(2 * n + 1);
    for (int i = 1; i <= 2 * n; i++) cin >> a[i];

    vector<ll> dp(2 * n + 1, 0);
    vector<int> first(n + 1, 0);
    for (int i = 1; i <= 2 * n; i++) {
        int x = a[i];
        ll cand = dp[i - 1] + 1;
        if (first[x] == 0) {
            first[x] = i;
        } else {
            int f = first[x];
            ll len = i - f + 1;
            cand = max(cand, dp[f - 1] + len * len);
        }
        dp[i] = cand;
    }
    cout << dp[2 * n] << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}
