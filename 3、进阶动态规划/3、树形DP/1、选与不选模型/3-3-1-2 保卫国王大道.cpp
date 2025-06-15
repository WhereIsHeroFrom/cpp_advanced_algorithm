//////////////////////////////////////////////////////////////////////
///////////////////////简单树形DP模板（选or不选）///////////////////////
//////////////////////////////////////////////////////////////////////
#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

#define type int
#define maxn 200010
#define inf 1000000000
int n;
// dp[i][0] 代表以 i 为根节点的子树，且根节点不选的最大（小）价值（或方案数）
// dp[i][1] 代表以 i 为根节点的子树，且根节点  选的最大（小）价值（或方案数）
type dp[maxn][2];
vector<int> child[maxn];

// 每个要求题目不同，需要做修改
type TreeDPSimple_InitVal(int u, bool isChoose) {
    return isChoose;
}

// 每个要求题目不同，需要做修改
type TreeDPSimple_Opt(type curVal, bool isChoose, type ncVal, type cVal) {
    if(isChoose) {
        return curVal + min(ncVal, cVal);
    }
    return curVal + cVal;
}

// 模板代码，一般不做修改
void TreeDPSimple_Init(int n) {
    for(int i = 0; i <= n; ++i) {
        dp[i][0] = dp[i][1] = inf;
    }
}

// 模板代码，一般不做修改
type TreeDPSimple_DFS(int u, bool isChoose, int fat) {
    type& ans = dp[u][isChoose];
    if(ans != inf) {
        return ans;
    }
    ans = TreeDPSimple_InitVal(u, isChoose);
    for(int i = 0; i < child[u].size(); ++i) {
        int v = child[u][i];
        if(v == fat) continue;
        type nc = TreeDPSimple_DFS(v, false, u);
        type  c = TreeDPSimple_DFS(v,  true, u);
        ans = TreeDPSimple_Opt(ans, isChoose, nc, c);
    }
    return ans;
}

//////////////////////////////////////////////////////////////////////
///////////////////////简单树形DP模板（选or不选）///////////////////////
//////////////////////////////////////////////////////////////////////

int main() {
    cin >> n;
    TreeDPSimple_Init(n);
    for(int i = 0; i < n - 1; ++i) {
        int a, b;
        cin >> a >> b;
        child[b].push_back(a);
        child[a].push_back(b);
    }
    type ans = min(
        TreeDPSimple_DFS(1, true, 0),
        TreeDPSimple_DFS(1, false, 0)
    );
    cout << ans << endl;
    return 0;
}