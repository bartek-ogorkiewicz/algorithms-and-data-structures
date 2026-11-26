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
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for (auto& s : a) {
        cin >> s;
    }
    vector<int> pref(n + 1, 0);
    for (int i = 1; i <=n; i++) {
        pref[i] = (pref[i - 1] + a[i - 1]) % k;
    }
    vector<int> values(k + 1, 0);
    ll subarrays = 0;
    for (int i = 1; i <= n; i++) {
        if (i - k - 1 >= 0) {
            values[pref[i - k - 1]]++;
        }
        subarrays += values[pref[i]];

    }
    cout << subarrays << '\n';
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
