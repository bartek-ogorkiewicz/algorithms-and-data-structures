#include <bits/stdc++.h>
using namespace std;

#define all(x) (x).begin(), (x).end()
using ll = long long;

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto& s : a) {
        cin >> s;
    }
    long long nie_mam = 0, mam = LLONG_MIN / 2;
    for (int i = 0; i < n; i++) {
        ll nowe_mam = max(nie_mam - a[i], mam);
        ll nowe_nie_mam = max(mam +a[i], nie_mam);
        nie_mam = nowe_nie_mam;
        mam = nowe_mam;
    }
    cout << nie_mam << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}
