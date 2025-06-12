#include <iostream>
using namespace std;

#define maxn 101
#define maxc 10
#define maxv 1001
#define inf -1
#define init 0
#define vType int

vType opt(int a, int b) {
    if(a == inf) return b;
    if(b == inf) return a;
    return a > b ? a : b;
}

void Knapsack01(int n, int V, int w[maxn*maxc], vType v[maxn*maxc], vType dp[maxv]) {
    // 1、初始化
    for(int i = 1; i <= V; ++i) {
        dp[i] = inf;
    }
    dp[0] = init;
    // 2、状态转移
    for(int i = 1; i <= n; ++i) {
        for(int j = V; j >= w[i]; --j) {
            dp[j] = opt(dp[j], dp[j-w[i]] + v[i]);
        }
    }
}

void KnapsackMultiple(int n, int V, int w[maxn], vType v[maxn], int c[maxn], vType dp[maxv]) {
    int m = 0;  // 拆分以后，物品数量就是 m 了，不再是 n
    int nw[maxn * maxc];
    vType nv[maxn * maxc];
    for(int i = 1; i <= n; ++i) {
        int k = 1;
        while(k < c[i]) {
            ++m;
            nw[m] = k*w[i];
            nv[m] = k*v[i];
            c[i] -= k;
            k *= 2;
        }
        if(c[i]) {
            ++m;
            nw[m] = c[i]*w[i];
            nv[m] = c[i]*v[i];
        }
    }
    Knapsack01(m, V, nw, nv, dp);
}

int w[maxn], c[maxn];
vType v[maxn];
vType dp[maxv];

int main() {
    int V, n, c0, d0;
    cin >> V >> n >> c0 >> d0;
    w[1] = c0;
    c[1] = V/c0;
    v[1] = d0;
    for(int i = 2; i <= n + 1; ++i) {
        int ai, bi, ci, di;
        cin >> ai >> bi >> ci >> di;
        w[i] = ci;
        c[i] = ai / bi;
        v[i] = di;
    }
    KnapsackMultiple(n+1, V, w, v, c, dp);
    vType ret = inf;
    for(int i = 0; i <= V; ++i) {
        ret = opt(ret, dp[i]);
    }
    cout << ret << endl;
    return 0;
}

