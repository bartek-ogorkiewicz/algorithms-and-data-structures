// ============================================================
//  04 SUMY PREFIKSOWE, TABLICA RÓŻNICOWA, KADANE, ZLICZANIE "PO LEWEJ"
// ============================================================
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// ---------- PREFIKSY 1D ----------
// P[0] = 0, P[i] = a[0] + ... + a[i-1]   =>  suma a[l..r] (0-indeks, włącznie) = P[r+1] - P[l]
vector<ll> prefix(const vector<ll>& a) {
    vector<ll> P(a.size() + 1, 0);
    for (size_t i = 0; i < a.size(); i++) P[i + 1] = P[i] + a[i];
    return P;
}
// STL: partial_sum(all(a), P.begin()+1);

// ---------- PREFIKSY 2D ----------
// S[i][j] = suma prostokąta [0,i) x [0,j);  suma [r1..r2] x [c1..c2] włącznie:
struct Prefix2D {
    vector<vector<ll>> S;
    Prefix2D(const vector<vector<ll>>& a) {
        int n = a.size(), m = a[0].size();
        S.assign(n + 1, vector<ll>(m + 1, 0));
        for (int i = 0; i < n; i++) for (int j = 0; j < m; j++)
            S[i + 1][j + 1] = a[i][j] + S[i][j + 1] + S[i + 1][j] - S[i][j];
    }
    ll query(int r1, int c1, int r2, int c2) {
        return S[r2 + 1][c2 + 1] - S[r1][c2 + 1] - S[r2 + 1][c1] + S[r1][c1];
    }
};

// ---------- TABLICA RÓŻNICOWA: "dodaj v na [l, r]" wiele razy, potem odczyt ----------
// D[l] += v; D[r+1] -= v;  na końcu a = prefiksy D.  O(1) na operację.
// Zastosowanie: "ile przedziałów pokrywa punkt x" (v = 1), malowanie płotu, rozkład obciążenia.
vector<ll> applyRangeAdds(int n, const vector<tuple<int,int,ll>>& ops) {
    vector<ll> D(n + 1, 0);
    for (auto [l, r, v] : ops) { D[l] += v; D[r + 1] -= v; }
    vector<ll> a(n); ll cur = 0;
    for (int i = 0; i < n; i++) { cur += D[i]; a[i] = cur; }
    return a;
}

// ---------- KADANE: maksymalna suma spójnego fragmentu (niepustego)  O(n) ----------
ll kadane(const vector<ll>& a) {
    ll best = a[0], cur = 0;
    for (ll x : a) { cur = max(cur + x, x); best = max(best, cur); }
    return best;
}
// wariant przez prefiksy: max_{r} (P[r] - min_{l<r} P[l])  — ten sam trik "min po lewej"

// ---------- LICZBA FRAGMENTÓW O SUMIE DOKŁADNIE K (dowolne znaki)  O(n) ----------
// Fragment [l, r) ma sumę K  <=>  P[r] - P[l] == K  <=>  P[l] == P[r] - K.
// Idziemy po r, trzymając mapę "ile razy widziałem dany prefiks po lewej".
// TEN WZORZEC ("zlicz pasujących partnerów po lewej") rozwiązuje mnóstwo zadań.
ll countSubarraysSumK(const vector<ll>& a, ll K) {
    unordered_map<ll, ll> seen; seen[0] = 1;   // pusty prefiks
    ll P = 0, ans = 0;
    for (ll x : a) {
        P += x;
        auto it = seen.find(P - K);
        if (it != seen.end()) ans += it->second;
        seen[P]++;
    }
    return ans;
}
// warianty tego samego triku:
//  - suma podzielna przez m: klucz = P mod m (uwaga na ujemne: ((P % m) + m) % m)
//  - tyle samo 0 i 1: zamień 0 -> -1, szukaj sumy 0
//  - najdłuższy fragment z sumą K: pamiętaj PIERWSZE wystąpienie prefiksu zamiast licznika
ll countSubarraysDivisible(const vector<ll>& a, ll m) {
    vector<ll> cnt(m, 0); cnt[0] = 1; ll P = 0, ans = 0;
    for (ll x : a) { P = ((P + x) % m + m) % m; ans += cnt[P]++; }
    return ans;
}
int longestSumK(const vector<ll>& a, ll K) {
    unordered_map<ll, int> first; first[0] = 0; ll P = 0; int best = 0;
    for (int i = 0; i < (int)a.size(); i++) {
        P += a[i];
        auto it = first.find(P - K);
        if (it != first.end()) best = max(best, i + 1 - it->second);
        first.emplace(P, i + 1);                // emplace NIE nadpisuje => zostaje pierwsze
    }
    return best;
}

// ---------- SUMA PO WSZYSTKICH PARACH |a_i - a_j|  O(n log n) ----------
// Posortuj; a[i] jest odejmowany przez i mniejszych => wkład a[i]*i - (suma poprzednich)
ll sumAbsDiffPairs(vector<ll> a) {
    sort(a.begin(), a.end()); ll pre = 0, ans = 0;
    for (ll i = 0; i < (ll)a.size(); i++) { ans += a[i] * i - pre; pre += a[i]; }
    return ans;
}

// ======================= SELF-TEST =======================
int main() {
    mt19937 rng(4);
    for (int it = 0; it < 2000; it++) {
        int n = rng() % 12 + 1;
        vector<ll> a(n);
        for (auto& x : a) x = (ll)(rng() % 11) - 5;
        auto P = prefix(a);
        int l = rng() % n, r = l + rng() % (n - l);
        assert(P[r + 1] - P[l] == accumulate(a.begin() + l, a.begin() + r + 1, 0LL));

        ll bk = LLONG_MIN, K = (ll)(rng() % 9) - 4, cK = 0, cD = 0, m = rng() % 4 + 1; int lK = 0;
        for (int i = 0; i < n; i++) { ll s = 0; for (int j = i; j < n; j++) { s += a[j]; bk = max(bk, s);
            if (s == K) { cK++; lK = max(lK, j - i + 1); } if (s % m == 0) cD++; } }
        assert(kadane(a) == bk); assert(countSubarraysSumK(a, K) == cK);
        assert(countSubarraysDivisible(a, m) == cD); assert(longestSumK(a, K) == lK);

        ll sa = 0; for (int i = 0; i < n; i++) for (int j = i + 1; j < n; j++) sa += llabs(a[i] - a[j]);
        assert(sumAbsDiffPairs(a) == sa);

        vector<tuple<int,int,ll>> ops; vector<ll> br(n, 0);
        for (int q = 0; q < 5; q++) { int L = rng() % n, R = L + rng() % (n - L); ll v = rng() % 5; ops.push_back({L, R, v}); for (int i = L; i <= R; i++) br[i] += v; }
        assert(applyRangeAdds(n, ops) == br);

        int R = rng() % 4 + 1, C = rng() % 4 + 1;
        vector<vector<ll>> g(R, vector<ll>(C)); for (auto& row : g) for (auto& x : row) x = rng() % 10;
        Prefix2D p2(g); int r1 = rng() % R, r2 = r1 + rng() % (R - r1), c1 = rng() % C, c2 = c1 + rng() % (C - c1);
        ll s2 = 0; for (int i = r1; i <= r2; i++) for (int j = c1; j <= c2; j++) s2 += g[i][j];
        assert(p2.query(r1, c1, r2, c2) == s2);
    }
    puts("04_sumy_prefiksowe: OK");
}
