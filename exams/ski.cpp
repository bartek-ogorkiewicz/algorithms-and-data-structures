#include <bits/stdc++.h>
using namespace std;

#define all(x) (x).begin(), (x).end()
using ll = long long;

void solve() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> graph(n + 1);
    vector<int> color(n + 1, -1);
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    queue<int> kol;
    kol.push(1);
    color[1] = 0;
    for (int j = 1; j <= n; j++) {
        if (color[j] == -1) {
            color[j] = 0;
            kol.push(j);
        }
        while (!kol.empty()) {
            int x = kol.front();
            kol.pop();
            for (auto& s : graph[x]) {
                if (color[s] == -1) {
                    color[s] = 1 - color[x];
                    kol.push(s);
                } else if (color[s] == 1 - color[x]) {
                    continue;
                } else {
                    cout << "NIE" << "\n";
                    return;
                }
            }
        }
    }
    cout << "TAK" << "\n";

}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}
