// SKI — Skierowanie: czy da się skierować krawędzie tak, by nie było ścieżki długości 2?
// <=> każdy wierzchołek jest źródłem albo ujściem <=> graf DWUDZIELNY. BFS, graf może być niespójny.
#include <bits/stdc++.h>
using namespace std;
int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int n, m; cin >> n >> m;
    vector<vector<int>> g(n + 1);
    for (int i = 0; i < m; i++) { int a, b; cin >> a >> b; g[a].push_back(b); g[b].push_back(a); }
    vector<int> col(n + 1, -1);
    for (int s = 1; s <= n; s++) if (col[s] == -1) {
        col[s] = 0; queue<int> q; q.push(s);
        while (!q.empty()) {
            int v = q.front(); q.pop();
            for (int u : g[v]) {
                if (col[u] == -1) { col[u] = col[v] ^ 1; q.push(u); }
                else if (col[u] == col[v]) { cout << "NIE\n"; return 0; }
            }
        }
    }
    cout << "TAK\n";
}
