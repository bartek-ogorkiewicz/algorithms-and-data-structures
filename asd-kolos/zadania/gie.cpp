// GIE — Giełda: ceny p_1..p_n, kupujesz/sprzedajesz dowolnie wiele razy, max 1 akcja naraz. Max zysk.
// DP 2 stany (nie_mam / mam) albo zachłan: suma dodatnich różnic p[i+1]-p[i]. long long!
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int n; cin >> n;
    vector<ll> p(n); for (auto& x : p) cin >> x;
    ll nie = 0, mam = LLONG_MIN / 2;          // "mam" na start niemożliwe => -INF
    for (ll x : p) {
        ll nn = max(nie, mam + x), nm = max(mam, nie - x);   // TYMCZASOWE zmienne!
        nie = nn; mam = nm;
    }
    cout << nie << "\n";
}
