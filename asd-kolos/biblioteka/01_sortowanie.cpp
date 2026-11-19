// ============================================================
//  01 SORTOWANIE — merge sort + inwersje, counting sort, radix sort,
//  quickselect / k-ty element, kompresja współrzędnych, argsort, komparatory
//  Uruchom self-test:  g++ -O2 -std=c++20 01_sortowanie.cpp && ./a.out
// ============================================================
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// ---------- MERGE SORT + LICZBA INWERSJI  O(n log n) ----------
// inwersja = para i<j z a[i] > a[j].  Wynik do n^2/2 => ll.
// Typowe przebrania: "ile zamian sąsiadów, by posortować", "ile par wyprzedzeń".
ll mergeSortInv(vector<ll>& a, int l, int r, vector<ll>& tmp) {   // sortuje a[l..r)
    if (r - l <= 1) return 0;
    int m = (l + r) / 2;
    ll inv = mergeSortInv(a, l, m, tmp) + mergeSortInv(a, m, r, tmp);
    int i = l, j = m, k = l;
    while (i < m && j < r) {
        if (a[i] <= a[j]) tmp[k++] = a[i++];        // <= : równe NIE są inwersją, sort stabilny
        else { inv += m - i; tmp[k++] = a[j++]; }   // a[j] mniejszy od wszystkich a[i..m)
    }
    while (i < m) tmp[k++] = a[i++];
    while (j < r) tmp[k++] = a[j++];
    for (int t = l; t < r; t++) a[t] = tmp[t];
    return inv;
}
ll countInversions(vector<ll> a) { vector<ll> tmp(a.size()); return mergeSortInv(a, 0, a.size(), tmp); }

// ---------- COUNTING SORT  O(n + K), wartości w [0, K) ----------
// Gdy wartości małe (np. <= 10^6). Stabilny wariant (przez prefiksy) — potrzebny w radix sorcie.
vector<int> countingSort(const vector<int>& a, int K) {
    vector<int> cnt(K + 1, 0), out(a.size());
    for (int x : a) cnt[x + 1]++;
    for (int i = 0; i < K; i++) cnt[i + 1] += cnt[i];   // cnt[v] = ile elementów < v = pozycja startowa
    for (int x : a) out[cnt[x]++] = x;                  // przechodzimy w kolejności => stabilnie
    return out;
}

// ---------- RADIX SORT  O(n) dla liczb 32-bitowych nieujemnych ----------
// 2 przebiegi counting sortu po 16 bitów. Od NIŻSZEJ cyfry; każdy przebieg STABILNY.
void radixSort(vector<unsigned>& a) {
    vector<unsigned> tmp(a.size());
    for (int shift = 0; shift < 32; shift += 16) {
        vector<int> cnt(1 << 16 | 1, 0);
        for (unsigned x : a) cnt[((x >> shift) & 0xFFFF) + 1]++;
        for (int i = 0; i < (1 << 16); i++) cnt[i + 1] += cnt[i];
        for (unsigned x : a) tmp[cnt[(x >> shift) & 0xFFFF]++] = x;
        a.swap(tmp);
    }
}

// ---------- K-TY NAJMNIEJSZY  średnio O(n) ----------
// Na kolosie: nth_element(a.begin(), a.begin()+k, a.end());  a[k] = k-ty (od 0)
// Mediana: k = n/2.  Poniżej ręczny quickselect (gdyby zakazali STL / na teorię).
mt19937 rng_qs(123);
ll quickselect(vector<ll> a, int k) {          // k od 0
    int l = 0, r = a.size() - 1;
    while (true) {
        if (l == r) return a[l];
        ll p = a[l + rng_qs() % (r - l + 1)];  // LOSOWY pivot => brak złośliwego O(n^2)
        // podział na 3 części: < p, == p, > p  (ważne przy wielu równych!)
        int lt = l, i = l, gt = r;
        while (i <= gt) {
            if (a[i] < p) swap(a[lt++], a[i++]);
            else if (a[i] > p) swap(a[i], a[gt--]);
            else i++;
        }
        if (k < lt) r = lt - 1;
        else if (k > gt) l = gt + 1;
        else return p;
    }
}

// ---------- KOMPRESJA WSPÓŁRZĘDNYCH ----------
// Wartości do 1e9, ale tylko n różnych => zamień na 0..m-1 zachowując porządek.
// Potrzebne do: tablic zliczających, Fenwicka, "ile różnych", itp.
vector<int> compress(const vector<ll>& a) {
    vector<ll> v = a;
    sort(v.begin(), v.end());
    v.erase(unique(v.begin(), v.end()), v.end());       // v = posortowane unikalne
    vector<int> res(a.size());
    for (size_t i = 0; i < a.size(); i++)
        res[i] = lower_bound(v.begin(), v.end(), a[i]) - v.begin();
    return res;
}

// ---------- ARGSORT: indeksy posortowane po wartościach ----------
// Gdy trzeba pamiętać oryginalne pozycje (np. wypisać odpowiedzi w kolejności wejścia).
vector<int> argsort(const vector<ll>& a) {
    vector<int> idx(a.size());
    iota(idx.begin(), idx.end(), 0);
    stable_sort(idx.begin(), idx.end(), [&](int i, int j) { return a[i] < a[j]; });
    return idx;
}

// ---------- KOMPARATORY — ściąga ----------
struct Seg { int l, r, id; };
void komparatoryPrzyklady() {
    vector<Seg> s;
    // po l rosnąco, przy remisie po r MALEJĄCO (typowe dla przedziałów zawierających się)
    sort(s.begin(), s.end(), [](const Seg& a, const Seg& b) {
        if (a.l != b.l) return a.l < b.l;
        return a.r > b.r;
    });
    // krótko przez tie (leksykograficznie):
    sort(s.begin(), s.end(), [](const Seg& a, const Seg& b) { return tie(a.l, b.r) < tie(b.l, a.r); });
    // malejąco:  sort(v.rbegin(), v.rend());  albo  sort(all(v), greater<>());
    // pary/tuple/array sortują się leksykograficznie bez komparatora.
    // KOMPARATOR MUSI BYĆ ŚCISŁY (<, nie <=) — inaczej UB / crash w sort!
}

// ======================= SELF-TEST =======================
int main() {
    mt19937 rng(7);
    for (int it = 0; it < 2000; it++) {
        int n = rng() % 30 + 1;
        vector<ll> a(n);
        for (auto& x : a) x = rng() % 10;
        ll br = 0;
        for (int i = 0; i < n; i++) for (int j = i + 1; j < n; j++) br += a[i] > a[j];
        assert(countInversions(a) == br);

        vector<ll> s = a; sort(s.begin(), s.end());
        int k = rng() % n;
        assert(quickselect(a, k) == s[k]);

        vector<int> ai(a.begin(), a.end());
        vector<int> cs = countingSort(ai, 10);
        assert(vector<ll>(cs.begin(), cs.end()) == s);

        vector<unsigned> u(n);
        for (auto& x : u) x = rng();
        vector<unsigned> us = u; sort(us.begin(), us.end()); radixSort(u);
        assert(u == us);

        auto c = compress(a);
        for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) assert((a[i] < a[j]) == (c[i] < c[j]));

        auto idx = argsort(a);
        for (int i = 0; i + 1 < n; i++) assert(a[idx[i]] <= a[idx[i + 1]]);
    }
    puts("01_sortowanie: OK");
}
