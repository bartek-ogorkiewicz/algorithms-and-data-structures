// PRO — Projekty (ważony wybór rozłącznych przedziałów). FORMAT WEJŚCIA SPRAWDŹ W TREŚCI —
// tu założone: n, potem n wierszy "l r w" (przedział domknięty [l, r], zapłata w).
// Sortuj po l; dp[i] = max(dp[i+1], w_i + dp[j]), j = pierwszy projekt z l_j > r_i (upper_bound).
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
struct Job { ll l, r, w; };
int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int n; cin >> n;
    vector<Job> v(n);
    for (auto& [l, r, w] : v) cin >> l >> r >> w;
    sort(v.begin(), v.end(), [](const Job& a, const Job& b) { return a.l < b.l; });
    vector<ll> st(n); for (int i = 0; i < n; i++) st[i] = v[i].l;
    vector<ll> dp(n + 1, 0);
    for (int i = n - 1; i >= 0; i--) {
        int j = upper_bound(st.begin(), st.end(), v[i].r) - st.begin();
        dp[i] = max(dp[i + 1], v[i].w + dp[j]);
    }
    cout << dp[0] << "\n";
}
