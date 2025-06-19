#include <iostream>
#include <vector>
#include <stack>
#include <cstring>
#include <algorithm>
#include <unordered_set>
using namespace std;

class TarjanSCC {
private:
    int n;                       // ͼ�Ķ�����
    vector<vector<int>>  adj;    // ͼ���ڽӱ�
    vector<int>  dfn;            // ���㱻���ʵ���ʱ���
    vector<int>  low;            // �����ܹ����ݵ�������ʱ��
    vector<bool> inStack;        // �Ƿ���ջ��
    stack<int>   st;             // ջ
    int timeStamp;               // ���㱻���ʵĵ�ǰʱ���
    vector<int>  sccId;          // ÿ���������ڵ�ǿ��ͨ�������
    int sccCount;                // ǿ��ͨ��������
    vector<vector<int>> sccNodes;// ÿ��scc�����Ķ���

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

    const vector<int>& getEdges(int u) const {
        return adj[u];
    }
};


class ShrinkGraph {
private:
    int n;
    vector< unordered_set<int> > adj;
    vector<int> ind, outd;

    void init(int sccCount) {
        n = sccCount;
        ind.resize(n, 0);
        outd.resize(n, 0);
        adj.resize(n, {});
    } 

    void addEdge(int u, int v) {
        if(u == v) {
            return ;
        }
        if (adj[u].find(v) != adj[u].end()) {
            return ;
        }
        adj[u].insert(v);
        outd[u]++;
        ind[v]++;
    }

public:
    // 1 -> 2
    // 3 -> 4
    // 1->3 3->1
    // 2->4 4->2
    // A {1, 3}
    // B {2, 4}
    // A->B A->B
    void shrinkFromSCC(const TarjanSCC& scc) {
        init(scc.getSCCCount());
        for(int i = 0; i < n; ++i) {
            // v ����i���ǿ��ͨ����������ԭͼ����ļ���
            const vector<int>& v = scc.getSCCNodes(i);
            for(int j = 0; j < v.size(); ++j) {
                // org ������ v[j] ��Ϊ��������ԭͼ�ı߼���
                const vector<int>& org = scc.getEdges(v[j]);
                for(int k = 0; k < org.size(); ++k) {
                    // v[j], org[k]
                    int u = scc.getSCCId(v[j]);
                    int v = scc.getSCCId(org[k]);
                    addEdge(u, v);
                }
            }
        }
    }

    int solve() {
        int indCount = 0, outdCount = 0;
        for(int i = 0; i < n; ++i) {
            if( !ind[i])  indCount++;
            if( !outd[i] ) outdCount++;
        }
        return max(indCount, outdCount);
    }
};

int main() {
    int t;
    cin >> t;
    while(t--) {
        int n, m;
        cin >> n >> m;
        TarjanSCC scc(n);
        for(int i = 0; i < m; ++i) {
            int u, v;
            cin >> u >> v;
            scc.addEdge(u, v);
        }
        scc.solve();
        ShrinkGraph sg;
        sg.shrinkFromSCC(scc);
        cout << sg.solve() << endl;
    }
    return 0;
}



/*

1 -> 2 -> 3          <=>     1


1 -> 2 -> 3          <=>     2
4 -> 2

1 -> 2 -> 3          <=>     2
2 -> 4

ͼ�����Ϊ0�ĵ���Ϊx������Ϊ0�ĵ���Ϊy
�𰸾��� max(x, y)

1 -> 2 -> 3 -> 1    ->   A
5 -> 6 -> 7 -> 5    ->   B
1 -> 5 

A -> B
��������

*/