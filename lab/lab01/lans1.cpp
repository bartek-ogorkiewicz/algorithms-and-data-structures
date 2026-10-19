#include <iostream>
#include <vector>

using namespace std;

const int MOD = 1'000'000'007;

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    long long sum = 0;
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            long long x = a[j] - a[i];
            sum = (sum + (x * x)) % MOD;
        }
    }

    cout << (sum + MOD) % MOD << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}
