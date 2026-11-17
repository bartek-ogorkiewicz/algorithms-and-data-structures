#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    long long w;
    cin >> n >> m >> w;
    vector<long long> a(n), b(m);
    for (auto& x : a) cin >> x;
    for (auto& x : b) cin >> x;

    sort(a.begin(), a.end());
    sort(b.begin(), b.end());

    long long ans = 0;
    int lo = 0, hi = 0;
    for (int i = 0; i < n; i++) {
        while (lo < m && b[lo] < a[i] - w) lo++;    // za małe
        while (hi < m && b[hi] <= a[i] + w) hi++;   // nie za duże
        ans += hi - lo;
    }
    cout << ans << "\n";
}
