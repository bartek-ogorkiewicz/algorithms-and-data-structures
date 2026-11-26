//
//
#include <bits/stdc++.h>
using namespace std;

#define all(x) (x).begin(), (x).end()
using ll = long long;

void YES() { cout << "YES" << "\n"; }
void NO()  { cout << "NO" << "\n"; }
void answer(bool b) { b ? YES() : NO(); }

void solve() {
    int n, x, y;
    cin >> n >> x >> y;
    vector<int> p(n);
    for (auto &v : p) cin >> v;

    vector<int> B(p.begin() + x, p.begin() + y);
    vector<int> O(p.begin(), p.begin() + x);
    O.insert(O.end(), p.begin() + y, p.end());

    rotate(B.begin(), min_element(all(B)), B.end());

    vector<int> res;
    res.reserve(n);
    size_t i = 0;
    while (i < O.size() && O[i] < B[0]) res.push_back(O[i++]);
    for (int v : B) res.push_back(v);
    while (i < O.size()) res.push_back(O[i++]);

    for (int j = 0; j < n; j++) cout << res[j] << " \n"[j == n - 1];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}
