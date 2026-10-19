#include <iostream>
#include <vector>

using namespace std;

const int MOD = 1'000'000'007;

void solve() {
    int n;
    cin >> n;
    vector<pair<int, int>> cars;
    for (int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;
        cars.push_back({x, y});
    }
    sort(cars.begin(), cars.end());
    int max_time = 0;
    int max_cars = 0;
    int car = 0;
    for (int i = 0; i < n; i++) {
        car = 0;
        for (int j = 0; j < n; j++) {
            if (cars[j].first <= cars[i].first && cars[i].first < cars[j].second) {
                car++;
            }
        }
        if (car > max_cars) {
            max_time = cars[i].first;
            max_cars = car;
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
