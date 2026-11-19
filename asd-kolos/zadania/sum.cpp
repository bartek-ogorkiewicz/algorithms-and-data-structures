// SUM — Suma kwadratów różnic kolejnych elementów zbioru po każdym wstawieniu.
// set + sąsiedzi: + (x-p)^2 + (nx-x)^2 - (nx-p)^2. Wszystko w long long! O(n log n).
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int n; cin >> n;
    set<ll> s; ll sum = 0;
    auto sq = [](ll d) { return d * d; };
    for (int i = 0; i < n; i++) {
        ll x; cin >> x;
        auto it = s.insert(x).first;
        bool hp = it != s.begin(), hn = next(it) != s.end();
        if (hp) sum += sq(x - *prev(it));
        if (hn) sum += sq(*next(it) - x);
        if (hp && hn) sum -= sq(*next(it) - *prev(it));
        if (i > 0) cout << sum << "\n";
    }
}
