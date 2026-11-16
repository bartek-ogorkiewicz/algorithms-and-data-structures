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
    vector<int> L(n), R(n);
    for (int i = 0; i < n; i++) {
        int j = i - 1;
        while (j >= 0 && a[j] < a[i]) {
            j = L[j];
        }
        L[i] = j;
    }
    for (int i = n - 1; i >= 0; i--) {
        int j = i + 1;
        while (j < n && a[j] <= a[i]) {
            j = R[j];
        }
        R[i] = j;
    }
    ll sum = 0;
    for (int i = 0; i < n; i++) {
        sum += (ll)a[i] * (i - L[i]) * (R[i] - i);
    }
    cout << sum << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}
