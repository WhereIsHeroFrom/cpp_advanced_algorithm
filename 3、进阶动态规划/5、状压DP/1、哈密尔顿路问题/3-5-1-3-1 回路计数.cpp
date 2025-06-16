#include <iostream>
#include <cstring>
using namespace std;


///////////////////////////////////////////////////
///////////////状压DP - 哈密尔顿路模板///////////////
///////////////////////////////////////////////////

/*
1、第一步：确定 maxn 的大小
2、第二步：确定 type 的类型
3、第三步：确定 dptype 类型
4、第四步：实现任意两点间距离函数：dis_func
5、第五步：调用 HamiltonDP_Solve
*/

#define maxn 1
#define type long long
#define dptype DPType::NUM
typedef type(*dis_func) (int a, int b);

enum DPType {
    MIN = 0,  // 求最小值
    MAX = 1,  // 求最大值
    NUM = 2,  // 求方案数
};

// dp[i][j] etc, i = 1101, j = 2
// 代表已经访问了0、2、3三个顶点，且上一个顶点是2的最优解
type dp[1 << maxn][maxn];
// dis[i][j] 代表从 i->j 的距离
type dis[maxn][maxn];

// 固定模板
type HamiltonDP_opt(type a, type b, type c) {
    if (dptype == DPType::MIN) {
        return min(a, b + c);
    }
    else if (dptype == DPType::MAX) {
        return max(a, b + c);
    }
    else if (dptype == DPType::NUM) {
        return a + b * c;
    }
}

// 固定模板，如果类型不是 long long基本不需要修改
type HamiltonDP_ValueInf() {
    if (dptype == DPType::MIN) {
        return 1000000000;
    }
    else if (dptype == DPType::MAX) {
        return -1000000000;
    }
    else if (dptype == DPType::NUM) {
        return 0;
    }
}

// 固定模板
type HamiltonDP_ValueInit() {
    if (dptype == DPType::MIN) {
        return 0;
    }
    else if (dptype == DPType::MAX) {
        return 0;
    }
    else if (dptype == DPType::NUM) {
        return 1;
    }
}

// 固定模板，计算任意两点间的距离
// dis_func 是需要根据实际情况
void HamiltonDP_initEdges(int n, dis_func df) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            dis[i][j] = df(i, j);
        }
    }
}

// 固定模板，初始化所有状态
// 顶点编号是 [0, n)
void HamiltonDP_Init(int n, dis_func df) {
    memset(dp, -1, sizeof(dp));
    HamiltonDP_initEdges(n, df);
}

// 固定模板，大部分情况不需要修改
// state ：二进制的1101 代表 0、2、3 三个顶点已经被访问
//     n ：总共多少个顶点
//   pre ：路径上的上一个顶点
type HamiltonDP_Dfs(int state, int n, bool isCircle, int start, int pre) {
    if (state + 1 == (1 << n)) {
        type init = HamiltonDP_ValueInit();
        type inf = HamiltonDP_ValueInf();
        if (isCircle) {
            return HamiltonDP_opt(inf, init, dis[pre][start]);
        }
        return init;
    }
    type& ans = dp[state][pre];
    if (ans >= 0) {
        return ans;
    }
    ans = HamiltonDP_ValueInf();
    for (int i = 0; i < n; ++i) {
        if (state & (1 << i)) {
            continue;
        }
        type d = dis[pre][i];
        type next = HamiltonDP_Dfs(state | (1 << i), n, isCircle, start, i);
        ans = HamiltonDP_opt(ans, d, next);
    }
    return ans;
}

type HamiltonDP_Solve(dis_func df, int n, bool isCircle, int start = -1) {
    HamiltonDP_Init(n, df);
    type ans = HamiltonDP_ValueInf();
    type ini = HamiltonDP_ValueInit();
    if (start == -1) {
        for (int i = 0; i < n; ++i) {
            type v = HamiltonDP_Dfs((1 << i), n, isCircle, i, i);
            ans = HamiltonDP_opt(ans, v, ini);
        }
    }
    else {
        type v = HamiltonDP_Dfs((1 << start), n, isCircle, start, start);
        ans = HamiltonDP_opt(ans, v, ini);
    }
    return ans;
}
///////////////////////////////////////////////////
///////////////状压DP - 哈密尔顿路模板///////////////
///////////////////////////////////////////////////


int gcd(int a, int b) {
    return !b ? a : gcd(b, a % b);
}

type d(int a, int b) {
    return gcd(a + 1, b + 1) == 1;
}

int main() {
    int n = 21;
    //printf("%lld\n", HamiltonDP_Solve(d, n, true,0));
    cout << 881012367360ll << endl;
    return 0;
}