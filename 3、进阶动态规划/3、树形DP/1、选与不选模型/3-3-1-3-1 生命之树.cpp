//////////////////////////////////////////////////////////////////////
///////////////////////������DPģ�壨ѡor��ѡ��///////////////////////
//////////////////////////////////////////////////////////////////////
#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

#define type long long
#define maxn 100010
#define inf -1000000000000ll
int n;
// dp[i][0] ������ i Ϊ���ڵ���������Ҹ��ڵ㲻ѡ�����С����ֵ���򷽰�����
// dp[i][1] ������ i Ϊ���ڵ���������Ҹ��ڵ�  ѡ�����С����ֵ���򷽰�����
type dp[maxn][2];
vector<int> child[maxn];
type w[maxn];

// ÿ��Ҫ����Ŀ��ͬ����Ҫ���޸�
type TreeDPSimple_InitVal(int u, bool isChoose) {
    return w[u] * isChoose;
}

// ÿ��Ҫ����Ŀ��ͬ����Ҫ���޸�
type TreeDPSimple_Opt(type curVal, bool isChoose, type ncVal, type cVal) {
    if(isChoose) {
        return curVal + max(ncVal, cVal);
    }
    return 0;
}

// ģ����룬һ�㲻���޸�
void TreeDPSimple_Init(int n) {
    for(int i = 0; i <= n; ++i) {
        dp[i][0] = dp[i][1] = inf;
    }
}

// ģ����룬һ�㲻���޸�
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
///////////////////////������DPģ�壨ѡor��ѡ��///////////////////////
//////////////////////////////////////////////////////////////////////


int main() {
    cin >> n;
    TreeDPSimple_Init(n);
    for(int i = 1; i <= n; ++i) {
        cin >> w[i];
    }
    for(int i = 0; i < n - 1; ++i) {
        int a, b;
        cin >> a >> b;
        child[b].push_back(a);
        child[a].push_back(b);
    }
    type ans = inf;
    for(int i = 1; i <= n; ++i) {
        TreeDPSimple_DFS(i, 0, 0);
        TreeDPSimple_DFS(i, 1, 0);
        ans = max(ans, max(dp[i][0], dp[i][1]) );
    }
    cout << ans << endl;
    return 0;
}