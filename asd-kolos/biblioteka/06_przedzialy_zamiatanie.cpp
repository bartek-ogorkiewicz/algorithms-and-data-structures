// ============================================================
//  06 PRZEDZIAŁY I ZAMIATANIE (sweep line)
//  Przedziały prawie zawsze: SORTUJ (po początku albo po końcu) + przejdź raz.
// ============================================================
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using P = pair<ll, ll>;   // [l, r] domknięty

// ---------- SCALANIE PRZEDZIAŁÓW (suma mnogościowa) ----------
// sortuj po l; jeśli następny zaczyna się <= bieżący koniec => skleja się.
// Dla przedziałów CAŁKOWITYCH, gdy [1,3] i [4,5] też mają się kleić: warunek l <= cur.r + 1
vector<P> mergeIntervals(vector<P> v) {
    sort(v.begin(), v.end());
    vector<P> res;
    for (auto [l, r] : v) {
        if (!res.empty() && l <= res.back().second) res.back().second = max(res.back().second, r);
        else res.push_back({l, r});
    }
    return res;
}
// łączna długość pokryta = suma (r - l) po scalonych

// ---------- MAKS. LICZBA NACHODZĄCYCH SIĘ PRZEDZIAŁÓW W PUNKCIE (zdarzenia) ----------
// Zdarzenia: (l, +1), (r, -1). DOMKNIĘTE przedziały: przy tym samym x najpierw +1, potem -1
// => koduj koniec jako (r, +1) z typem tak, by sort dał start przed końcem.
// Półotwarte [l, r): najpierw -1 (koniec), potem +1.
int maxOverlap(const vector<P>& v) {
    vector<pair<ll,int>> ev;
    for (auto [l, r] : v) { ev.push_back({l, -1}); ev.push_back({r, +1}); }  // -1 = start (sortuje się pierwszy)
    sort(ev.begin(), ev.end());
    int cur = 0, best = 0;
    for (auto [x, t] : ev) {
        if (t == -1) cur++; else cur--;
        best = max(best, cur);
    }
    return best;
}
// To samo daje minimalną liczbę sal / maszyn / kolorów dla przedziałów (interval graph coloring).

// ---------- MAKS. LICZBA ROZŁĄCZNYCH PRZEDZIAŁÓW (activity selection) — ZACHŁAN ----------
// sortuj po KOŃCU, bierz każdy, który zaczyna się po końcu ostatnio wziętego.
// (domknięte i stykające się końcem są kolizją => l > lastEnd)
int maxDisjoint(vector<P> v) {
    sort(v.begin(), v.end(), [](P a, P b) { return a.second < b.second; });
    int cnt = 0; ll lastEnd = LLONG_MIN;
    for (auto [l, r] : v) if (l > lastEnd) { cnt++; lastEnd = r; }
    return cnt;
}
// Pokrewne: min liczba punktów przebijających wszystkie przedziały = ten sam wynik
// (punkt stawiasz na końcu każdego wybranego).

// ---------- WAŻONY WYBÓR PRZEDZIAŁÓW (zadanie PRO)  DP + binsearch  O(n log n) ----------
// dp[i] = najlepszy wynik używając przedziałów i..n-1 (posortowanych po początku)
// dp[i] = max(dp[i+1], w_i + dp[j]),  j = pierwszy z l_j > r_i  (upper_bound)
struct Job { ll l, r, w; };
ll weightedIntervals(vector<Job> v) {
    sort(v.begin(), v.end(), [](const Job& a, const Job& b) { return a.l < b.l; });
    int n = v.size();
    vector<ll> starts(n); for (int i = 0; i < n; i++) starts[i] = v[i].l;
    vector<ll> dp(n + 1, 0);
    for (int i = n - 1; i >= 0; i--) {
        int j = upper_bound(starts.begin(), starts.end(), v[i].r) - starts.begin();  // l_j > r_i
        dp[i] = max(dp[i + 1], v[i].w + dp[j]);
    }
    return dp[0];
}

// ---------- LICZBA PAR PRZECINAJĄCYCH SIĘ PRZEDZIAŁÓW  O(n log n) ----------
// Para się NIE przecina <=> jeden kończy się przed początkiem drugiego.
// rozłączne = suma po i: #(j : r_j < l_i);  wynik = n(n-1)/2 - rozłączne. (Zadanie ODC: grupuj po x.)
ll countIntersectingPairs(const vector<P>& v) {
    ll n = v.size();
    vector<ll> ends; for (auto [l, r] : v) ends.push_back(r);
    sort(ends.begin(), ends.end());
    ll disjoint = 0;
    for (auto [l, r] : v) disjoint += lower_bound(ends.begin(), ends.end(), l) - ends.begin();  // r_j < l
    return n * (n - 1) / 2 - disjoint;
}

