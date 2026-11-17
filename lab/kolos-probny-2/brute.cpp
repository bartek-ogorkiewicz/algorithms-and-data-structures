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
    int cnt = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (abs(a[i] - a[j]) <= w) {
                cnt++;
            }
        }
    }
    cout << cnt << "\n";

}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}
