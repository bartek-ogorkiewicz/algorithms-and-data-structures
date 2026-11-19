// ============================================================
//  07 SET / MULTISET / MAP / PRIORITY_QUEUE / LISTA NA TABLICACH
// ============================================================
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

/* ---------- ŚCIĄGA ----------
 set<int> s;            insert O(log n), erase(x) O(log n), count(x)/contains(x) (C++20)
   s.lower_bound(x)  -> pierwszy >= x   (METODA, nie std::lower_bound!)
   s.upper_bound(x)  -> pierwszy >  x
   *s.begin() = min,  *s.rbegin() = max,  prev(it) / next(it) = sąsiedzi
   it == s.begin() => brak poprzednika;  it == s.end() => brak (np. nie znaleziono)
 multiset<int> ms;      jak set, ale z powtórzeniami
   ms.erase(x)           USUWA WSZYSTKIE kopie x !!!
   ms.erase(ms.find(x))  usuwa JEDNĄ kopię (najpierw sprawdź find != end)
   ms.count(x)           O(log n + liczba kopii) — wolne przy wielu kopiach
 map<K,V> m;            m[k] tworzy wpis z V() jeśli nie ma (uwaga przy samym sprawdzaniu!)
   m.count(k) / m.find(k) / m.contains(k) — sprawdzanie bez tworzenia
   for (auto& [k, v] : m)  — iteracja posortowana po kluczu
 unordered_map/set      średnio O(1), ale da się zabić złośliwym testem -> custom hash (11_bity_matma)
 priority_queue<T> pq;  MAX-kopiec: top() = największy
   priority_queue<T, vector<T>, greater<T>> pq;   MIN-kopiec
   brak usuwania dowolnego elementu -> "leniwe usuwanie" albo multiset
 vector jako stos: push_back / back / pop_back
 deque: push_front/back, pop_front/back O(1), indeksowanie O(1)
 ---------------------------------------- */

// ---------- SĄSIEDZI W ZBIORZE (zadanie SUM: suma kwadratów różnic kolejnych) ----------
// Wstawienie x między p i nx: + (x-p)^2 + (nx-x)^2 - (nx-p)^2
struct SumSqDiff {
    set<ll> s; ll sum = 0;
    static ll sq(ll d) { return d * d; }
    void insert(ll x) {
        auto it = s.insert(x).first;
        bool hp = it != s.begin(), hn = next(it) != s.end();
        ll p = hp ? *prev(it) : 0, nx = hn ? *next(it) : 0;
        if (hp) sum += sq(x - p);
        if (hn) sum += sq(nx - x);
        if (hp && hn) sum -= sq(nx - p);
    }
    void erase(ll x) {                      // odwrotność insert
        auto it = s.find(x);
        bool hp = it != s.begin(), hn = next(it) != s.end();
        ll p = hp ? *prev(it) : 0, nx = hn ? *next(it) : 0;
        if (hp) sum -= sq(x - p);
        if (hn) sum -= sq(nx - x);
        if (hp && hn) sum += sq(nx - p);
        s.erase(it);
    }
};

// ---------- NAJBLIŻSZY ELEMENT DO x W ZBIORZE ----------
ll closest(const set<ll>& s, ll x) {   // s niepusty
    auto it = s.lower_bound(x);
    if (it == s.end()) return *prev(it);
    if (it == s.begin()) return *it;
    ll a = *prev(it), b = *it;
    return (x - a <= b - x) ? a : b;
}

// ---------- LISTA DWUKIERUNKOWA NA TABLICACH (zadanie ZOL)  O(1) na usunięcie ----------
// Elementy 1..n w kolejności; usuwamy element i pytamy o jego sąsiadów.
struct ArrayList {
    vector<int> L, R;
    ArrayList(int n) : L(n + 2), R(n + 2) {
        for (int i = 1; i <= n; i++) { L[i] = i - 1; R[i] = i + 1; }   // 0 i n+1 = wartownicy
    }
    void erase(int i) { R[L[i]] = R[i]; L[R[i]] = L[i]; }
    // sąsiedzi i: L[i] (0 => brak), R[i] (n+1 => brak)
};

// ---------- MEDIANA STRUMIENIA: dwa kopce ----------
// lo = max-kopiec (mniejsza połowa), hi = min-kopiec (większa). |lo| == |hi| lub |lo| == |hi|+1
struct RunningMedian {
    priority_queue<ll> lo;
    priority_queue<ll, vector<ll>, greater<ll>> hi;
    void add(ll x) {
        if (lo.empty() || x <= lo.top()) lo.push(x); else hi.push(x);
        if (lo.size() > hi.size() + 1) { hi.push(lo.top()); lo.pop(); }
        else if (hi.size() > lo.size()) { lo.push(hi.top()); hi.pop(); }
    }
    ll median() { return lo.top(); }   // dolna mediana
};

// ---------- MEDIANA W OKNIE (z usuwaniem) — dwa multisety ----------
// To samo, ale multiset pozwala usunąć dowolny element. O(log n) na operację.
struct WindowMedian {
    multiset<ll> lo, hi;   // max(lo) <= min(hi), |lo| == |hi| lub |hi|+1
    void fix() {
        while (lo.size() > hi.size() + 1) { hi.insert(*lo.rbegin()); lo.erase(prev(lo.end())); }
        while (hi.size() > lo.size()) { lo.insert(*hi.begin()); hi.erase(hi.begin()); }
    }
    void add(ll x) { if (lo.empty() || x <= *lo.rbegin()) lo.insert(x); else hi.insert(x); fix(); }
    void remove(ll x) {
        auto it = lo.find(x);
        if (it != lo.end()) lo.erase(it); else hi.erase(hi.find(x));
        fix();
    }
    ll median() { return *lo.rbegin(); }
};

