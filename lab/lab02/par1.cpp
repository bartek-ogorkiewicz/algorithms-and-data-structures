#include <iostream>
#include <vector>

using namespace std;

const int MOD = 1'000'000'007;

struct Zdarzenie {
    int czas;
    int delta;
};

bool Cmp(Zdarzenie a, Zdarzenie b) {
    return a.czas < b.czas;
};

void solve() {
    int n;
    cin >> n;
    vector<Zdarzenie> cars;
    for (int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;
        Zdarzenie a, b;
        a.czas = x;
        a.delta = 1;
        b.czas = y;
        b.delta = -1;
        cars.push_back(a);
        cars.push_back(b);
    }
    sort(cars.begin(), cars.end(), Cmp);
    int max_time = 0;
    int max_cars = 0;
    int car = 0;

    for (int i = 0; i < 2 * n; i++) {
        car += cars[i].delta;
        if (car > max_cars) {
            max_cars = car;
            max_time = cars[i].czas;
        }
    }
    cout << max_cars << ' ' << max_time << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}
