#include <iostream>
#include <vector>
#include <stack>
#include <cstring>
#include <algorithm>
using namespace std;

class TarjanSCC {
private:
    int n;                       // 图的顶点数
    vector<vector<int>>  adj;    // 图的邻接表
    vector<int>  dfn;            // 顶点被访问到的时间戳
    vector<int>  low;            // 顶点能够回溯到的最早时间
    vector<bool> inStack;        // 是否在栈中
    stack<int>   st;             // 栈
    int timeStamp;               // 顶点被访问的当前时间戳
    vector<int>  sccId;          // 每个顶点属于的强连通分量编号
    int sccCount;                // 强连通分量个数
    vector<vector<int>> sccNodes;// 每个scc包含的顶点

    void tarjanDFS(int u) {
        dfn[u] = low[u] = ++timeStamp;
        st.push(u);
        inStack[u] = true;

        for(int i = 0; i < adj[u].size(); ++i) {
            int v = adj[u][i];
            if( !dfn[v] ) {
                tarjanDFS(v);
                low[u] = min(low[u], low[v]);
            }else if( inStack[v] ) {
                low[u] = min(low[u], dfn[v]);
            }
        }

        if(dfn[u] == low[u]) {
            vector<int> scc;
            int v;

            do {
                v = st.top();
                st.pop();
                inStack[v] = false;
                sccId[v] = sccCount;
                scc.push_back(v);
            }while(v != u);
            sccNodes.push_back( scc );
            sccCount++;
        }
    }
public:
    TarjanSCC(int _n) : n(_n) {
        adj.resize(n + 1);
        dfn.resize(n + 1, 0);
        low.resize(n + 1, 0);
        inStack.resize(n + 1, false);
        sccId.resize(n + 1, 0);
        timeStamp = 0;
        sccCount = 0;
    }

    void addEdge(int u, int v) {
        adj[u].push_back(v);
    }

    void solve() {
        for(int i = 1; i <= n; ++i) {
            if( !dfn[i] ) {
                tarjanDFS(i);
            }
        }
    }

    int getSCCCount() const {
        return sccCount;
    }

    int getSCCId(int u) const {
        return sccId[u];
    }

    const vector<int>& getSCCNodes(int sccId) const {
        return sccNodes[sccId];
    }
};

int main() {
    int n, m;
    cin >> n >> m;
    TarjanSCC scc(n);
    for(int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        scc.addEdge(u, v);
    }
    scc.solve();
    cout << scc.getSCCCount() << endl;

    vector<int> ret;
    for(int i = 0; i < scc.getSCCCount(); ++i) {
        const vector<int>& v = scc.getSCCNodes(i);
        int min = v[0];
        for(int j = 1; j < v.size(); ++j) {
            if(v[j] < min) {
                min = v[j];
            }
        }
        ret.push_back(min);
    }
    sort(ret.begin(), ret.end());
    for(int i = 0; i < ret.size(); ++i) {
        cout << ret[i] << endl;
    }
    return 0;
}
