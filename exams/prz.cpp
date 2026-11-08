#include <bits/stdc++.h>
using namespace std;

#define all(x) (x).begin(), (x).end()
using ll = long long;

void solve() {
    int n;
    cin >> n;
    vector<pair<int,int>> v(n);
    for (auto &[a, b] : v) cin >> a >> b;
    sort(v.begin(), v.end());
    int maxi = INT_MAX;
    for (int i = 1; i < n; i++) {
        if (v[i].first <= v[i - 1].second) {
            maxi = 0;
            break;
        } else {
            maxi = min(maxi, v[i].first - v[i - 1].second);
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
