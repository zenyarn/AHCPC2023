#include <iostream>
#include <unordered_map>
#include <vector>
#define int long long

using namespace std;

struct DPState {
    vector<int> values;    // 存储每个节点的吸光能力值
    vector<bool> visited;  // 记录节点是否被访问
    vector<int> sub;      // 存储子树的最大吸光能力
    vector<int> f;        // 存储选择当前节点与子节点配对的最大值
    vector<int> g;        // 存储不选择当前节点配对的最大值
    
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

// dfs函数现在接收两个参数：当前节点和其父节点
void dfs(int node, int parent) {
    dp.visited[node] = true;
    
    // 递归处理所有子节点
    for(int neighbor : graph[node]) {
        if(!dp.visited[neighbor]) {
            dfs(neighbor, node);
        }
    }
    
    // 计算g[node]：累加所有子节点的sub值
    dp.g[node] = 0;  // 确保初始值为0
    for(int neighbor : graph[node]) {
        if(neighbor != parent) {
            dp.g[node] += dp.sub[neighbor];
        }
    }
    
    // 计算f[node]：尝试与每个子节点配对
    dp.f[node] = 0;  // 确保初始值为0
    for(int child : graph[node]) {
        if(child != parent) {
            // 选择当前子节点配对时的值
            int tmp = dp.values[node] * dp.values[child] + dp.g[child];
            
            // 加上其他子节点的sub值
            for(int other : graph[node]) {
                if(other != parent && other != child) {
                    tmp += dp.sub[other];
                }
            }
            dp.f[node] = max(dp.f[node], tmp);
        }
    }
    
    // 更新sub[node]
    dp.sub[node] = max(dp.f[node], dp.g[node]);
}

signed main() {
    // 输入处理
    cin >> n;
    dp.init(n);
    
    // 读入边的信息
    for(int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }
    
    // 读入节点的吸光能力值
    for(int i = 1; i <= n; i++) {
        cin >> dp.values[i];
    }
    
    // 从根节点1开始DFS，父节点设为0
    dfs(1, 0);
    
    // 输出结果
    cout << dp.sub[1] << endl;
    
    // 输出调试信息
    for(int i = 1; i <= n; i++) {
        cout << "sub[" << i << "] = " << dp.sub[i] << endl;
        cout << "f[" << i << "] = " << dp.f[i] << endl;
        cout << "g[" << i << "] = " << dp.g[i] << endl;
    }
    
    return 0;
}

void printDebugInfo() {
    cout << "Debug Information:" << endl;
    for(int i = 1; i <= n; i++) {
        cout << "Node " << i << ":" << endl;
        cout << "  sub[" << i << "] = " << dp.sub[i] << endl;
        cout << "  f[" << i << "] = " << dp.f[i] << endl;
        cout << "  g[" << i << "] = " << dp.g[i] << endl;
        cout << "  value[" << i << "] = " << dp.values[i] << endl;
        cout << "  neighbors: ";
        for(int neighbor : graph[i]) {
            cout << neighbor << " ";
        }
        cout << endl;
    }
}
