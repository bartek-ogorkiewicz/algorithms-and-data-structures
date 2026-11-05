#include <bits/stdc++.h>
using namespace std;

#define all(x) (x).begin(), (x).end()
using ll = long long;

constexpr long long MAXI = 4 * 100'000'000'000'000LL;
void solve() {
    int n, m;
    cin >> n >> m;
    vector<vector<array<int,3>>> adj(n + 1);
    for (int i = 0; i < m; i++) {
        int a, b, p, c;;
        cin >> a >> b >> p >> c;
        adj[a].push_back({b, p, c});
    }
    set<pair<ll, ll>> U;
    vector<ll> dist(n + 1, MAXI);
    dist[1] = 0;
    for (int i = 1; i <= n; i++) {
        U.insert({dist[i], i});
    }
    while (!U.empty()) {
        auto [d, u] = *U.begin();
        U.erase(U.begin());
        for (auto [bi, pi, ci] : adj[u]) {
            ll koszt = (dist[u] + pi - 1) / pi * pi + ci;
            if (koszt < dist[bi]) {
                U.erase({dist[bi], bi});
                dist[bi] = koszt;
                U.insert({dist[bi], bi});
            }
        }
    }
    for (int i = 1; i <= n; i++) {
        cout << (dist[i] == MAXI ? -1 : dist[i]) << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}
