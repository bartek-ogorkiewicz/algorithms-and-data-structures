// ============================================================
//  08 PROGRAMOWANIE DYNAMICZNE — klasyki
//  Przepis: 1) co to jest stan dp[...] (zdanie po polsku!)  2) przejście
//           3) warunki brzegowe  4) kolejność liczenia  5) gdzie wynik
//  Pamięć: jeśli dp[i] zależy tylko od dp[i-1] -> trzymaj 2 wiersze / zmienne.
// ============================================================
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll MOD = 1e9 + 7;

// ---------- LIS: najdłuższy ściśle rosnący podciąg  O(n log n) ----------
// d[k] = najmniejszy możliwy ostatni element rosnącego podciągu długości k+1.
// Niemalejący: upper_bound zamiast lower_bound.
int lis(const vector<ll>& a) {
    vector<ll> d;
    for (ll x : a) {
        auto it = lower_bound(d.begin(), d.end(), x);
        if (it == d.end()) d.push_back(x); else *it = x;
    }
    return d.size();
}

// ---------- PLECAK 0/1  O(n * W) ----------
// dp[c] = max wartość przy wadze <= c. Pętla po c MALEJĄCO (każdy przedmiot raz).
// Plecak nieograniczony (każdy ile razy chcesz): pętla po c ROSNĄCO.
ll knapsack01(const vector<int>& wt, const vector<ll>& val, int W) {
    vector<ll> dp(W + 1, 0);
    for (size_t i = 0; i < wt.size(); i++)
        for (int c = W; c >= wt[i]; c--) dp[c] = max(dp[c], dp[c - wt[i]] + val[i]);
    return dp[W];
}

// ---------- MONETY: liczba sposobów (kolejność nieważna) i min liczba monet ----------
ll coinWays(const vector<int>& coins, int S) {      // mod MOD
    vector<ll> dp(S + 1, 0); dp[0] = 1;
    for (int c : coins) for (int s = c; s <= S; s++) dp[s] = (dp[s] + dp[s - c]) % MOD;
    return dp[S];   // pętle zamienione (s na zewnątrz) => liczy UPORZĄDKOWANE ciągi
}
int coinMin(const vector<int>& coins, int S) {      // -1 gdy się nie da
    vector<int> dp(S + 1, INT_MAX); dp[0] = 0;
    for (int s = 1; s <= S; s++) for (int c : coins) if (c <= s && dp[s - c] != INT_MAX) dp[s] = min(dp[s], dp[s - c] + 1);
    return dp[S] == INT_MAX ? -1 : dp[S];
}

// ---------- LCS i ODLEGŁOŚĆ EDYCYJNA  O(n m) ----------
int lcs(const string& a, const string& b) {
    int n = a.size(), m = b.size(); vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
    for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++)
        dp[i][j] = a[i - 1] == b[j - 1] ? dp[i - 1][j - 1] + 1 : max(dp[i - 1][j], dp[i][j - 1]);
    return dp[n][m];
}
int editDistance(const string& a, const string& b) {
    int n = a.size(), m = b.size(); vector<vector<int>> dp(n + 1, vector<int>(m + 1));
    for (int i = 0; i <= n; i++) dp[i][0] = i;
    for (int j = 0; j <= m; j++) dp[0][j] = j;
    for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++)
        dp[i][j] = min({dp[i - 1][j] + 1, dp[i][j - 1] + 1, dp[i - 1][j - 1] + (a[i - 1] != b[j - 1])});
    return dp[n][m];
}

// ---------- GIEŁDA (zadanie GIE): kup/sprzedaj dowolnie wiele razy, max 1 akcja ----------
// stany: nie_mam / mam. Uwaga: dp "mam" na starcie = -INF (nie można mieć akcji przed kupnem)
ll stock(const vector<ll>& p) {
    ll nie = 0, mam = LLONG_MIN / 2;
    for (ll x : p) { ll nn = max(nie, mam + x), nm = max(mam, nie - x); nie = nn; mam = nm; }   // tymczasowe!
    return nie;   // == suma dodatnich różnic p[i+1]-p[i] (zachłan)
}

// ---------- ZLICZANIE PODCIĄGÓW: wzorzec "ile kończy się na wartości v" (zadanie POD) ----------
// Liczba ściśle rosnących podciągów (niepustych) ciągu o wartościach 1..K:
// end[v] = liczba podciągów kończących się wartością v. Nowy a_i = v: end[v] += 1 + sum(end[u<v])
// Dla dużych K: sum(end[u<v]) z drzewa Fenwicka (10_drzewa).
ll countIncreasing(const vector<int>& a, int K) {
    vector<ll> end(K + 1, 0);
    for (int v : a) { ll s = 1; for (int u = 1; u < v; u++) s += end[u]; end[v] += s; }
    return accumulate(end.begin(), end.end(), 0LL);
}

// ---------- ŚCIEŻKI NA KRATCE z przeszkodami ('#') ----------
ll gridPaths(const vector<string>& g) {
    int n = g.size(), m = g[0].size(); vector<vector<ll>> dp(n, vector<ll>(m, 0));
    for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) {
        if (g[i][j] == '#') continue;
        if (i == 0 && j == 0) { dp[i][j] = 1; continue; }
        if (i) dp[i][j] += dp[i - 1][j];
        if (j) dp[i][j] += dp[i][j - 1];
        dp[i][j] %= MOD;
    }
    return dp[n - 1][m - 1];
}

