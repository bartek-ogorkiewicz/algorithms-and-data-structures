// ZOL — Żołnierze. Usuwamy żołnierza i, wypisz lewego i prawego sąsiada (-1 gdy brak).
// Lista dwukierunkowa na tablicach, wartownicy 0 i n+1. O(n).
#include <bits/stdc++.h>
using namespace std;
int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int n; cin >> n;
    vector<int> L(n + 2), R(n + 2);
    for (int i = 1; i <= n; i++) { L[i] = i - 1; R[i] = i + 1; }
    for (int k = 0; k < n; k++) {
        int x; cin >> x;
        cout << (L[x] == 0 ? -1 : L[x]) << " " << (R[x] == n + 1 ? -1 : R[x]) << "\n";
        R[L[x]] = R[x]; L[R[x]] = L[x];      // wypnij x
    }
}
