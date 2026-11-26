//
//
#include <bits/stdc++.h>
using namespace std;

#define all(x) (x).begin(), (x).end()
using ll = long long;

void YES() { cout << "YES" << "\n"; }
void NO()  { cout << "NO" << "\n"; }
void answer(bool b) { b ? YES() : NO(); }

void solve() {
    int n;
    cin >> n;
    vector<ll> f(n);
    for (auto& s : f) {
        cin >> s;
    }
    vector<ll> a(n);
    for (int i = 1; i < n - 1; i++) {
        a[i] = (f[i + 1] - 2 * f[i] + f[i - 1]) / 2;
    }
    ll a1 = f[n - 1];
    ll an = f[0];
    for (int i = 0; i < n; i++) {
        an -= abs((i)) * a[i];
    }
    an = an / abs(n - 1);
    a[n - 1] = an;
    for (int i = 0; i < n; i++) {
        a1 -= abs((i + 1 - n)) * a[i];
    }
    a1 = a1 / abs(1 - n);
    a[0] = a1;
    for (int i = 0; i < n; i++) {
        cout << a[i] << " ";
    }
    cout << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}
