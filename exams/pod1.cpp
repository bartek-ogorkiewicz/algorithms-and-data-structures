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
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    ll jedynek = 0;
    ll dwojek = 0;
    ll dwojek_po_jeden = 0;
    ll wszystkich = 0;
    for (int i = 0; i < n; i++) {
        if (a[i] == 1) {
            jedynek++;
            wszystkich++;
        }
        if (a[i] == 2) {
            dwojek++;
            dwojek_po_jeden += jedynek;
            wszystkich += jedynek;
            wszystkich++;
        }
        if (a[i] == 3) {
            wszystkich++;
            wszystkich += dwojek;
            wszystkich += dwojek_po_jeden;
            wszystkich += jedynek;
        }
    }
    cout << wszystkich << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}
