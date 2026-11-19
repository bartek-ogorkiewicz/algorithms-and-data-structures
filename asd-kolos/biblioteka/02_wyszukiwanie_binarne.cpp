// ============================================================
//  02 WYSZUKIWANIE BINARNE — lower/upper_bound, liczenie w przedziale,
//  wyszukiwanie po wyniku (binsearch on answer), na liczbach rzeczywistych
// ============================================================
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// ---------- ŚCIĄGA STL (na POSORTOWANYM wektorze) ----------
// lower_bound(all(v), x) -> pierwszy element >= x
// upper_bound(all(v), x) -> pierwszy element >  x
// ile elementów == x         : upper_bound(x) - lower_bound(x)
// ile elementów w [lo, hi]   : upper_bound(hi) - lower_bound(lo)
// ile elementów <  x         : lower_bound(x) - v.begin()
// ile elementów <= x         : upper_bound(x) - v.begin()
// ostatni element <= x       : it = upper_bound(x); if (it != v.begin()) --it ...
// ostatni element <  x       : it = lower_bound(x); if (it != v.begin()) --it ...
// Dla set/map: s.lower_bound(x) (METODA!), NIE lower_bound(all(s), x) — to drugie jest O(n)!
ll countInRange(const vector<ll>& v, ll lo, ll hi) {
    return upper_bound(v.begin(), v.end(), hi) - lower_bound(v.begin(), v.end(), lo);
}

// ---------- RĘCZNY BINSEARCH — wzór, który się nie myli ----------
// Szukamy PIERWSZEGO x w [lo, hi], dla którego ok(x) == true,
// gdy ok jest monotoniczne: false false ... false true true ... true
// Niezmiennik: ok(hi) == true zawsze (hi to "kandydat"), wszystko < lo jest false.
template <class F> ll firstTrue(ll lo, ll hi, F ok) {   // zwraca hi+1 gdy brak
    hi++;                                   // hi+1 = "wirtualne true"
    while (lo < hi) {
        ll mid = lo + (hi - lo) / 2;        // bez przepełnienia
        if (ok(mid)) hi = mid; else lo = mid + 1;
    }
    return lo;
}
// OSTATNI x z ok(x) == true (gdy true ... true false ... false):
template <class F> ll lastTrue(ll lo, ll hi, F ok) {     // zwraca lo-1 gdy brak
    lo--;
    while (lo < hi) {
        ll mid = lo + (hi - lo + 1) / 2;    // +1 => zaokrąglenie w górę, inaczej pętla nieskończona
        if (ok(mid)) lo = mid; else hi = mid - 1;
    }
    return lo;
}

// ---------- BINSEARCH PO WYNIKU — przykład: "agresywne krowy" ----------
// n pozycji, postaw k krów, zmaksymalizuj minimalną odległość między krowami.
// Pytanie decyzyjne: "czy da się z odległością >= d?" — monotoniczne w d. Zachłannie O(n).
// Rozpoznasz po: "zminimalizuj maksimum" / "zmaksymalizuj minimum" / "najmniejsze X takie, że...".
ll aggressiveCows(vector<ll> p, int k) {
    sort(p.begin(), p.end());
    auto canPlace = [&](ll d) {
        int placed = 1; ll last = p[0];
        for (size_t i = 1; i < p.size(); i++)
            if (p[i] - last >= d) { placed++; last = p[i]; }
        return placed >= k;
    };
    return lastTrue(0, p.back() - p[0], canPlace);
}

// przykład 2: podziel tablicę na k spójnych kawałków, zminimalizuj max sumę kawałka
ll minMaxSplit(const vector<ll>& a, int k) {
    auto ok = [&](ll lim) {   // czy da się na <= k kawałków o sumie <= lim
        int parts = 1; ll cur = 0;
        for (ll x : a) {
            if (x > lim) return false;
            if (cur + x > lim) { parts++; cur = 0; }
            cur += x;
        }
        return parts <= k;
    };
    return firstTrue(0, accumulate(a.begin(), a.end(), 0LL), ok);
}

// ---------- BINSEARCH NA LICZBACH RZECZYWISTYCH ----------
// Stała liczba iteracji (100) zamiast warunku r-l > eps — zawsze się kończy.
double sqrtBin(double x) {
    double lo = 0, hi = max(1.0, x);
    for (int it = 0; it < 100; it++) {
        double mid = (lo + hi) / 2;
        if (mid * mid < x) lo = mid; else hi = mid;
    }
    return lo;
}

// ---------- BINSEARCH PO INDEKSIE W TABLICY "rosnąco-malejącej" (bitonicznej) ----------
// max w ciągu najpierw ściśle rosnącym potem ściśle malejącym
int bitonicPeak(const vector<ll>& a) {
    return firstTrue(0, (ll)a.size() - 2, [&](ll i) { return a[i] > a[i + 1]; });
}

// ======================= SELF-TEST =======================
int main() {
    mt19937 rng(1);
    for (int it = 0; it < 3000; it++) {
        int n = rng() % 12 + 2;
        vector<ll> v(n);
        for (auto& x : v) x = rng() % 15;
        sort(v.begin(), v.end());
        ll lo = rng() % 15, hi = lo + rng() % 6;
        assert(countInRange(v, lo, hi) == count_if(v.begin(), v.end(), [&](ll x) { return lo <= x && x <= hi; }));

        ll T = rng() % 20;
        ll ft = firstTrue(0, 19, [&](ll x) { return x >= T; });
        assert(ft == T);
        ll lt = lastTrue(0, 19, [&](ll x) { return x <= T; });
        assert(lt == min<ll>(T, 19));

        // krowy: brute po wszystkich podzbiorach
        vector<ll> p(n);
        for (auto& x : p) x = rng() % 30;
        int k = rng() % n + 1;
        ll br = -1;
        vector<ll> ps = p; sort(ps.begin(), ps.end());
        for (int m = 0; m < (1 << n); m++) if (__builtin_popcount(m) == k) {
            ll mn = LLONG_MAX, last = -1;
            for (int i = 0; i < n; i++) if (m >> i & 1) { if (last != -1) mn = min(mn, ps[i] - last); last = ps[i]; }
            if (k == 1) mn = ps.back() - ps[0];   // przy k=1 nasz binsearch zwraca max zakres
            br = max(br, mn);
        }
        assert(aggressiveCows(p, k) == br);

        // min max split: brute po podziałach
        vector<ll> a(n);
        for (auto& x : a) x = rng() % 10;
        int kk = rng() % n + 1;
        ll best = LLONG_MAX;
        for (int m = 0; m < (1 << (n - 1)); m++) if (__builtin_popcount(m) <= kk - 1) {
            ll cur = 0, mx = 0;
            for (int i = 0; i < n; i++) { cur += a[i]; if (i == n - 1 || (m >> i & 1)) { mx = max(mx, cur); cur = 0; } }
            best = min(best, mx);
        }
        assert(minMaxSplit(a, kk) == best);

        // bitoniczny
        vector<ll> b; int up = rng() % 6 + 1, dn = rng() % 6;
        for (int i = 0; i < up; i++) b.push_back(i * 2);
        for (int i = 0; i < dn; i++) b.push_back(up * 2 - 3 - i * 2);
        if (b.size() >= 2) assert(bitonicPeak(b) == up - 1);
    }
    assert(fabs(sqrtBin(2) - sqrt(2.0)) < 1e-9);
    puts("02_wyszukiwanie_binarne: OK");
}
