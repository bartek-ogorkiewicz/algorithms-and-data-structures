#include <bits/stdc++.h>
using namespace std;

#define all(x) (x).begin(), (x).end()
using ll = long long;

void solve() {
    int n;
    ll l, r;
    cin >> n >> l >> r;
    vector<int> a(n);
    for (auto& s : a) {
        cin >> s;
    }

    ll ans = 0;
    int j = 0;
    int k = 0;
    sort(a.begin(), a.end());
    for (int i = 0; i < n; i++) {
        while (j < i && a[i] - a[j] > r) {
            j++;
        }
        while (k < i && a[i] - a[k] >= l) {
            k++;
        }
        ans += k - j;
    }
    cout << ans << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}
