#include <bits/stdc++.h>
using namespace std;

#define all(x) (x).begin(), (x).end()
using ll = long long;

void solve() {
    int n, w;
    cin >> n >> w;
    vector<int> a(n);
    for (auto& s : a) {
        cin >> s;
    }

    int maxi = 0;
    for (int i = 0; i < n; i++) {
        int cnt = 0;
        for (int j = 0; j < n; j++) {
            if ((ll)a[i] + w >= a[j] && a[j] >= a[i]) {
                cnt++;
            }
        }
        maxi = max(maxi, cnt);
    }
    cout << maxi << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}