// ---------- ILE PRZEDZIAŁÓW ZAWIERA PUNKT q (offline, wiele zapytań) ----------
// #(l <= q) - #(r < q)   — dwa posortowane wektory + binsearch
ll coverCount(const vector<ll>& Ls, const vector<ll>& Rs, ll q) {   // Ls, Rs posortowane
    return (upper_bound(Ls.begin(), Ls.end(), q) - Ls.begin()) - (lower_bound(Rs.begin(), Rs.end(), q) - Rs.begin());
}

// ---------- CZY JAKIŚ PRZEDZIAŁ ZAWIERA INNY ----------
// sortuj po l rosnąco, przy remisie r MALEJĄCO; jeśli r_i <= max dotychczasowych r => i jest zawarty.
vector<bool> isContained(const vector<P>& v) {
    int n = v.size(); vector<int> id(n); iota(id.begin(), id.end(), 0);
    sort(id.begin(), id.end(), [&](int a, int b) { return v[a].first != v[b].first ? v[a].first < v[b].first : v[a].second > v[b].second; });
    vector<bool> res(n); ll mxR = LLONG_MIN;
    for (int i : id) { res[i] = v[i].second <= mxR; mxR = max(mxR, v[i].second); }
    return res;
}

// ======================= SELF-TEST =======================
int main() {
    mt19937 rng(6);
    for (int it = 0; it < 2000; it++) {
        int n = rng() % 9 + 1;
        vector<P> v(n);
        for (auto& [l, r] : v) { l = rng() % 15; r = l + rng() % 6; }
        // scalanie
        vector<bool> cov(25, false); for (auto [l, r] : v) for (ll x = l; x <= r; x++) cov[x] = true;
        auto m = mergeIntervals(v);
        for (ll x = 0; x < 25; x++) { bool in = false; for (auto [l, r] : m) in |= l <= x && x <= r; assert(in == cov[x]); }
        for (size_t i = 0; i + 1 < m.size(); i++) assert(m[i].second < m[i + 1].first);
        // overlap
        int bo = 0; for (ll x = 0; x < 25; x++) { int c = 0; for (auto [l, r] : v) c += l <= x && x <= r; bo = max(bo, c); }
        assert(maxOverlap(v) == bo);
        // disjoint + weighted: brute po podzbiorach
        vector<Job> jobs; for (auto [l, r] : v) jobs.push_back({l, r, (ll)(rng() % 10)});
        int bd = 0; ll bw = 0;
        for (int msk = 0; msk < (1 << n); msk++) {
            bool ok = true; ll w = 0;
            for (int i = 0; i < n; i++) if (msk >> i & 1) { w += jobs[i].w;
                for (int j = i + 1; j < n; j++) if (msk >> j & 1) if (!(v[i].second < v[j].first || v[j].second < v[i].first)) ok = false; }
            if (ok) { bd = max(bd, __builtin_popcount(msk)); bw = max(bw, w); }
        }
        assert(maxDisjoint(v) == bd); assert(weightedIntervals(jobs) == bw);
        // pary przecinające
        ll bp = 0; for (int i = 0; i < n; i++) for (int j = i + 1; j < n; j++) bp += !(v[i].second < v[j].first || v[j].second < v[i].first);
        assert(countIntersectingPairs(v) == bp);
        // cover
        vector<ll> Ls, Rs; for (auto [l, r] : v) { Ls.push_back(l); Rs.push_back(r); }
        sort(Ls.begin(), Ls.end()); sort(Rs.begin(), Rs.end());
        ll q = rng() % 22; ll bc = 0; for (auto [l, r] : v) bc += l <= q && q <= r;
        assert(coverCount(Ls, Rs, q) == bc);
        // zawieranie
        auto ic = isContained(v);
        for (int i = 0; i < n; i++) {
            bool c = false, dup = false;
            for (int j = 0; j < n; j++) if (j != i) {
                if (v[j] == v[i]) dup = true;
                if (v[j].first <= v[i].first && v[i].second <= v[j].second) c = true;
            }
            if (!dup) assert(ic[i] == c);   // przy duplikatach jeden z nich zostaje "niezawarty"
        }
    }
    puts("06_przedzialy_zamiatanie: OK");
}