// ---------- K NAJWIĘKSZYCH ZE STRUMIENIA: min-kopiec rozmiaru k ----------
vector<ll> topK(const vector<ll>& a, int k) {
    priority_queue<ll, vector<ll>, greater<ll>> pq;
    for (ll x : a) { pq.push(x); if ((int)pq.size() > k) pq.pop(); }
    vector<ll> res; while (!pq.empty()) { res.push_back(pq.top()); pq.pop(); }
    reverse(res.begin(), res.end()); return res;   // malejąco
}

// ---------- SCALANIE k POSORTOWANYCH LIST ----------
vector<ll> mergeK(const vector<vector<ll>>& lists) {
    using T = tuple<ll, int, int>;  // (wartość, nr listy, indeks)
    priority_queue<T, vector<T>, greater<T>> pq;
    for (int i = 0; i < (int)lists.size(); i++) if (!lists[i].empty()) pq.push({lists[i][0], i, 0});
    vector<ll> res;
    while (!pq.empty()) {
        auto [v, i, j] = pq.top(); pq.pop(); res.push_back(v);
        if (j + 1 < (int)lists[i].size()) pq.push({lists[i][j + 1], i, j + 1});
    }
    return res;
}

// ---------- SYMULACJA ZDARZEŃ: kopiec + leniwe usuwanie ----------
// "zadania przychodzą w czasie t_i i trwają d_i, procesor bierze najkrótsze" itp.
// Wzorzec: sortuj zdarzenia po czasie, w pętli dorzucaj wszystkie z t <= now do kopca,
// zdejmij najlepsze; jeśli kopiec pusty, przeskocz now do następnego zdarzenia.
ll sjfTotalCompletion(vector<pair<ll,ll>> jobs) {   // (przyjście, czas trwania) -> suma czasów zakończenia
    sort(jobs.begin(), jobs.end());
    priority_queue<ll, vector<ll>, greater<ll>> pq; ll now = 0, total = 0; size_t i = 0;
    while (i < jobs.size() || !pq.empty()) {
        if (pq.empty() && now < jobs[i].first) now = jobs[i].first;
        while (i < jobs.size() && jobs[i].first <= now) pq.push(jobs[i++].second);
        now += pq.top(); pq.pop(); total += now;
    }
    return total;
}

// ======================= SELF-TEST =======================
int main() {
    mt19937 rng(8);
    for (int it = 0; it < 1000; it++) {
        // SumSqDiff vs brute
        SumSqDiff S; set<ll> ref;
        for (int q = 0; q < 15; q++) {
            ll x = rng() % 30;
            if (ref.count(x)) { S.erase(x); ref.erase(x); } else { S.insert(x); ref.insert(x); }
            ll br = 0; for (auto i2 = ref.begin(); i2 != ref.end() && next(i2) != ref.end(); ++i2) br += (*next(i2) - *i2) * (*next(i2) - *i2);
            assert(S.sum == br);
            if (!ref.empty()) { ll y = rng() % 30, c = closest(ref, y), bd = LLONG_MAX; for (ll z : ref) bd = min(bd, llabs(z - y)); assert(llabs(c - y) == bd); }
        }
        // ArrayList vs set
        int n = rng() % 10 + 1; ArrayList L(n); set<int> alive; for (int i = 1; i <= n; i++) alive.insert(i);
        vector<int> order(n); iota(order.begin(), order.end(), 1); shuffle(order.begin(), order.end(), rng);
        for (int x : order) { auto i2 = alive.find(x);
            int l = i2 == alive.begin() ? 0 : *prev(i2), r = next(i2) == alive.end() ? n + 1 : *next(i2);
            assert(L.L[x] == l && L.R[x] == r); L.erase(x); alive.erase(i2); }
        // mediany
        RunningMedian rm; WindowMedian wm; vector<ll> v; int k = rng() % 5 + 1; vector<ll> a;
        for (int q = 0; q < 20; q++) { ll x = rng() % 10; a.push_back(x);
            rm.add(x); v.push_back(x); vector<ll> s = v; sort(s.begin(), s.end()); assert(rm.median() == s[(s.size() - 1) / 2]);
            wm.add(x); if ((int)a.size() > k) wm.remove(a[a.size() - 1 - k]);
            vector<ll> w(a.end() - min<int>(k, a.size()), a.end()); sort(w.begin(), w.end()); assert(wm.median() == w[(w.size() - 1) / 2]); }
        auto tk = topK(a, k); vector<ll> s = a; sort(s.rbegin(), s.rend()); s.resize(k); assert(tk == s);
        vector<vector<ll>> ls(rng() % 4 + 1); vector<ll> all;
        for (auto& l : ls) { l.resize(rng() % 5); for (auto& x : l) { x = rng() % 20; all.push_back(x); } sort(l.begin(), l.end()); }
        sort(all.begin(), all.end()); assert(mergeK(ls) == all);
    }
    assert(sjfTotalCompletion({{0, 3}, {1, 1}, {2, 1}}) == 3 + 4 + 5);
    puts("07_set_map_kopiec: OK");
}
