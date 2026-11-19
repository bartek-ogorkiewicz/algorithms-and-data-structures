// POD — Podciągi rosnące w ciągu o wartościach {1,2,3}: ile niepustych ściśle rosnących podciągów.
// end[v] = ile podciągów kończy się wartością v. Nowy element v: end[v] += 1 + suma end[u<v]. O(n).
// (Ogólnie dla dużych wartości: suma end[u<v] z drzewa Fenwicka.)
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int n; cin >> n;
    ll e1 = 0, e2 = 0, e3 = 0;
    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        if (x == 1) e1 += 1;
        else if (x == 2) e2 += 1 + e1;
        else e3 += 1 + e1 + e2;
    }
    cout << e1 + e2 + e3 << "\n";
}
