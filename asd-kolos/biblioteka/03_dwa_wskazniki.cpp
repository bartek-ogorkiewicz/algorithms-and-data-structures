// ============================================================
//  03 DWA WSKAŹNIKI / OKNO PRZESUWNE
//  Warunek użycia: gdy przesuwamy prawy koniec w prawo, optymalny lewy
//  koniec też tylko się przesuwa w prawo (MONOTONICZNOŚĆ). Wtedy O(n),
//  bo każdy wskaźnik przejdzie max n kroków (analiza zamortyzowana).
//  Typowo: tablica POSORTOWANA albo liczby NIEUJEMNE (sumy rosną).
// ============================================================
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// ---- A. Max liczba punktów w przedziale długości w (LOG) — a posortowane ----
int maxInWindow(const vector<ll>& a, ll w) {
    int best = 0;
    for (int l = 0, r = 0; r < (int)a.size(); r++) {
        while (a[r] - a[l] > w) l++;
        best = max(best, r - l + 1);
    }
    return best;
}

// ---- B. Liczba par i<j z a[j]-a[i] <= w (SZA) — a posortowane ----
ll pairsDiffAtMost(const vector<ll>& a, ll w) {
    ll ans = 0; int n = a.size();
    for (int l = 0, r = 0; l < n; l++) {
        while (r < n && a[r] - a[l] <= w) r++;
        ans += r - l - 1;
    }
    return ans;
}
// Pary z różnicą DOKŁADNIE w / >= w / w przedziale [A,B]:
//   cnt(<= B) - cnt(<= A-1)   <-- ZAWSZE sprowadzaj do "<= X" i odejmuj!
//   >= w  ==  wszystkie n(n-1)/2  -  (<= w-1)
ll pairsDiffInRange(const vector<ll>& a, ll A, ll B) {
    return pairsDiffAtMost(a, B) - (A > 0 ? pairsDiffAtMost(a, A - 1) : 0);
}

// ---- C. Liczba par i<j z a[i]+a[j] <= S — a posortowane (wskaźniki z dwóch stron) ----
ll pairsSumAtMost(const vector<ll>& a, ll S) {
    ll ans = 0; int l = 0, r = (int)a.size() - 1;
    while (l < r) {
        if (a[l] + a[r] <= S) { ans += r - l; l++; }   // a[l] pasuje z każdym a[l+1..r]
        else r--;
    }
    return ans;
}

// ---- D. Czy istnieje para o sumie dokładnie S (two-sum) — a posortowane ----
bool twoSum(const vector<ll>& a, ll S) {
    int l = 0, r = (int)a.size() - 1;
    while (l < r) {
        ll s = a[l] + a[r];
        if (s == S) return true;
        if (s < S) l++; else r--;
    }
    return false;
}

// ---- E. Najdłuższy podciąg spójny o sumie <= S  (a[i] >= 0 !) ----
int longestSumAtMost(const vector<ll>& a, ll S) {
    int best = 0; ll sum = 0;
    for (int l = 0, r = 0; r < (int)a.size(); r++) {
        sum += a[r];
        while (sum > S) sum -= a[l++];       // l może przeskoczyć r => okno puste, OK
        best = max(best, r - l + 1);
    }
    return best;
}

// ---- F. Liczba podciągów spójnych o sumie <= S  (a[i] >= 0) ----
// Dla każdego r: wszystkie początki l..r są dobre => +(r-l+1)
ll countSubarraysSumAtMost(const vector<ll>& a, ll S) {
    ll ans = 0, sum = 0;
    for (int l = 0, r = 0; r < (int)a.size(); r++) {
        sum += a[r];
        while (l <= r && sum > S) sum -= a[l++];
        ans += r - l + 1;
    }
    return ans;
}

// ---- G. Najkrótszy podciąg spójny o sumie >= S (a[i] >= 0) — zwraca 0 gdy brak ----
int shortestSumAtLeast(const vector<ll>& a, ll S) {
    int best = INT_MAX; ll sum = 0;
    for (int l = 0, r = 0; r < (int)a.size(); r++) {
        sum += a[r];
        while (l < r && sum - a[l] >= S) sum -= a[l++];    // zwężaj, dopóki nadal >= S (min. 1 element)
        if (sum >= S) best = min(best, r - l + 1);
    }
    return best == INT_MAX ? 0 : best;
}

// ---- H. Najdłuższy fragment z co najwyżej K RÓŻNYMI wartościami ----
// (wariant: "bez powtórzeń" = każda wartość max 1 raz). Wartości duże => map/kompresja.
int longestAtMostKDistinct(const vector<int>& a, int K) {
    unordered_map<int, int> cnt; int distinct = 0, best = 0;
    for (int l = 0, r = 0; r < (int)a.size(); r++) {
        if (cnt[a[r]]++ == 0) distinct++;
        while (distinct > K) if (--cnt[a[l++]] == 0) distinct--;
        best = max(best, r - l + 1);
    }
    return best;
}
// Liczba fragmentów z DOKŁADNIE K różnymi = atMost(K) - atMost(K-1)  (ten sam trik co w B)
ll countAtMostKDistinct(const vector<int>& a, int K) {
    if (K < 0) return 0;
    unordered_map<int, int> cnt; int distinct = 0; ll ans = 0;
    for (int l = 0, r = 0; r < (int)a.size(); r++) {
        if (cnt[a[r]]++ == 0) distinct++;
        while (distinct > K) if (--cnt[a[l++]] == 0) distinct--;
        ans += r - l + 1;
    }
    return ans;
}

