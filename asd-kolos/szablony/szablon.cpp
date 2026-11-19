// ============================================================
//  SZABLON NA KOLOS — skopiuj: cp ~/asd-kolos/szablony/szablon.cpp zad.cpp
// ============================================================
#include <bits/stdc++.h>
using namespace std;

#define all(x) (x).begin(), (x).end()
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;

// debug: działa tylko przy kompilacji z -DLOCAL (na Szkopule znika)
#ifdef LOCAL
#define dbg(x) cerr << #x << " = " << (x) << "\n"
#define dbgv(v) do { cerr << #v << " = ["; for (auto& _e : v) cerr << _e << " "; cerr << "]\n"; } while (0)
#else
#define dbg(x)
#define dbgv(v)
#endif

const ll INF = 4e18;      // "nieskończoność" dla ll  (uwaga: INF + INF się przepełni!)
const int IINF = 1e9 + 7; // "nieskończoność" dla int

void solve() {
    int n;
    cin >> n;
    vector<ll> a(n);
    for (auto& x : a) cin >> x;

    // ...

    cout << 0 << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    // cin >> t;          // odkomentuj, jeśli jest wiele testów w jednym wejściu
    while (t--) solve();

    return 0;
}
