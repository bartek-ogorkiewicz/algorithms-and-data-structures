#include <bits/stdc++.h>
using namespace std;

#define all(x) (x).begin(), (x).end()
using ll = long long;

void solve() {
    int n, m;
    cin >> n >> m;
    vector<ll> pref1(n - 1);
    vector<ll> suf1(n - 1);
    vector<ll> pref2(m - 1);
    vector<ll> suf2(m - 1);
    vector<ll> suma_poziomych(m);
    vector<ll> suma_pionowych(n);
    ll sum = 0;
    int x;
    for (int i = 0; i < n - 1; i++) {
        cin >> x;
        sum += x;
        pref1[i] = x;
    }
    suma_poziomych[0] = sum;
    for (int i = 1; i < m - 1; i++) {
        sum = 0;
        for (int i = 0; i < n - 1; i++) {
            cin >> x;
            sum += x;
        }
        suma_poziomych[i] = sum;
    }
    sum = 0;
    if (m > 1) {
        for (int i = 0; i < n - 1; i++) {
            cin >> x;
            sum += x;
            suf1[i] = x;
        }
        suma_poziomych[m - 1] = sum;
    } else {
        suf1 = pref1;
    }
    sum = 0;

    for (int i = 0; i < m - 1; i++) {
        cin >> x;
        sum += x;
        pref2[i] = x;
    }
    suma_pionowych[0] = sum;
    for (int i = 1; i < n - 1; i++) {
        sum = 0;
        for (int i = 0; i < m - 1; i++) {
            cin >> x;
            sum += x;
        }
        suma_pionowych[i] = sum;
    }
    sum = 0;
    if (n > 1) {
        for (int i = 0; i < m - 1; i++) {
            cin >> x;
            sum += x;
            suf2[i] = x;
        }
        suma_pionowych[n - 1] = sum;
    } else {
        suf2 = pref2;
    }
    sum = 0;


    ll pref_sum2 = 0;
    ll suf_sum2 = suma_pionowych[n - 1];
    ll mini = __LONG_LONG_MAX__;
    ll cur = 0;
    for (int i = 0; i <= m - 1; i++) {
        cur = pref_sum2 + suf_sum2 + suma_poziomych[i];
        mini = min(mini, cur);
        if (i < m - 1) pref_sum2 += pref2[i];
        if (i < m - 1) suf_sum2 -= suf2[i];
    }

    ll pref_sum1 = 0;
    ll suf_sum1 = suma_poziomych[m - 1];
    for (int i = 0; i <= n - 1; i++) {
        cur = pref_sum1 + suf_sum1 + suma_pionowych[i];
        mini = min(mini, cur);
        if (i < n - 1) pref_sum1 += pref1[i];
        if (i < n - 1) suf_sum1 -= suf1[i];
    }
    cout << mini << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}
