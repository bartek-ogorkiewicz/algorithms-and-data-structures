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

    long long sumsq = 0;
    long long sumofsq = 0;

    for (int i = 0; i < n; i++) {
        sumsq = (sumsq + a[i]) % MOD;
        sumofsq = (sumofsq + (long long)a[i] * a[i]) % MOD;
    }

    sumsq = (long long)sumsq * sumsq % MOD;

    sum = (n - 1) * sumofsq % MOD;
    sum -= ((sumsq % MOD) - sumofsq) % MOD;
    cout << (sum % MOD + MOD) % MOD << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}
