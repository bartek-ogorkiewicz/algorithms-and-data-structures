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
    vector<int> a(n);
    for (int &x : a) cin >> x;

    int best = 360;
    for (int i = 0; i < n; i++) {
        int s = 0;
        for (int j = i; j < n; j++) {
            s += a[j];
            best = min(best, abs(360 - 2 * s));
        }
    }
    cout << best << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}
