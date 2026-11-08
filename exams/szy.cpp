#include <bits/stdc++.h>
using namespace std;

#define all(x) (x).begin(), (x).end()
using ll = long long;

void solve() {
    int n;
    cin >> n;
    vector<int> p(n);
    for (auto& a : p) {
        cin >> a;
    }
    int last = -1;
    map<int, int> m;
    int pairs = 0;
    for (int i = 0; i < n; i++) {
        auto it = m.find(p[i]);
        if (it != m.end() && it->second > last) {
            pairs++;
            last = i;
        }
        m[p[i]] = i;

    }
    cout << pairs << "\n";

}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}
