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
    ll n;
    cin >> n;
    vector<ll> b(n);
    for (auto& s : b) {
        cin >> s;
    }
    vector<ll> h = b;
    sort(h.begin(), h.end());
    ll how_much = 1;
    ll maxi = 0;

    map<ll, ll> u;
    if (h[0] != 0) {
        cout << -1 << "\n";
        return;
    }
    for (int i = 1; i < n; i++) {
        if (h[i] == h[i - 1]) {
            how_much++;
        } else {
            ll num = (h[i] - h[i - 1]) / how_much;
            if ((h[i] - h[i - 1] ) % how_much != 0) {
                cout << -1 << "\n";
                return;
            }
            if (num <= maxi) {
                cout << -1 << "\n";
                return;
            }
            u.insert({h[i - 1], num});
            maxi = num;
            how_much = 1;
        }
    }
    u.insert({h[n - 1], maxi + 1});
    vector<ll> a(n, 0);
    for (int i = 0; i < n; i++) {
        a[i] = u[b[i]];
    }
    for (auto& s : a) {
        cout << s << " ";
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
