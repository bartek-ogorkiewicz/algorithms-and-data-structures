#include <bits/stdc++.h>
using namespace std;

#define all(x) (x).begin(), (x).end()
using ll = long long;

struct Seg { int t, id, sign; };

bool Cmp(Seg a, Seg b) {
    return a.t != b.t ? a.t < b.t : a.sign < b.sign;
}

void solve() {
    int n;
    cin >> n;

    vector<Seg> a;
    a.reserve(2 * n);

    for (int i = 0; i < n; i++) {
        int t1, t2, id;
        cin >> t1 >> t2 >> id;
        a.push_back({t1, id, 1});
        a.push_back({t2, id, -1});
    }
    unordered_multiset<int> prezesi;

    sort(all(a), Cmp);
    ll aktualni = 0;
    ll czas = 0;
    ll maxi = 0;
    for (auto& [t, id, sign] : a) {
        auto it = prezesi.find(id);
        if (sign == 1) {
            if (it == prezesi.end()) {
                aktualni++;
            }
            prezesi.insert(id);
        } else {
            prezesi.erase(it);
            auto ix = prezesi.find(id);
            if (ix == prezesi.end()) {
                aktualni--;
            }
        }
        if (aktualni > maxi) {
            maxi = aktualni;
            czas = t;
        }
    }
    cout << czas << " " << maxi << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}
