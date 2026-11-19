// SZA — Partie towarzyskie (Lab07, 17.11.2026)
// Liczba par i<j z |x_i - x_j| <= w.
// Idea: kolejność nie ma znaczenia (para nieuporządkowana) => sortuj.
// Dla każdego l: r = pierwszy indeks z x[r] - x[l] > w; par z l jako lewym: r - l - 1.
// r tylko rośnie => dwa wskaźniki O(n) po sortowaniu.
// WYNIK do ~1.25e11 => long long!
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n; ll w;
    cin >> n >> w;
    vector<ll> x(n);
    for (auto& v : x) cin >> v;
    sort(x.begin(), x.end());
    ll ans = 0;
    for (int l = 0, r = 0; l < n; l++) {
        while (r < n && x[r] - x[l] <= w) r++;
        ans += r - l - 1;           // pary (l, l+1..r-1)
    }
    cout << ans << "\n";

    // Alternatywa z wyszukiwaniem binarnym (też O(n log n)):
    //   ans += upper_bound(x.begin() + l + 1, x.end(), x[l] + w) - (x.begin() + l + 1);
}
