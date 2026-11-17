#include <bits/stdc++.h>
using namespace std;

#define all(x) (x).begin(), (x).end()
using ll = long long;

void solve() {
    int n, w;
    cin >> n >> w;
    vector<int> a(n);
    for (auto& s : a) {
        cin >> s;
    }

    sort(a.begin(), a.end());

    ll ans = 0;
    int j = 0;
    for (int i = 0; i < n; i++) {
        while(j < i && a[i] > w + (ll)a[j]) {
            j++;
        }
        ans += i - j;
    }
    cout << ans << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}
