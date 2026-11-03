#include <bits/stdc++.h>
using namespace std;

#define all(x) (x).begin(), (x).end()
using ll = long long;

struct Seg { int x, y, t; };

bool Cmp(Seg a, Seg b) {
    return a.x != b.x ? a.x < b.x : a.y < b.y;
}

void solve() {
    int n;
    cin >> n;
    vector<Seg> ev;
    ev.reserve(2 * n);

    for (int i = 0; i < n; i++) {
        int x, y1, y2;
        cin >> x >> y1 >> y2;
        ev.push_back({x, y1, 1});
        ev.push_back({x, y2, -1});
    }

    sort(all(ev), Cmp);

    ll ans = 0;
    ll active = 0;
    for (auto& [x, y, t] : ev) {
        if (t == 1) {
            ans += active;
            active++;
        } else {
            active--;
        }
    }

    cout << ans << '\n';

}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}
