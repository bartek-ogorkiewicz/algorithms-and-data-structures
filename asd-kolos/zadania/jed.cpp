// JED — Jedynki: po dodaniu kolejnych 2^{a_i} wypisz liczbę jedynek w zapisie binarnym sumy.
// Licznik binarny: gaś jedynki od pozycji a_i (każda -1), zapal pierwsze zero (+1).
// Zamortyzowane O(1) na operację (potencjał = liczba jedynek). Tablica bitów do max(a)+~20.
#include <bits/stdc++.h>
using namespace std;
int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int n; cin >> n;
    vector<char> bit(500000 + 64, 0); int ones = 0;
    for (int i = 0; i < n; i++) {
        int p; cin >> p;
        while (bit[p]) { bit[p] = 0; ones--; p++; }
        bit[p] = 1; ones++;
        cout << ones << "\n";
    }
}
