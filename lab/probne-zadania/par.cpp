#include <bits/stdc++.h>
using namespace std;

#define all(x) (x).begin(), (x).end()
using ll = long long;

void solve() {
    int n;
    ll s;
    cin >> n >> s;
    vector<int> a(n);
    for (auto& s : a) {
        cin >> s;
    }
    sort(a.begin(), a.end());
    int j = n - 1;
    ll ans = 0;
    for (int i = 0; i < j; i++) {
        while (i < j && (ll)a[i] + a[j] > s) {
            j--;
        }
        ans += j - i;
    }
    cout << ans << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}
