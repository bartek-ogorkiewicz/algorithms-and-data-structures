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
    sort(a.begin(), a.end());

    int maxi = 0;
    int cnt = 0;
    int i = 0;
    int j = 0;
    while (i < n) {
        while (j < n && a[j] < (ll)a[i] + w) {
            cnt++;
            j++;
        }
        maxi = max(maxi, cnt);
        i++;
        cnt--;
    }
    cout << maxi << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}
