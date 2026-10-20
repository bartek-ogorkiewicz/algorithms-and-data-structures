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
    int n;
    cin >> n;

    ll C = 0;
    ll cap = 0;
    while (cap < n) {
        C++;
        cap = 0;
        for (ll s = 1; s <= C; s++) cap += s * (C / s);
    }

    vector<long long> bags;
    for (long long s = 1; s <= C; s++)
        for (long long k = 0; k < C / s; k++) bags.push_back(s);

    ll extra = cap - n;
    size_t i = 0;
    while (extra > 0) {
        bags[i]--;
        extra--;
        if (bags[i] == 0) i++;
    }

    string out;
    int id = 0;
    for (size_t j = i; j < bags.size(); j++) {
        id++;
        for (ll k = 0; k < bags[j]; k++) {
            out += to_string(id);
            out += ' ';
        }
    }
    out += '\n';
    cout << C << ' ' << out;
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
