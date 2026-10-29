#include <bits/stdc++.h>
using namespace std;

#define all(x) (x).begin(), (x).end()
using ll = long long;

void YES() { cout << "YES" << "\n"; }
void NO()  { cout << "NO" << "\n"; }
void answer(bool b) { b ? YES() : NO(); }

const ll INF = 1000000000000;
const ll K = 20;

void solve() {
    int n;
    int m;
    cin >> n >> m;

    vector<int> trap;

    for (int i = 0; i < m; i++) {
        int x;
        cin >> x;
        trap.push_back(x);
    }

    if (m > 0 && trap[m - 1] == n) {
        cout << -1 << "\n";
        return;
    }

    vector<int> board = {0};
    ll usuniete = 0;
    int prev = 0;

    for (int i = 0; i <= m; i++) {
        int p = (i < m) ? trap[i] : n;
        ll gap = (ll)p - prev - 1;
        if (gap > K) {
            usuniete += (gap - K);
            gap = K;
        }
        for (int j = 0; j < gap; j++) board.push_back(0);
        board.push_back(i < m ? 1 : 0);
        prev = p;
    }

    const int ruchy[3][2] = {
        {1, 1},
        {5, 10},
        {10, 100}
    };

    int N = board.size() - 1;
    vector<ll> dp(N + 1, INF);
    dp[0] = 0;
    for (int i = 1; i <= N; i++) {
        if (board[i]) {
            continue;
        } else {
            for (auto& [dl, koszt] : ruchy) {
                if (i >= dl) {
                    dp[i] = min(dp[i], dp[i - dl] + koszt);
                }
            }
        }
    }
    cout << (dp[N] == INF ? -1 : dp[N] + usuniete) << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}
