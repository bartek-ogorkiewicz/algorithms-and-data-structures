#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;
    vector<long long> a(n);
    for (auto& x : a) cin >> x;

    sort(a.begin(), a.end());

    long long ans = LLONG_MAX;
    for (int i = 0; i + k - 1 < n; i++) {
        ans = min(ans, a[i + k - 1] - a[i]);
    }
    cout << ans << "\n";
}
