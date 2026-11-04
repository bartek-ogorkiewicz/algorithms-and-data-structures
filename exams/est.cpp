#include <bits/stdc++.h>
using namespace std;

#define all(x) (x).begin(), (x).end()
using ll = long long;

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    sort(all(a));

    int maxi = 1;
    int cur = 1;
    for (int i = 1; i < n; i++) {
        if (abs(a[i] - a[i - 1]) <= 1) {
            cur++;
        } else {
            cur = 1;
        }
        maxi = max(maxi, cur);
    }
    cout << maxi << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}
