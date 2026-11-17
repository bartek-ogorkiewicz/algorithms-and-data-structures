#include <bits/stdc++.h>
using namespace std;

#define all(x) (x).begin(), (x).end()
using ll = long long;

void solve() {
    int n;
    int k;
    cin >> n >> k;
    vector<int> a(n);
    for (auto& s : a) {
        cin >> s;
    }
    if (n == 1) {
        cout << 0 << "\n";
        return;
    }
    sort(a.begin(), a.end());
    int maxi = INT_MAX;
    vector<int> pref(n, 0);
    for (int i = 1; i < n; i++) {
        pref[i] = pref[i - 1] + a[i] - a[i - 1];
    }
    int l = k - 1;
    for (int i = 1; i < n; i++) {
        if (i - l >= 0) {
            maxi = min(maxi, pref[i] - pref[i - l]);
        }
    }
    cout << maxi << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}
