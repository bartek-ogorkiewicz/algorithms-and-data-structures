// ODC — Odcinki pionowe: ile par się przecina (domknięte, żadne dwa nie mają wspólnego końca).
// Przecinać mogą się tylko odcinki o tym samym x. W grupie: pary - pary rozłączne,
// rozłączne = suma po i: #(j: y2_j < y1_i)  (binsearch po posortowanych końcach). O(n log n).
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
struct Seg { int x, y1, y2; };
int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int n; cin >> n;
    vector<Seg> s(n);
    for (auto& [x, y1, y2] : s) cin >> x >> y1 >> y2;
    sort(s.begin(), s.end(), [](const Seg& a, const Seg& b) { return a.x < b.x; });
    ll ans = 0;
    for (int i = 0; i < n;) {
        int j = i; while (j < n && s[j].x == s[i].x) j++;     // grupa [i, j)
        vector<int> ends; for (int k = i; k < j; k++) ends.push_back(s[k].y2);
        sort(ends.begin(), ends.end());
        ll c = j - i, disjoint = 0;
        for (int k = i; k < j; k++) disjoint += lower_bound(ends.begin(), ends.end(), s[k].y1) - ends.begin();
        ans += c * (c - 1) / 2 - disjoint;
        i = j;
    }
    cout << ans << "\n";
}
