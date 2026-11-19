// ============================================================
//  GENERATOR TESTÓW LOSOWYCH
//  Użycie:   ./gen SEED [MAXN] [MAXV]  > test.in
//  Przykład: ./gen 17          -> mały test (n <= 8, wartości <= 20)
//            ./gen 1 500000 2000000000  -> duży test do pomiaru czasu
//  Ten sam SEED => ten sam test (da się odtworzyć błąd).
//
//  PRZERABIASZ TYLKO funkcję main() pod format wejścia zadania.
// ============================================================
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

mt19937_64 rng;

// losowa liczba całkowita z przedziału [a, b] (obustronnie domknięty)
ll rnd(ll a, ll b) { return uniform_int_distribution<ll>(a, b)(rng); }

// losowa permutacja 1..n
vector<int> perm(int n) {
    vector<int> p(n);
    iota(p.begin(), p.end(), 1);
    shuffle(p.begin(), p.end(), rng);
    return p;
}

// k RÓŻNYCH liczb z [lo, hi]  (wymaga hi - lo + 1 >= k)
vector<ll> distinct(int k, ll lo, ll hi) {
    set<ll> s;
    while ((int)s.size() < k) s.insert(rnd(lo, hi));
    vector<ll> v(s.begin(), s.end());
    shuffle(v.begin(), v.end(), rng);
    return v;
}

// losowe drzewo na n wierzchołkach (krawędzie 1-indeksowane)
vector<pair<int,int>> tree(int n) {
    vector<pair<int,int>> e;
    for (int i = 2; i <= n; i++) e.push_back({(int)rnd(1, i - 1), i});
    return e;
}

// losowy graf prosty: n wierzchołków, m krawędzi, bez pętli i multikrawędzi
vector<pair<int,int>> graph(int n, int m) {
    set<pair<int,int>> s;
    m = min<ll>(m, 1LL * n * (n - 1) / 2);
    while ((int)s.size() < m) {
        int a = rnd(1, n), b = rnd(1, n);
        if (a == b) continue;
        if (a > b) swap(a, b);
        s.insert({a, b});
    }
    return vector<pair<int,int>>(s.begin(), s.end());
}

int main(int argc, char* argv[]) {
    ll seed = argc > 1 ? atoll(argv[1]) : 0;
    ll MAXN = argc > 2 ? atoll(argv[2]) : 8;   // małe n => łatwo czytać kontrprzykład
    ll MAXV = argc > 3 ? atoll(argv[3]) : 20;  // małe wartości => dużo powtórzeń/remisów
    rng.seed(seed);

    // ---------- FORMAT WEJŚCIA (przykład: zadanie LOG / SZA) ----------
    // pierwsza linia: n w, potem n liczb, każda w osobnej linii
    int n = MAXN > 1000 ? MAXN : rnd(1, MAXN);   // duże MAXN => test maksymalny (pomiar czasu)
    ll w = rnd(0, MAXV / 2);
    printf("%d %lld\n", n, w);
    for (int i = 0; i < n; i++) printf("%lld\n", rnd(0, MAXV));

    // ---------- inne typowe formaty (odkomentuj potrzebny) ----------
    // ciąg w jednej linii:
    //   for (int i = 0; i < n; i++) printf("%lld%c", rnd(1, MAXV), " \n"[i == n - 1]);
    // przedziały [l, r]:
    //   for (int i = 0; i < n; i++) { ll l = rnd(0, MAXV), r = rnd(l, MAXV); printf("%lld %lld\n", l, r); }
    // graf:
    //   int m = rnd(0, n * (n - 1) / 2); auto E = graph(n, m);
    //   printf("%d %d\n", n, (int)E.size()); for (auto [a, b] : E) printf("%d %d\n", a, b);
    // zapytania (typ 1/2):
    //   int q = rnd(1, MAXN); printf("%d\n", q);
    //   while (q--) if (rnd(0, 1)) printf("1 %lld\n", rnd(1, MAXV)); else printf("2\n");
}