// ---- I. Najkrótsze okno zawierające wszystkie kolory 1..K (0 gdy brak) ----
int shortestAllColors(const vector<int>& a, int K) {
    vector<int> cnt(K + 1, 0); int have = 0, best = INT_MAX;
    for (int l = 0, r = 0; r < (int)a.size(); r++) {
        if (cnt[a[r]]++ == 0) have++;
        while (have == K) {
            best = min(best, r - l + 1);
            if (--cnt[a[l++]] == 0) have--;
        }
    }
    return best == INT_MAX ? 0 : best;
}

// ---- J. Liczba trójek i<j<k z a[i]+a[j]+a[k] == S (3-sum)  O(n^2) ----
ll countTriples(vector<ll> a, ll S) {
    sort(a.begin(), a.end());
    int n = a.size(); ll ans = 0;
    for (int i = 0; i < n; i++) {          // ustal najmniejszy, resztę jak two-sum z liczeniem
        int l = i + 1, r = n - 1;
        while (l < r) {
            ll s = a[i] + a[l] + a[r];
            if (s < S) l++;
            else if (s > S) r--;
            else if (a[l] == a[r]) { ll m = r - l + 1; ans += m * (m - 1) / 2; break; }
            else {
                ll cl = 1, cr = 1;
                while (l + 1 < r && a[l + 1] == a[l]) { l++; cl++; }
                while (r - 1 > l && a[r - 1] == a[r]) { r--; cr++; }
                ans += cl * cr; l++; r--;
            }
        }
    }
    return ans;
}

// ---- K. Scalanie dwóch posortowanych (merge) / przecięcie dwóch zbiorów ----
vector<ll> intersectSorted(const vector<ll>& a, const vector<ll>& b) {
    vector<ll> res; size_t i = 0, j = 0;
    while (i < a.size() && j < b.size()) {
        if (a[i] < b[j]) i++;
        else if (a[i] > b[j]) j++;
        else { res.push_back(a[i]); i++; j++; }
    }
    return res;   // STL: set_intersection(all(a), all(b), back_inserter(res));
}

// ======================= SELF-TEST (porównanie z brute) =======================
int main() {
    mt19937 rng(3);
    for (int it = 0; it < 3000; it++) {
        int n = rng() % 10 + 1;
        vector<ll> a(n);
        for (auto& x : a) x = rng() % 12;
        vector<ll> s = a; sort(s.begin(), s.end());
        ll w = rng() % 8, S = rng() % 30;

        int bA = 0; for (int i = 0; i < n; i++) { int c = 0; for (int j = 0; j < n; j++) c += s[i] <= s[j] && s[j] <= s[i] + w; bA = max(bA, c); }
        assert(maxInWindow(s, w) == bA);

        ll bB = 0, bC = 0, bR = 0; bool bD = false; ll A = rng() % 5, B = A + rng() % 5;
        for (int i = 0; i < n; i++) for (int j = i + 1; j < n; j++) {
            bB += llabs(a[i] - a[j]) <= w; bC += a[i] + a[j] <= S; bD |= a[i] + a[j] == S;
            ll d = llabs(a[i] - a[j]); bR += A <= d && d <= B;
        }
        assert(pairsDiffAtMost(s, w) == bB); assert(pairsSumAtMost(s, S) == bC);
        assert(twoSum(s, S) == bD); assert(pairsDiffInRange(s, A, B) == bR);

        int bE = 0; ll bF = 0; int bG = INT_MAX;
        for (int l = 0; l < n; l++) { ll sum = 0; for (int r = l; r < n; r++) { sum += a[r];
            if (sum <= S) { bE = max(bE, r - l + 1); bF++; } if (sum >= S) bG = min(bG, r - l + 1); } }
        assert(longestSumAtMost(a, S) == bE); assert(countSubarraysSumAtMost(a, S) == bF);
        assert(shortestSumAtLeast(a, S) == (bG == INT_MAX ? 0 : bG));

        vector<int> c(n); for (auto& x : c) x = rng() % 4 + 1;
        int K = rng() % 4 + 1;
        int bH = 0; ll bK = 0;
        for (int l = 0; l < n; l++) { set<int> st; for (int r = l; r < n; r++) { st.insert(c[r]);
            if ((int)st.size() <= K) bH = max(bH, r - l + 1);
            if ((int)st.size() == K) bK++;
            } }
        assert(longestAtMostKDistinct(c, K) == bH);
        assert(countAtMostKDistinct(c, K) - countAtMostKDistinct(c, K - 1) == bK);
        { vector<int> cc = c; int KK = *max_element(cc.begin(), cc.end()); bool all = true;
          for (int v = 1; v <= KK; v++) all &= count(cc.begin(), cc.end(), v) > 0;
          if (all) { int bb = INT_MAX; for (int l = 0; l < n; l++) { set<int> st; for (int r = l; r < n; r++) { st.insert(cc[r]); if ((int)st.size() == KK) { bb = min(bb, r - l + 1); break; } } }
            assert(shortestAllColors(cc, KK) == bb); } }

        ll bJ = 0; ll S3 = rng() % 25;
        for (int i = 0; i < n; i++) for (int j = i + 1; j < n; j++) for (int k = j + 1; k < n; k++) bJ += a[i] + a[j] + a[k] == S3;
        assert(countTriples(a, S3) == bJ);

        vector<ll> b(rng() % 8); for (auto& x : b) x = rng() % 12; sort(b.begin(), b.end());
        vector<ll> exp; set_intersection(s.begin(), s.end(), b.begin(), b.end(), back_inserter(exp));
        assert(intersectSorted(s, b) == exp);
    }
    puts("03_dwa_wskazniki: OK");
}
