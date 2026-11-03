#include <bits/stdc++.h>
using namespace std;

#define all(x) (x).begin(), (x).end()
using ll = long long;
const int N = 500020;

void solve() {
    int n;
    cin >> n;
    vector<int> tab(n);
    for (int i = 0; i < n; i++) {
        cin >> tab[i];
    }

    vector<int> poz(N, 0);
    int ones = 0;
    for (int i = 0; i < n; i++) {
        int j = tab[i];
        while (poz[j] != 0) {
            ones--;
            poz[j++] = 0;
        }
        poz[j] = 1;
        ones++;
        cout << ones << "\n";
    }

}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}
