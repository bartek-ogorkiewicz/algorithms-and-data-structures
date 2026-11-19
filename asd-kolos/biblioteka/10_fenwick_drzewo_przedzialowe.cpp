// ============================================================
//  10 DRZEWO FENWICKA i DRZEWO PRZEDZIAŁOWE
//  Kiedy: tablica ZMIENIA SIĘ między zapytaniami o sumę/min/max na przedziale.
//  (Gdy tablica stała -> wystarczą sumy prefiksowe z 04.)
// ============================================================
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// ---------- FENWICK: dodaj w punkcie, suma prefiksu  O(log n), indeksy 1..n ----------
struct Fenwick {
    int n; vector<ll> t;
    Fenwick(int n_) : n(n_), t(n_ + 1, 0) {}
    void add(int i, ll v) { for (; i <= n; i += i & -i) t[i] += v; }
    ll sum(int i) { ll s = 0; for (; i > 0; i -= i & -i) s += t[i]; return s; }   // a[1..i]
    ll sum(int l, int r) { return sum(r) - sum(l - 1); }                             // a[l..r]
};
// Trik "dodaj na przedziale, pytaj o punkt": add(l, v); add(r+1, -v); wartość = sum(i).

// ---------- INWERSJE FENWICKIEM (alternatywa dla merge sorta) ----------
// Idź od lewej; dla a[i] dolicz ile wcześniejszych jest > a[i]. Wartości duże -> kompresja.
ll inversionsBIT(const vector<ll>& a) {
    vector<ll> v = a; sort(v.begin(), v.end()); v.erase(unique(v.begin(), v.end()), v.end());
    Fenwick f(v.size()); ll inv = 0;
    for (size_t i = 0; i < a.size(); i++) {
        int x = lower_bound(v.begin(), v.end(), a[i]) - v.begin() + 1;   // ranga 1..m
        inv += i - f.sum(x);   // wcześniejsze minus te <= a[i]
        f.add(x, 1);
    }
    return inv;
}
// Inny klasyk tym samym wzorcem: "dla każdego i: ile j < i ma a[j] < a[i]" (np. liczba rosnących par).

// ---------- DRZEWO PRZEDZIAŁOWE (iteracyjne, bottom-up): ustaw w punkcie, zapytanie o przedział ----------
// Operacja op musi być łączna, ID jej element neutralny. Tu: min. Dla sumy: op = +, ID = 0. Dla max: max, ID = -INF.
struct SegTree {
    int n; vector<ll> t;
    static constexpr ll ID = LLONG_MAX;
    static ll op(ll a, ll b) { return min(a, b); }
    SegTree(int n_) : n(n_), t(2 * n_, ID) {}
    SegTree(const vector<ll>& a) : n(a.size()), t(2 * a.size()) {
        for (int i = 0; i < n; i++) t[n + i] = a[i];
        for (int i = n - 1; i > 0; i--) t[i] = op(t[2 * i], t[2 * i + 1]);
    }
    void set(int i, ll v) { for (t[i += n] = v; i > 1; i >>= 1) t[i >> 1] = op(t[i], t[i ^ 1]); }   // indeks od 0
    ll query(int l, int r) {   // [l, r) od 0
        ll res = ID;
        for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if (l & 1) res = op(res, t[l++]);
            if (r & 1) res = op(res, t[--r]);
        }
        return res;
    }
};

// ---------- DRZEWO PRZEDZIAŁOWE Z LENIWĄ PROPAGACJĄ: dodaj na przedziale, suma na przedziale ----------
struct LazySeg {
    int n; vector<ll> sum, lz;
    LazySeg(int n_) : n(n_), sum(4 * n_, 0), lz(4 * n_, 0) {}
    void push(int x, int l, int r) {
        if (!lz[x]) return;
        int m = (l + r) / 2;
        for (auto [c, len] : {pair{2 * x, m - l + 1}, pair{2 * x + 1, r - m}}) { sum[c] += lz[x] * len; lz[c] += lz[x]; }
        lz[x] = 0;
    }
    void add(int a, int b, ll v, int x, int l, int r) {
        if (b < l || r < a) return;
        if (a <= l && r <= b) { sum[x] += v * (r - l + 1); lz[x] += v; return; }
        push(x, l, r); int m = (l + r) / 2;
        add(a, b, v, 2 * x, l, m); add(a, b, v, 2 * x + 1, m + 1, r);
        sum[x] = sum[2 * x] + sum[2 * x + 1];
    }
    ll query(int a, int b, int x, int l, int r) {
        if (b < l || r < a) return 0;
        if (a <= l && r <= b) return sum[x];
        push(x, l, r); int m = (l + r) / 2;
        return query(a, b, 2 * x, l, m) + query(a, b, 2 * x + 1, m + 1, r);
    }
    void add(int a, int b, ll v) { add(a, b, v, 1, 0, n - 1); }   // [a, b] od 0
    ll query(int a, int b) { return query(a, b, 1, 0, n - 1); }
};

// ======================= SELF-TEST =======================
int main() {
    mt19937 rng(11);
    for (int it = 0; it < 500; it++) {
        int n = rng() % 15 + 1;
        vector<ll> a(n); for (auto& x : a) x = rng() % 20;
        Fenwick f(n); for (int i = 0; i < n; i++) f.add(i + 1, a[i]);
        SegTree st(a); LazySeg lz(n); for (int i = 0; i < n; i++) lz.add(i, i, a[i]);
        for (int q = 0; q < 30; q++) {
            int l = rng() % n, r = l + rng() % (n - l); ll v = rng() % 10;
            switch (rng() % 4) {
                case 0: { int i = rng() % n; f.add(i + 1, v - a[i]); lz.add(i, i, v - a[i]); a[i] = v; st.set(i, v); break; }
                case 1: assert(f.sum(l + 1, r + 1) == accumulate(a.begin() + l, a.begin() + r + 1, 0LL)); break;
                case 2: assert(st.query(l, r + 1) == *min_element(a.begin() + l, a.begin() + r + 1)); break;
                case 3: { lz.add(l, r, v); for (int i = l; i <= r; i++) { a[i] += v; f.add(i + 1, v); st.set(i, a[i]); }
                          int L = rng() % n, R = L + rng() % (n - L); assert(lz.query(L, R) == accumulate(a.begin() + L, a.begin() + R + 1, 0LL)); break; }
            }
        }
        ll br = 0; for (int i = 0; i < n; i++) for (int j = i + 1; j < n; j++) br += a[i] > a[j];
        assert(inversionsBIT(a) == br);
    }
    puts("10_fenwick_drzewo_przedzialowe: OK");
}
