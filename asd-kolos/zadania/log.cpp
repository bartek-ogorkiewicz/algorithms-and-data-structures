// LOG — Logi serwera (Lab07, 16.11.2026)
// Max liczba punktów w przedziale [a, a+w] (domkniętym).
// Idea: sortuj; optymalny przedział można przesunąć tak, by zaczynał się w punkcie.
// Dwa wskaźniki: dla każdego prawego końca r przesuwaj l, dopóki t[r]-t[l] > w.
// O(n log n). Uwaga: t do 2e9 mieści się w int, ale t+w już nie => ll.
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n; ll w;
    cin >> n >> w;
    vector<ll> t(n);
    for (auto& x : t) cin >> x;
    sort(t.begin(), t.end());
    int best = 0;
    for (int l = 0, r = 0; r < n; r++) {
        while (t[r] - t[l] > w) l++;
        best = max(best, r - l + 1);
    }
    cout << best << "\n";
}
