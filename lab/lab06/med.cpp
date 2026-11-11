#include <bits/stdc++.h>
using namespace std;

#define all(x) (x).begin(), (x).end()
using ll = long long;

void solve() {
    int n;
    cin >> n;

    priority_queue<int> L;
    priority_queue<int, vector<int>, greater<int>> R;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        if (L.empty() || x <= L.top()) L.push(x);
        else R.push(x);

        if (L.size() > R.size() + 1) { R.push(L.top()); L.pop(); }
        else if (R.size() > L.size()) { L.push(R.top()); R.pop(); }
        cout << L.top() << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}
