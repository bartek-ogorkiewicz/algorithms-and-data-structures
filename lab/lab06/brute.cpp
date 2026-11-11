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
    ll sum = 0;
    for (int i = 0; i < n; i++) {
        int maxi = 0;
        for (int j = i; j < n; j++) {
            maxi = max(maxi, a[j]);
            sum += maxi;
        }
    }
    cout << sum << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}
