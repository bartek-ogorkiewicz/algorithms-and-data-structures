// SZA — brute O(n^2) wprost z definicji
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    int n; ll w;
    cin >> n >> w;
    vector<ll> x(n);
    for (auto& v : x) cin >> v;
    ll ans = 0;
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
            if (llabs(x[i] - x[j]) <= w) ans++;
    cout << ans << "\n";
}
