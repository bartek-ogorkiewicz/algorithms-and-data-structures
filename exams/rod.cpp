#include <bits/stdc++.h>
using namespace std;

#define all(x) (x).begin(), (x).end()
using ll = long long;

void solve() {
    int n, d;
    cin >> n >> d;
    set<int> ms;
    int pairs = 0;
    for (int i = 0; i < n; i++) {
        int c, a;
        cin >> c >> a;
        if (c == -1) {
            int lower1 = ms.count(a - d);
            int upper1 = ms.count(a + d);
            pairs -= lower1;
            pairs -= upper1;
            ms.erase(a);
            if (pairs != 0) {
                cout << "TAK" << "\n";
            } else {
                cout << "NIE" << "\n";
            }
        } else {
            int lower2 = ms.count(a - d);
            int upper2 = ms.count(a + d);
            ms.insert(a);
            pairs += lower2;
            pairs += upper2;
            if (pairs != 0) {
                cout << "TAK" << "\n";
            } else {
                cout << "NIE" << "\n";
            }

        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}