// ---------- DP NA PRZEDZIAŁACH: dp[l][r] (np. palindromy, nawiasowanie, gra) ----------
// Gra: ze stosu monet bierzesz z lewej albo prawej, przeciwnik optymalnie. Ile max zdobędziesz?
// dp[l][r] = max wyniku (ja - przeciwnik) na a[l..r]. Liczymy po rosnącej długości.
ll coinGameDiff(const vector<ll>& a) {
    int n = a.size(); vector<vector<ll>> dp(n, vector<ll>(n, 0));
    for (int len = 1; len <= n; len++) for (int l = 0; l + len - 1 < n; l++) {
        int r = l + len - 1;
        if (len == 1) dp[l][r] = a[l];
        else dp[l][r] = max(a[l] - dp[l + 1][r], a[r] - dp[l][r - 1]);
    }
    return dp[0][n - 1];
}

// ---------- MAKSYMALNA SUMA BEZ DWÓCH SĄSIEDNICH (house robber) ----------
ll noAdjacent(const vector<ll>& a) {
    ll take = 0, skip = 0;   // take = biorę bieżący, skip = nie biorę
    for (ll x : a) { ll nt = skip + x, ns = max(take, skip); take = nt; skip = ns; }
    return max(take, skip);
}

// ---------- DP NA MASKACH (n <= 20): komiwojażer / przydział ----------
// dp[mask][v] = min koszt odwiedzenia zbioru mask kończąc w v
ll tsp(const vector<vector<ll>>& d) {
    int n = d.size(); const ll INF = LLONG_MAX / 4;
    vector<vector<ll>> dp(1 << n, vector<ll>(n, INF)); dp[1][0] = 0;
    for (int m = 1; m < (1 << n); m++) for (int v = 0; v < n; v++) if (dp[m][v] < INF)
        for (int u = 0; u < n; u++) if (!(m >> u & 1)) dp[m | 1 << u][u] = min(dp[m | 1 << u][u], dp[m][v] + d[v][u]);
    ll best = INF; for (int v = 0; v < n; v++) best = min(best, dp[(1 << n) - 1][v] + d[v][0]);
    return best;
}

// ======================= SELF-TEST =======================
int main() {
    mt19937 rng(9);
    for (int it = 0; it < 1500; it++) {
        int n = rng() % 9 + 1;
        vector<ll> a(n); for (auto& x : a) x = rng() % 8;
        int bl = 0; ll bnoadj = 0;
        for (int m = 0; m < (1 << n); m++) {
            vector<ll> s; bool adj = false; ll sum = 0; int last = -5;
            for (int i = 0; i < n; i++) if (m >> i & 1) { s.push_back(a[i]); sum += a[i]; if (i == last + 1) adj = true; last = i; }
            bool inc = true; for (size_t i = 1; i < s.size(); i++) inc &= s[i - 1] < s[i];
            if (inc) bl = max(bl, (int)s.size());
            if (!adj) bnoadj = max(bnoadj, sum);
        }
        assert(lis(a) == bl); assert(noAdjacent(a) == bnoadj);

        vector<int> wt(n); vector<ll> val(n); for (int i = 0; i < n; i++) { wt[i] = rng() % 6 + 1; val[i] = rng() % 10; }
        int W = rng() % 15; ll bk = 0;
        for (int m = 0; m < (1 << n); m++) { int w = 0; ll v = 0; for (int i = 0; i < n; i++) if (m >> i & 1) { w += wt[i]; v += val[i]; } if (w <= W) bk = max(bk, v); }
        assert(knapsack01(wt, val, W) == bk);

        ll bs = 0; for (int i = 0; i + 1 < n; i++) bs += max(0LL, a[i + 1] - a[i]);
        assert(stock(a) == bs);

        vector<int> c(n); for (auto& x : c) x = rng() % 3 + 1; ll bc = 0;
        for (int m = 1; m < (1 << n); m++) { int last = 0; bool ok = true; for (int i = 0; i < n; i++) if (m >> i & 1) { ok &= c[i] > last; last = c[i]; } bc += ok; }
        assert(countIncreasing(c, 3) == bc);

        // gra: brute minimax
        function<ll(int,int)> g = [&](int l, int r) -> ll { if (l > r) return 0; return max(a[l] - g(l + 1, r), a[r] - g(l, r - 1)); };
        assert(coinGameDiff(a) == g(0, n - 1));
    }
    assert(coinWays({1, 2, 5}, 5) == 4); assert(coinMin({2, 5}, 3) == -1); assert(coinMin({1, 3, 4}, 6) == 2);
    assert(lcs("ABCBDAB", "BDCABA") == 4); assert(editDistance("kitten", "sitting") == 3);
    assert(gridPaths({"...", ".#.", "..."}) == 2);
    assert(tsp({{0, 1, 15, 6}, {2, 0, 7, 3}, {9, 6, 0, 12}, {10, 4, 8, 0}}) == 21);
    puts("08_dp: OK");
}
