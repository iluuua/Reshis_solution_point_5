#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>

using namespace std;

void solve() {
    int cnt_rounds;
    int n, m;
    cin >> n >> m >> cnt_rounds;
    vector<vector<int>> g(n + 1);
    vector<int> out(n + 1);

    for (int i = 0; i < m; i++) {
        int v, u;
        cin >> v >> u;
        g[v].push_back(u);
        out[v]++;
    }

    vector<vector<long double>> cnt(cnt_rounds + 1, vector<long double>(n + 1));
    for (int v = 1; v <= n; v++) {
        cnt[0][v] = 1;
    }

    for (int round = 1; round <= cnt_rounds; round++) {
        for (int v = 1; v <= n; v++) {
            for (int u : g[v]) {
                cnt[round][u] += cnt[round - 1][v] * ((long double)1 / (long double)out[v]);
            }
        }
    }

    for (int v = 1; v <= n; v++) {
        cnt[cnt_rounds][v] = round(cnt[cnt_rounds][v] * 100) / 100;
    }
    cout << fixed << setprecision(2);

    for (int v = 1; v <= n; v++) {
        cout << cnt[cnt_rounds][v] << ' ';
    }
}

int main() {
    freopen("input.txt", "r", stdin);
    solve();
    return 0;
}