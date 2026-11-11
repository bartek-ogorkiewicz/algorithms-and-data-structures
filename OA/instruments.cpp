#include <bits/stdc++.h>
using namespace std;

struct Instrument {
    map<long long, long long> ceny;   // czas -> aktualna cena
    multiset<long long> wszystkie;    // aktualne ceny

    void update(long long t, long long cena) {
        auto it = ceny.find(t);
        if (it != ceny.end()) {
            wszystkie.erase(wszystkie.find(it->second));
        }
        ceny[t] = cena;
        wszystkie.insert(cena);

    }
    bool pusty() const { return wszystkie.empty(); }
    long long maxCena() const { return *wszystkie.rbegin(); }
    long long minCena() const { return *wszystkie.begin(); }
    long long latest() const { return ceny.rbegin()->second; };
    long long priceAt(long long x) const {
        auto it = ceny.upper_bound(x);
        if (it == ceny.begin()) return -1;
        return prev(it)->second;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    unordered_map<string, Instrument> instr;
    string cmd, name;
    while (cin >> cmd) {
        if (cmd == "UPDATE") {
            long long t, cena;
            cin >> t >> name >> cena;
            instr[name].update(t, cena);
        } else if (cmd == "LATEST") {
            cin >> name;
            auto it = instr.find(name);
            if (it == instr.end() || it->second.pusty()) cout << "NONE\n";
            else cout << it->second.latest() << "\n";
        } else if (cmd == "MAX" || cmd == "MIN") {
            cin >> name;
            auto it = instr.find(name);
            if (it == instr.end() || it->second.pusty()) cout << "NONE\n";
            else if (cmd == "MAX") cout << it->second.maxCena() << "\n";
            else cout << it->second.minCena() << "\n";
        } else if (cmd == "PRICE_AT") {
            long long t;
            cin >> name >> t;
            auto it = instr.find(name);
            long long w = (it == instr.end()) ? -1 : it->second.priceAt(t);
            if (w == -1) cout << "NONE\n";
            else cout << w << "\n";
        }
    }
}