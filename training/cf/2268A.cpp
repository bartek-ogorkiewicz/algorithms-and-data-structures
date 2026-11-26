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
    int k;
    cin >> n >> k;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) cin >> a[i];

    ll ans = 0;
    for (int i = k; i <= n - k + 1; i++) ans += a[i];
    int p = min(k - 1, n - k + 1);
    for (int i = 1; i <= p; i++) ans += max(a[i], a[n + 1 - i]);
    cout << ans << '\n';
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
