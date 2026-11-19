// TRO — Trójki: ile trójek i<j<k z a_i + a_j = a_k, wartości 1..10, n <= 500 000.
// Jedno przejście: cnt[v] = ile razy v było dotąd, pairs[s] = ile par (i<j) dotąd ma sumę s.
// Dla a_k: ans += pairs[a_k]; potem dopisz pary kończące się na k; potem cnt[a_k]++. O(10 n).
// Wynik do ~2*10^16 => long long.
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int n; cin >> n;
    ll cnt[11] = {0}, pairs[21] = {0}, ans = 0;
    for (int k = 0; k < n; k++) {
        int x; cin >> x;
        ans += pairs[x];
        for (int v = 1; v <= 10; v++) pairs[v + x] += cnt[v];
        cnt[x]++;
    }
    cout << ans << "\n";
}
