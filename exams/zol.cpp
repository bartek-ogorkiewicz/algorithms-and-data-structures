#include <bits/stdc++.h>
using namespace std;

#define all(x) (x).begin(), (x).end()
using ll = long long;

void solve() {
    int n;
    cin >> n;
    set<int> zol;
    for (int i = 1; i <= n; i++) {
        zol.insert(i);
    }
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        auto it = zol.find(x);
        if (it != zol.begin()) {
            auto pv = prev(it);
            cout << *pv << " ";
        } else {
            cout << -1 << " ";
        }
        auto nx = next(it);
        if (nx != zol.end()) {
            cout << *nx << "\n";
        } else {
            cout << -1 << "\n";
        }
        zol.erase(it);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}
