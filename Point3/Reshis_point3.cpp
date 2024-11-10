#include <iostream>
#include <vector>

using namespace std;

/// Граф из задания лежит в cmake-build-debug/input.txt

/*  g - изначальный граф, представляемый в виде списка смежности,
 *  g_t - транспонированный граф,
 *  comps_consists - из каких вершин состоит i-я компонента связности,
 *  comps - какой компоненте принадлежит v-я вершина,
 *  top - вектор топологической сортировки,
 *  used - вектор, отвечающий за проверку посещения вершины,
 *  comp - отвечает за номер текущей компоненты.
*/

vector<vector<int>> g, g_t, comps_consists;
vector<int> comps, top;
vector<bool> used;
int comp = 0;

/// Топологическая сортировка

void topsort(int v) {
    used[v] = true;
    for (int to : g[v]) {
        if (!used[to]) {
            topsort(to);
        }
    }
    top.push_back(v);
}

/// Выделение компоненты сильной связности

void dfs(int v) {
    comps[v] = comp;
    for (int to : g_t[v]) {
        if (!comps[to]) {
            dfs(to);
        }
    }
}

/* n - количество вершин,
 * m - количество ребер в графе.
 */

/// Читаем граф, вызываем топологическую сортировку, выделяем компоненты,
/// объединяем вершины в компоненты, выводим результат.

void solve() {
    int n, m;
    cin >> n >> m;
    g.resize(n + 1);
    g_t.resize(n + 1);
    comps.resize(n + 1);

    for (int i = 0; i < m; i++) {
        int v, u;
        cin >> v >> u;
        g[v].push_back(u);
        g_t[u].push_back(v);
    }

    used.assign(n + 1, false);
    for (int v = 1; v <= n; v++) {
        if (!used[v]) {
            topsort(v);
        }
    }

    reverse(top.begin(), top.end());
    for (int v : top) {
        if (!comps[v]) {
            comp++;
            dfs(v);
        }
    }

    comps_consists.resize(comp + 1);
    for (int v = 1; v <= n; v++) {
        comps_consists[comps[v]].push_back(v);
    }

    for (int v = 1; v <= n; v++) {
        cout << "Состав группы, в которую входит вершина " << v << ":\n";
        sort(comps_consists[comps[v]].begin(), comps_consists[comps[v]].end());
        for (int u : comps_consists[comps[v]]) {
            cout << u << ' ';
        }
        cout << '\n' << "Ее размер равен " << comps_consists[comps[v]].size() << "\n\n";
    }
}

int main() {
    freopen("input.txt", "r", stdin);
    solve();
    return 0;
}