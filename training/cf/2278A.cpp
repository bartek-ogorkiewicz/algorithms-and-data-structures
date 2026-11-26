#include <bits/stdc++.h>
using namespace std;

#define all(x) (x).begin(), (x).end()
using ll = long long;

void YES() { cout << "YES" << "\n"; }
void NO()  { cout << "NO" << "\n"; }
void answer(bool b) { b ? YES() : NO(); }

void solve() {
    int x, y;
    cin >> x >> y;
    string p, q;
    cin >> p >> q;
    if (x - y != 3) {
        cout << "NO" << "\n";
        return;
    }
    vector<int> cnt(26, 0);

    for (char c : p) {
        cnt[c - 'a']++;
    }
    for (char c : q) {
        cnt[c - 'a']--;
    }
    cnt['s' - 'a']--;
    cnt['i' - 'a']--;
    cnt['x' - 'a']--;
    bool ok = true;
    for (int k = 0; k < 26; k++) if (cnt[k] != 0) ok = false;
    cout << (ok ? "YES" : "NO") << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}
