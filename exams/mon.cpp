#include <bits/stdc++.h>
using namespace std;

#define all(x) (x).begin(), (x).end()
using ll = long long;

int kierunek(int a, int b) {
    if (a < b) {
        return 1;
    }
    if (a == b) {
        return 0;
    }
    if (a > b) {
        return -1;
    }
    return 2;
}
void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    long long podciagi = 0;
    int parz = 0, nparz = 0;
    int mon = 2;
    int pPrev = 0;
    int pCur = a[0] % 2;
    for (int i = 1; i < n; i++) {
        int d = kierunek(a[i-1], a[i]);
        if (d != mon) {
            mon = d;
            parz = 0;
            nparz = 0;
        }

        if (pPrev == 0) {
            parz++;
        } else {
            nparz++;
        }

        int pNext = (pCur + a[i]) % 2;
        podciagi += (pNext == 0) ? parz : nparz;

        pPrev = pCur;
        pCur = pNext;
    }

    cout << podciagi << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}
