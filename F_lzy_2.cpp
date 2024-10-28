#include <iostream>
#include <unordered_map>
#include <vector>
#define int long long
using namespace std;

struct {
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

    // 先处理所有子节点
    for (int neighbor : graph[node]) {
        if (!dp.visited[neighbor]) {
            dfs(neighbor);
        }
    }

    // 计算 g[node]
    for (int neighbor : graph[node]) {
        if (dp.visited[neighbor]) {
            dp.g[node] += dp.sub[neighbor]; // 计算不合并的情况
        }
    }

    // 计算 f[node]
    int maxf = 0;
    for (int neighbor : graph[node]) {
        if (dp.visited[neighbor]) {
            int tmpf = dp.g[neighbor] + dp.values[neighbor] * dp.values[node];
            for (int other : graph[node]) {
                if (other != neighbor && dp.visited[other]) {
                    tmpf += dp.sub[other]; // 加上其他子树的值
                }
            }
            maxf = max(tmpf, maxf);
        }
    }
    dp.f[node] = maxf;

    // 计算 sub[node]
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

    for (int i = 1; i <= n; i++)
        cin >> dp.values[i];

    dfs(1);
    cout << dp.sub[1] << endl;

    return 0;
}