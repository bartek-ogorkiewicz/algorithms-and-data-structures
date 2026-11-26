//
//
#include <bits/stdc++.h>
using namespace std;

#define all(x) (x).begin(), (x).end()
using ll = long long;

void YES() { cout << "YES" << "\n"; }
void NO()  { cout << "NO" << "\n"; }
void answer(bool b) { b ? YES() : NO(); }

ll f(const string &s) {
    int allB = count(all(s), 'b');
    int bBefore = 0;
    ll dp = 0;
    for (char c : s) {
        if (c == 'b') bBefore++;
        else dp += min(bBefore, allB - bBefore);
    }
    return dp;
}

void solve() {
    int n;
    string s;
    cin >> n >> s;

    string t = s;
    for (char &c : t) c = (c == 'a' ? 'b' : 'a');

    cout << min(f(s), f(t)) << "\n";
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
