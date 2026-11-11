#include <bits/stdc++.h>
using namespace std;

#define all(x) (x).begin(), (x).end()
using ll = long long;

void solve() {
    int n;
    cin >> n;

    vector<int> a;
    a.push_back(-1);
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        a.push_back(x);
        sort(all(a));
        cout << a[(i + 1 + 1)/2] << "\n";

    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}
