#include <iostream>
#include <vector>
using namespace std;

// dp[i][j] 代表以 i 作为根结点，想要得到 j 个气球的最小力气
// KnapsackTree_GetAnswer 增加 w 参数
//////////////////////////////////////////////////////////////////////////////
///////////////////////////////// 树上背包模板 ////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

// 求解数据的数据类型
#define type int
// 物品的总个数（树的顶点个数）
#define maxn 5010
// 总共可以选择的最大容量
#define maxv 5010
// 物品结构体
struct Item {
    int vol;    // 每个物品的容量  
    int wei;    // 每个物品的权值
    int edge;   // 前向边权值
}items[maxn];
// 树形关系（双向图）
vector<int> child[maxn];
// dp[i][j] 代表以i为根的子树中，选择容量总和为j的物品，得到的最优价值
type dp[maxn][maxv];
// sumVol[i] 代表所有子结点的容量和
int sumVol[maxn];
// n件物品，最大容量为V
int n, V;

// 初始状态值
// 需要根据题目含义进行修改
type KnapsackTree_InitValue(int u) {
    return 0;
}

// 非法状态值（求最大值时选最小，求最小值时选最大）
// 需要根据题目含义进行修改
type KnapsackTree_InfValue() {
    return 1000000000;
}

// 每次状态转移开始时，状态的初始值
// 如果是加边模板，则直接返回 KnapsackTree_InfValue
// 如果是删边模板，则需要根据 v 的值进行判定
type KnapsackTree_CurInitValue(type dpu[maxv], int v) {
    return KnapsackTree_InfValue();
}

// 状态转移方程
// 需要根据题目含义进行修改
type KnapsackTree_Opt(type curVal, type preVal, type itemWei) {
    return min(curVal, preVal + itemWei);
}

// 这一步非常关键，目的是把 滚动数组 dpu 中计算出的数据，转移到 dp 上
// dpu 是临时数据，递归结束就销毁了
// dp 是持久化数据，递归结束一直保存
void KnapsackTree_Post(int u, int fat, type dpu[maxv]) {
    for(int j = 0; j <= V; ++j) {
        dp[u][j] = dpu[j];
    }
    dp[u][ sumVol[u] ]   = KnapsackTree_Opt(dp[u][ sumVol[u] ], items[u].edge, 0);
    dp[u][ sumVol[u]-1 ] = KnapsackTree_Opt(dp[u][ sumVol[u]-1 ], items[u].wei, 0);
}

// 获取最优解，根据题目要求执行逻辑
type KnapsackTree_GetAnswer(int root, int w) {
    type ans = KnapsackTree_InfValue();
    for(int i = n; i >= 0; --i) {
        if(dp[root][i] <= w) {
            return i;
        }
    }
    return 0;
}

// 模版代码，基本不用改
int KnapsackTree_Init(type dpu[2][maxv], int u) {
    int pre = 0;
    dpu[pre][0] = KnapsackTree_InitValue(u);
    for(int i = 1; i <= V; ++i) {
        dpu[pre][i] = KnapsackTree_InfValue();
    }
    return pre;
}

// 模版代码，基本不用改
void KnapsackTree_DFS(int u, int fat) {
    type dpu[2][maxv];
    int pre = KnapsackTree_Init(dpu, u);
    int cur = 1 - pre;
    sumVol[u] = items[u].vol;
    for(int i = 0; i < child[u].size(); ++i) {
        int v = child[u][i];
        if(v == fat) continue;
        KnapsackTree_DFS(v, u);
        sumVol[u] += sumVol[v];
        for(int j = 0; j <= V; ++j) {
            dpu[cur][j] = KnapsackTree_CurInitValue(dpu[pre], j); 
            for(int k = 0; k <= j && k <= sumVol[v]; ++k) {
                dpu[cur][j] = KnapsackTree_Opt(dpu[cur][j], dpu[pre][j-k], dp[v][k]);
            }
        }
        swap(pre, cur);
    }
    KnapsackTree_Post(u, fat, dpu[pre]);
}

//////////////////////////////////////////////////////////////////////////////
///////////////////////////////// 树上背包模板 ////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

int main()
{
    int w;
    cin >> n >> w;
    V = n;
    for (int i = 1; i <= n; ++i) {
        items[i].vol = 1;
        cin >> items[i].wei;
    }
    items[1].edge = KnapsackTree_InfValue();
    for (int i = 1; i <= n - 1; ++i) {
        int x, y;
        cin >> x >> y;
        child[x].push_back(i+1);
        items[i+1].edge = y;
    }
    KnapsackTree_DFS(1, 0);
    cout << KnapsackTree_GetAnswer(1, w) << endl;
    return 0;
}