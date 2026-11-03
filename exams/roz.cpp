#include <bits/stdc++.h>
using namespace std;

#define all(x) (x).begin(), (x).end()
using ll = long long;

void solve() {
    ll n, d;
    cin >> n >> d;
    vector<ll> tab(n);
    for (auto& s : tab) {
        cin >> s;
    }

    sort(tab.begin(), tab.end());

    if (d == 0) {
    for (int i = 0; i + 1 < n; i++) {
        if (tab[i] == tab[i + 1]) {
            cout << tab[i] << " " << tab[i] << "\n";
            return;
        }
    }
    cout << "NIE" << "\n";
    return;
    }

    for (ll v : tab) {
        if (binary_search(tab.begin(), tab.end(), v + d)) {
            cout << v + d << " " << v << "\n";
            return;
        }
    }
    cout << "NIE" << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}
