#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    long long s;
    cin >> n >> s;
    vector<long long> a(n);
    for (auto& x : a) cin >> x;

    sort(a.begin(), a.end());

    long long ans = 0;
    int i = 0, j = n - 1;
    while (i < j) {
        if (a[i] + a[j] <= s) {
            ans += j - i;
            i++;
        } else {
            j--;
        }
    }
    cout << ans << "\n";
}
