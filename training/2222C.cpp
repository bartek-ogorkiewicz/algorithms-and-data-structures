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
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) cin >> a[i];

    vector<int> b = a;
    sort(b.begin(), b.end());
    int m = b[(n + 1) / 2];
    vector<int> lt(n + 1, 0), gt(n + 1, 0);
    for (int k = 1; k <= n; k++) {
        lt[k] = lt[k - 1] + (a[k] < m ? 1 : 0);
        gt[k] = gt[k - 1] + (a[k] > m ? 1 : 0);
    }

    const int NEG = -1e9;
    vector<int> f(n + 1, NEG);
    f[0] = 0;

    for (int j = 1; j <= n; j++) {
        for (int i = j; i >= 1; i -= 2) {
            int h = (j - i + 1) / 2;
            int less = lt[j] - lt[i - 1];
            int greater = gt[j] - gt[i - 1];
            if (less <= h && greater <= h) {
                f[j] = max(f[j], f[i - 1] + 1);
            }
        }
    }
    cout << f[n] << "\n";
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
