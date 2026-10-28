// rob: szybkie rozwiązanie, O(n log n)
// Narzędzia: kod napisany przez Claude (Anthropic) według etapów 0-6 z karty,
// zweryfikowany stress testem przeciw brute i wersji O(n^2).
// Kompilacja z -DDBG wypisuje tablicę D i wszystkie cost(k).
#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long n, m;
    cin >> n >> m;
    vector<long long> r(n), t(n);
    for (auto &x : r) cin >> x;
    for (auto &x : t) cin >> x;
    sort(r.begin(), r.end());
    sort(t.begin(), t.end());

    // 1) T = trzy kopie celów: t-m, t, t+m. Każdy blok jest posortowany
    //    i każdy kolejny leży dalej w prawo, więc całe T jest posortowane.
    vector<long long> T(3 * n);
    for (int i = 0; i < n; i++) {
        T[i]         = t[i] - m;
        T[i + n]     = t[i];
        T[i + 2 * n] = t[i] + m;
    }

    // 2) Pudełka k = 0..2n (2n+1 okienek). D ma jedno pole więcej
    //    na karteczkę "przestań" dla przedziałów kończących się na 2n.
    long long K = 2 * n + 1;
    vector<long long> D(K + 1, 0);

    // add(a, b, v): "dodaj v do cost(a), cost(a+1), ..., cost(b)".
    // Przycina przedział do [0, 2n]; pusty przedział nic nie robi.
    auto add = [&](long long a, long long b, long long v) {
        a = max(a, 0LL);
        b = min(b, K - 1);
        if (a > b) return;
        D[a] += v;        // karteczka "od a zacznij dodawać v"
        D[b + 1] -= v;    // karteczka "od b+1 przestań"
    };

    // 3) ROBOTY. Robot i w okienku k jedzie do T[i+k].
    //    p = pierwsza pozycja w T z wartością >= r[i].
    //    Dla k < ki cel jest na lewo  -> |r - T| = r - T -> robot z PLUSEM.
    //    Dla k >= ki cel jest na prawo -> |r - T| = T - r -> robot z MINUSEM.
    for (long long i = 0; i < n; i++) {
        long long p = lower_bound(T.begin(), T.end(), r[i]) - T.begin();
        long long ki = p - i;
        add(0, ki - 1, +r[i]);
        add(ki, 2 * n, -r[i]);
    }

    // 4) CELE. T[j] jest w okienku k, gdy k <= j <= k+n-1, czyli k w [j-n+1, j].
    //    Jego partnerem jest robot i = j - k (im większe k, tym mniejszy robot).
    //    c = liczba robotów z r <= T[j]. T[j] >= r[i]  <=>  i < c  <=>  k >= j-c+1.
    //    Przed tym momentem T[j] jest mniejszy od partnera -> MINUS, potem PLUS.
    //    Remis r == T liczymy tak samo jak w kroku 3: "cel >= robot".
    for (long long j = 0; j < 3 * n; j++) {
        long long lo = j - n + 1;   // pierwsze k, w którym T[j] jest w okienku
        long long hi = j;           // ostatnie
        long long c = upper_bound(r.begin(), r.end(), T[j]) - r.begin();
        long long s = j - c + 1;    // od tego k T[j] ma plus
        add(lo, min(hi, s - 1), -T[j]);
        add(max(lo, s), hi, +T[j]);
    }

    // 5) Idziemy po pudełkach i sumujemy karteczki na bieżąco: cur = cost(k).
    long long cur = 0, best = LLONG_MAX;
    for (long long k = 0; k < K; k++) {
        cur += D[k];
        best = min(best, cur);
#ifdef DBG
        cerr << "cost(" << k << ") = " << cur << "\n";
#endif
    }
#ifdef DBG
    cerr << "D = ";
    for (auto x : D) cerr << x << " ";
    cerr << "\n";
#endif
    cout << best << "\n";
}
