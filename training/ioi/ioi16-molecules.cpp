#include "molecules.h"
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

vector<int> find_subset(int l, int u, vector<int> w) {
    int n = w.size();
    vector<pair<ll, int>> v(n);
    for (int i = 0; i < n; i++) v[i] = {w[i], i};
    sort(v.begin(), v.end());

    ll a = 0, b = 0;
    for (int k = 1; k <= n; k++) {
        a += v[k - 1].first;
        b += v[n - k].first;
        if (a > u || b < l) continue;


        ll sum = a;
        for (int s = 0; s + k <= n; s++) {
            if (s > 0) sum += v[s + k - 1].first - v[s - 1].first;
            if (l <= sum && sum <= u) {
                vector<int> res;
                for (int j = s; j < s + k; j++) res.push_back(v[j].second);
                return res;
            }
        }
    }
    return {};
}
