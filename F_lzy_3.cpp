#include <iostream>
#include <unordered_map>
#include <vector>
#include <algorithm>
#define int long long
using namespace std;

struct DP {
    vector<int> values;
    vector<bool> visited;
    vector<int> sub;
    vector<int> f;
    vector<int> g;

    void init(int n) {
        values.resize(n + 1, 0);
        visited.resize(n + 1, false);
        sub.resize(n + 1, 0);
        f.resize(n + 1, 0);
        g.resize(n + 1, 0);
    }
} dp;

int n;
unordered_map<int, vector<int>> graph;

void dfs(int node) {
    dp.visited[node] = true;

    for (int neighbor : graph[node]) {
        if (!dp.visited[neighbor]) {
            dfs(neighbor);
        }
    }

    int sum_g = 0;
    int max_f = 0;

    for (int neighbor : graph[node]) {
        if (dp.visited[neighbor]) {
            sum_g += dp.sub[neighbor];
        }
    }

    dp.g[node] = sum_g;

    for (int i : graph[node]) {
        if (dp.visited[i]) {
            int tmp_f = dp.g[i] + dp.values[node] * dp.values[i];
            for (int j : graph[node]) {
                if (j != i) {
                    tmp_f += dp.sub[j];
                }
            }
            max_f = max(tmp_f, max_f);
        }
    }

    dp.f[node] = max_f;
    dp.sub[node] = max(dp.f[node], dp.g[node]);
}

signed main() {
    cin >> n;
    dp.init(n);

    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    for (int i = 1; i <= n; i++) {
        cin >> dp.values[i];
    }

    dfs(1);
    cout << dp.sub[1] << endl;

    for (int i = 1; i <= n; i++) {
        cout << "sub[" << i << "] = " << dp.sub[i] << endl;
        cout << "f[" << i << "] = " << dp.f[i] << endl;
        cout << "g[" << i << "] = " << dp.g[i] << endl;
    }

    return 0;
}