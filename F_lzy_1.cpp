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
    bool have_son = false;
    for(int neighbor : graph[node]) {
        if(!dp.visited[neighbor]) {
            have_son = true;
            break;
        }
    }

    if(!have_son)
        return;
    
    dp.visited[node] = true;
    for(int neighbor : graph[node]) {
        if(!dp.visited[neighbor]) 
            dfs(neighbor);
    }

    for(int i : graph[node]) {
        // if visited neighbot
        if(dp.visited[i])
            dp.g[node] += dp.sub[i];
    }

    int maxf = 0;
    for(int i : graph[node]) {
        //if(dp.visited[i]) {
            int tmpf = dp.g[i] + dp.values[i] * dp.values[node];
            for(int j : graph[node]) {
                // if(dp.visited[j] && j != i) 
                if(j != i) 
                    tmpf += dp.sub[j];
            }
            maxf = max(tmpf, maxf);
        //}
    }
    dp.f[node] = maxf;

    dp.sub[node] = max(dp.f[node], dp.g[node]);
}

signed main() {
    cin>>n;
    dp.init(n);

    for(int i = 0; i < n - 1; i++) {
        int a, b;
        cin>>a>>b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    for(int i = 1; i <= n; i++)
        cin>>dp.values[i];

    dfs(1);
    cout<<dp.sub[1]<<endl;

    for(int i = 1; i <= n; i++) {
        cout<<"sub["<<i<<"] = "<<dp.sub[i]<<endl;
        cout<<"f["<<i<<"] = "<<dp.f[i]<<endl;
        cout<<"g["<<i<<"] = "<<dp.g[i]<<endl;
    }

    return 0;
}