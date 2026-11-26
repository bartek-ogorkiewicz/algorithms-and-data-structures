//
//
#include <bits/stdc++.h>
using namespace std;

#define all(x) (x).begin(), (x).end()
using ll = long long;

void YES() { cout << "YES" << "\n"; }
void NO()  { cout << "NO" << "\n"; }
void answer(bool b) { b ? YES() : NO(); }

void solve() {
    string s, t;
    cin >> s >> t;
    int cnt[26] = {0};
    for (char c : t) cnt[c - 'a']++;
    for (char c : s) cnt[c - 'a']--;

    for (int k = 0; k < 26; k++) {
        if (cnt[k] < 0) {
            cout << "Impossible" << '\n';
            return;
        }
    }

    string r;
    for (int k = 0; k < 26; k++) {
        r += string(cnt[k], 'a' + k);
    }

    string ans;
    int i = 0;
    int j = 0;
    while (i < s.size() || j < r.size()) {
        if (j < r.size() && (i == s.size() || r[j] < s[i])) ans += r[j++];
        else ans += s[i++];
    }
    cout << ans << '\n';
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
