// ============================================================
//  11 BITY, MATEMATYKA, HASHOWANIE
// ============================================================
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;

/* ---------- BITY — ściąga ----------
 x & 1            parzystość          x >> k & 1     k-ty bit
 x | (1 << k)     zapal bit k         x & ~(1 << k)  zgaś bit k        x ^ (1 << k)  przełącz
 x & -x           najniższy zapalony bit (Fenwick)
 x & (x - 1)      zgaś najniższy bit; ==0 <=> x jest potęgą 2 (lub 0)
 __builtin_popcount(x) / popcountll   liczba jedynek
 __builtin_ctz(x)  zera na końcu (x != 0)      __builtin_clz(x)  zera na początku (x != 0)
 __lg(x)          floor(log2 x)  (x > 0)
 1LL << k         gdy k >= 31 MUSI być 1LL, inaczej UB!
 Iteracja po podmaskach maski m:  for (int s = m; s; s = (s - 1) & m)
 Wszystkie podzbiory n elementów: for (int m = 0; m < (1 << n); m++)
 XOR: a ^ a = 0, a ^ 0 = a; xor prefiksowy jak suma prefiksowa: xor[l..r] = X[r+1] ^ X[l]
---------------------------------------- */

// ---------- LICZNIK BINARNY Z PRZENIESIENIAMI (zadanie JED) ----------
// Dodajemy 2^a_i do dużej liczby; po każdym dodaniu: liczba jedynek.
// Dodanie 2^a: od pozycji a gasimy kolejne jedynki (każda: -1), zapalamy pierwsze zero (+1).
// Zamortyzowane O(1): każda zgaszona jedynka była wcześniej zapalona, a zapalamy max 1 na operację.
vector<int> binaryCounterOnes(const vector<int>& a) {
    int MX = *max_element(a.begin(), a.end()) + 25;   // przeniesienie może wyjść ~log2(n) ponad max
    vector<char> bit(MX, 0); int ones = 0; vector<int> res;
    for (int x : a) {
        int p = x;
        while (bit[p]) { bit[p] = 0; ones--; p++; }
        bit[p] = 1; ones++;
        res.push_back(ones);
    }
    return res;
}

// ---------- ARYTMETYKA MODULARNA ----------
const ll MOD = 1e9 + 7;
ll power(ll b, ll e, ll m = MOD) {   // b^e mod m, O(log e)
    ll r = 1; b %= m; if (b < 0) b += m;
    while (e > 0) { if (e & 1) r = r * b % m; b = b * b % m; e >>= 1; }
    return r;
}
ll inverse(ll a) { return power(a, MOD - 2); }   // odwrotność mod p (p pierwsze, a % p != 0)
// Dwumian mod p: silnie + odwrotności silni, O(n) preprocessing, O(1) zapytanie
struct Binom {
    vector<ll> f, inv;
    Binom(int n) : f(n + 1), inv(n + 1) {
        f[0] = 1; for (int i = 1; i <= n; i++) f[i] = f[i - 1] * i % MOD;
        inv[n] = inverse(f[n]); for (int i = n; i > 0; i--) inv[i - 1] = inv[i] * i % MOD;
    }
    ll C(int n, int k) { if (k < 0 || k > n) return 0; return f[n] * inv[k] % MOD * inv[n - k] % MOD; }
};
// ujemne modulo w C++: (-7) % 3 == -1  =>  używaj ((x % m) + m) % m

// ---------- NWD / NWW / SITO ----------
// gcd(a, b) i lcm(a, b) są w <numeric> (std::gcd, std::lcm). lcm może się przepełnić: a / gcd * b
vector<int> sieve(int n) {    // spf[x] = najmniejszy dzielnik pierwszy x  => szybka faktoryzacja
    vector<int> spf(n + 1, 0);
    for (int i = 2; i <= n; i++) if (!spf[i]) for (int j = i; j <= n; j += i) if (!spf[j]) spf[j] = i;
    return spf;
}

// ---------- BEZPIECZNY HASH do unordered_map (anty-złośliwe testy) ----------
struct SafeHash {
    static ull splitmix64(ull x) {
        x += 0x9e3779b97f4a7c15ULL; x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9ULL;
        x = (x ^ (x >> 27)) * 0x94d049bb133111ebULL; return x ^ (x >> 31);
    }
    size_t operator()(ull x) const {
        static const ull R = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + R);
    }
};
// użycie: unordered_map<ll, int, SafeHash> m;  m.reserve(1 << 20);  (reserve przyspiesza)
// hash pary: klucz = (ll)a * 1'000'000'007 + b  albo  ((ull)a << 32) | b  dla a, b < 2^32

// ---------- HASH NAPISÓW (porównanie podsłów w O(1)) ----------
struct StrHash {
    static constexpr ull M = (1ULL << 61) - 1;
    static ull mul(ull a, ull b) {             // a*b mod (2^61 - 1)
        __uint128_t c = (__uint128_t)a * b;
        ull r = (ull)(c & M) + (ull)(c >> 61);
        return r >= M ? r - M : r;
    }
    vector<ull> h, p;
    StrHash(const string& s, ull B = 131) : h(s.size() + 1, 0), p(s.size() + 1, 1) {
        for (size_t i = 0; i < s.size(); i++) { h[i + 1] = (mul(h[i], B) + (ull)s[i]) % M; p[i + 1] = mul(p[i], B); }
    }
    ull get(int l, int r) { return (h[r] + M - mul(h[l], p[r - l])) % M; }   // s[l..r)
};

// ======================= SELF-TEST =======================
int main() {
    mt19937 rng(12);
    for (int it = 0; it < 500; it++) {
        int n = rng() % 30 + 1; vector<int> a(n); for (auto& x : a) x = rng() % 6;
        auto r = binaryCounterOnes(a); ull s = 0;
        for (int i = 0; i < n; i++) { s += 1ULL << a[i]; assert(r[i] == __builtin_popcountll(s)); }
        string str; for (int i = 0; i < 20; i++) str += "ab"[rng() % 2];
        StrHash H(str);
        for (int q = 0; q < 50; q++) { int l1 = rng() % 20, l2 = rng() % 20, len = rng() % (20 - max(l1, l2)) + 1;
            assert((H.get(l1, l1 + len) == H.get(l2, l2 + len)) == (str.substr(l1, len) == str.substr(l2, len))); }
    }
    assert(power(2, 10) == 1024 && power(3, MOD - 1) == 1);
    Binom B(100); assert(B.C(10, 3) == 120 && B.C(5, 7) == 0);
    auto spf = sieve(100); assert(spf[97] == 97 && spf[91] == 7 && spf[64] == 2);
    unordered_map<ll, int, SafeHash> m; m[5] = 3; assert(m[5] == 3);
    puts("11_bity_matma_hash: OK");
}
