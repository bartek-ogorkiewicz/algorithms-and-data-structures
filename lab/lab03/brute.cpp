//
//
#include <bits/stdc++.h>
using namespace std;

#define all(x) (x).begin(), (x).end()
using ll = long long;

void YES() { cout << "YES" << "\n"; }
void NO()  { cout << "NO" << "\n"; }
void answer(bool b) { b ? YES() : NO(); }

const ll INF = 1000000000000;
void solve() {
    int n;
    int m;
    cin >> n >> m;

    vector<int> tab(n + 1, 0);
    vector<ll> dp(n + 1, INF);
    for (int i = 0; i < m; i++) {
        int x;
        cin >> x;
        tab[x] = 1;
    }

    const int ruchy[3][2] = {
        {1, 1},
        {5, 10},
        {10, 100}
    };

    dp[0] = 0;
    for (int i = 1; i <= n; i++) {
        if (tab[i] == 1) {
            dp[i] = INF;
        } else {
            for (auto& [dl, koszt] : ruchy) {
                if (i >= dl) {
                    dp[i] = min(dp[i], dp[i - dl] + koszt);
                }
            }
        }
    }
    cout << (dp[n] == INF ? -1 : dp[n]) << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}
