// ============================================================
//  05 STOS MONOTONICZNY, KOLEJKA MONOTONICZNA (DEQUE), NAWIASY
//  Każdy element wchodzi i wychodzi raz => O(n) zamortyzowane.
// ============================================================
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// ---------- NAJBLIŻSZY WIĘKSZY ELEMENT NA PRAWO (next greater) ----------
// res[i] = najmniejsze j > i z a[j] > a[i], albo n gdy brak.
// Stos trzyma indeksy "czekające" na większy element; wartości na stosie MALEJĄ.
// Warianty: na lewo (iteruj od lewej, patrz na szczyt), >= zamiast >, mniejszy zamiast większy.
vector<int> nextGreater(const vector<ll>& a) {
    int n = a.size(); vector<int> res(n, n); vector<int> st;
    for (int i = 0; i < n; i++) {
        while (!st.empty() && a[st.back()] < a[i]) { res[st.back()] = i; st.pop_back(); }
        st.push_back(i);
    }
    return res;
}
// najbliższy MNIEJSZY na LEWO: prev[i] = największe j < i z a[j] < a[i], -1 gdy brak
vector<int> prevSmaller(const vector<ll>& a) {
    int n = a.size(); vector<int> res(n, -1); vector<int> st;
    for (int i = 0; i < n; i++) {
        while (!st.empty() && a[st.back()] >= a[i]) st.pop_back();
        if (!st.empty()) res[i] = st.back();
        st.push_back(i);
    }
    return res;
}

// ---------- NAJWIĘKSZY PROSTOKĄT W HISTOGRAMIE  O(n) ----------
// Dla każdego słupka: jak daleko w lewo/prawo sięga z wysokością >= h[i].
ll largestRectangle(const vector<ll>& h) {
    int n = h.size(); vector<int> st; ll best = 0;
    for (int i = 0; i <= n; i++) {
        ll cur = (i == n) ? 0 : h[i];               // wartownik 0 na końcu opróżnia stos
        while (!st.empty() && h[st.back()] >= cur) {
            ll height = h[st.back()]; st.pop_back();
            int left = st.empty() ? -1 : st.back();
            best = max(best, height * (i - left - 1));
        }
        st.push_back(i);
    }
    return best;
}

// ---------- MAKSIMUM W OKNIE DŁUGOŚCI k (sliding window max)  O(n) ----------
// Deque indeksów, wartości MALEJĄ od przodu. Przód = maksimum okna.
// Minimum: odwróć porównanie.
vector<ll> slidingMax(const vector<ll>& a, int k) {
    deque<int> dq; vector<ll> res;
    for (int i = 0; i < (int)a.size(); i++) {
        while (!dq.empty() && a[dq.back()] <= a[i]) dq.pop_back();   // gorsi i starsi — nigdy nie będą max
        dq.push_back(i);
        if (dq.front() <= i - k) dq.pop_front();                    // wypadł z okna
        if (i >= k - 1) res.push_back(a[dq.front()]);
    }
    return res;
}
// Zastosowanie razem z 2 wskaźnikami: "najdłuższy fragment z max - min <= d"
// -> dwie deque (max i min), przesuwaj l gdy a[maxdq.front] - a[mindq.front] > d
int longestMaxMinusMinAtMost(const vector<ll>& a, ll d) {
    deque<int> mx, mn; int best = 0;
    for (int l = 0, r = 0; r < (int)a.size(); r++) {
        while (!mx.empty() && a[mx.back()] <= a[r]) mx.pop_back();
        mx.push_back(r);
        while (!mn.empty() && a[mn.back()] >= a[r]) mn.pop_back();
        mn.push_back(r);
        while (a[mx.front()] - a[mn.front()] > d) {
            l++;
            if (mx.front() < l) mx.pop_front();
            if (mn.front() < l) mn.pop_front();
        }
        best = max(best, r - l + 1);
    }
    return best;
}

// ---------- NAWIASY: poprawność + najdłuższy poprawny fragment ----------
bool validBrackets(const string& s) {
    vector<char> st; string open = "([{", close = ")]}";
    for (char c : s) {
        if (open.find(c) != string::npos) st.push_back(c);
        else {
            int k = close.find(c);
            if (st.empty() || st.back() != open[k]) return false;
            st.pop_back();
        }
    }
    return st.empty();
}
int longestValidParens(const string& s) {        // tylko '(' i ')'
    vector<int> st = {-1}; int best = 0;          // na dnie: indeks ostatniego "złego" miejsca
    for (int i = 0; i < (int)s.size(); i++) {
        if (s[i] == '(') st.push_back(i);
        else { st.pop_back(); if (st.empty()) st.push_back(i); else best = max(best, i - st.back()); }
    }
    return best;
}

// ---------- KOLEJKA NA DWÓCH STOSACH (np. min w kolejce O(1) zamortyzowane) ----------
struct MinQueue {
    vector<pair<ll,ll>> in, out;   // (wartość, min do tej pory)
    void push(ll x) { in.push_back({x, in.empty() ? x : min(x, in.back().second)}); }
    void pop() {
        if (out.empty()) while (!in.empty()) { ll x = in.back().first; in.pop_back();
            out.push_back({x, out.empty() ? x : min(x, out.back().second)}); }
        out.pop_back();
    }
    ll getMin() {
        if (in.empty()) return out.back().second;
        if (out.empty()) return in.back().second;
        return min(in.back().second, out.back().second);
    }
};

// ======================= SELF-TEST =======================
int main() {
    mt19937 rng(5);
    for (int it = 0; it < 2000; it++) {
        int n = rng() % 12 + 1;
        vector<ll> a(n); for (auto& x : a) x = rng() % 6;
        auto ng = nextGreater(a); auto ps = prevSmaller(a);
        for (int i = 0; i < n; i++) {
            int j = i + 1; while (j < n && a[j] <= a[i]) j++; assert(ng[i] == j);
            int k = i - 1; while (k >= 0 && a[k] >= a[i]) k--; assert(ps[i] == k);
        }
        ll br = 0; for (int l = 0; l < n; l++) { ll mn = LLONG_MAX; for (int r = l; r < n; r++) { mn = min(mn, a[r]); br = max(br, mn * (r - l + 1)); } }
        assert(largestRectangle(a) == br);
        int k = rng() % n + 1; auto sm = slidingMax(a, k);
        for (int i = 0; i + k <= n; i++) assert(sm[i] == *max_element(a.begin() + i, a.begin() + i + k));
        ll d = rng() % 4; int bl = 0;
        for (int l = 0; l < n; l++) for (int r = l; r < n; r++) { auto [lo, hi] = minmax_element(a.begin() + l, a.begin() + r + 1); if (*hi - *lo <= d) bl = max(bl, r - l + 1); }
        assert(longestMaxMinusMinAtMost(a, d) == bl);

        string s; for (int i = 0; i < n; i++) s += "()"[rng() % 2];
        int bv = 0; for (int l = 0; l < n; l++) for (int r = l; r < n; r++) if (validBrackets(s.substr(l, r - l + 1))) bv = max(bv, r - l + 1);
        assert(longestValidParens(s) == bv);

        MinQueue q; deque<ll> ref;
        for (int t = 0; t < 20; t++) {
            if (ref.empty() || rng() % 2) { ll x = rng() % 10; q.push(x); ref.push_back(x); }
            else { q.pop(); ref.pop_front(); }
            if (!ref.empty()) assert(q.getMin() == *min_element(ref.begin(), ref.end()));
        }
    }
    assert(validBrackets("([]{})") && !validBrackets("([)]"));
    puts("05_stos_kolejka: OK");
}
