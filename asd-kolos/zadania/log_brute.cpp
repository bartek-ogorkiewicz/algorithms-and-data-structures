// LOG — brute O(n^2): dla każdego punktu jako początku przedziału policz punkty w [t_i, t_i + w]
// BRUTE MA BYĆ GŁUPI I OCZYWISTY — bez sortowania, bez sprytu.
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    int n; ll w;
    cin >> n >> w;
    vector<ll> t(n);
    for (auto& x : t) cin >> x;
    int best = 0;
    for (int i = 0; i < n; i++) {
        int cnt = 0;
        for (int j = 0; j < n; j++)
            if (t[i] <= t[j] && t[j] <= t[i] + w) cnt++;
        best = max(best, cnt);
    }
    cout << best << "\n";
}
