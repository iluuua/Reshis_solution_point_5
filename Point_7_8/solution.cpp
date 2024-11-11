#include <iostream>
#include <vector>
#include <queue>

using namespace std;

/// Граф из задания лежит в cmake-build-debug/input.txt

/// BFS или DFS?

void bfs_solve() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> g(n + 1);
    for (int i = 0; i < m; i++) {
        int v, u;
        cin >> v >> u;
        g[v].push_back(u);
    }

    vector<char> decode = {'%', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'};
    vector<bool> used(n + 1);
    used[5] = true;
    vector<int> ans;
    queue<int> q;
    q.push(5);

    while (!q.empty()) {
        int v = q.front();
        ans.push_back(v);
        q.pop();

        for (int u : g[v]) {
            if (!used[u]) {
                used[u] = true;
                q.push(u);
            }
        }
    }

    for (int v : ans) {
        cout << decode[v] << ' ';
    }
}

void dfs_solve() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> g(n + 1);
    for (int i = 0; i < m; i++) {
        int v, u;
        cin >> v >> u;
        g[v].push_back(u);
        g[u].push_back(v);
    }

    vector<bool> used(n + 1);
    vector<int> ans;
    vector<char> decode = {'%', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'};

    function<void(int)> dfs = [&](int v) -> void {
        used[v] = true;
        ans.push_back(v);
        for (int u : g[v]) {
            if (!used[u]) {
                dfs(u);
            }
        }
    };
    dfs(1);

    for (int v : ans) {
        cout << decode[v] << ' ';
    }
}

int main() {
    freopen("input.txt", "r", stdin);
    dfs_solve();
    return 0;
}