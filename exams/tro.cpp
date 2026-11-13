#include <bits/stdc++.h>
using namespace std;

#define all(x) (x).begin(), (x).end()
using ll = long long;

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto& s : a) {
        cin >> s;
    }
    vector<ll> cnt(11, 0);
    vector<ll> pairs(21, 0);
    ll wynik = 0;
    for (int i = 0; i < n; i++) {
        ll x = a[i];
        wynik += pairs[x];
        for (int j = 1; j <= 10; j++) {
            pairs[x + j] += cnt[j];
        }
        cnt[x]++;
    }
    cout << wynik << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}
