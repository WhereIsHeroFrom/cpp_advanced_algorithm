#include <iostream>
using namespace std;

#define maxn 10
#define maxc 11
#define maxv 305
#define inf ""
#define init ""
#define vType string

struct Item {
    int cnt;
    int w[maxc];
    vType v[maxc];
};

vType opt(vType a, vType b) {
    if(a == inf) return b;
    if(b == inf) return a;
    if(a.size() == b.size()) {
        return a > b ? a : b;
    }
    return a.size() > b.size() ? a : b;
}

void KnapsackGroup(int n, int V, Item items[], vType dp[maxn][maxv]) {
    for(int i = 1; i <= V; ++i) {
        dp[0][i] = inf;
    }
    dp[0][0] = init;

    for(int i = 1; i <= n; ++i) {
        for(int j = 0; j <= V; ++j) {
            // 前i组物品凑出容量为j的最优价值
            dp[i][j] = dp[i-1][j];
            for(int k = 0; k < items[i].cnt; ++k) {
                if(j >= items[i].w[k]) {
                    vType tmp = dp[i-1][j - items[i].w[k]] + items[i].v[k];
                    dp[i][j] = opt( dp[i][j], tmp );
                }
            }
        }
    }
}


Item items[maxn];
vType dp[maxn][maxv];

int tbl[] = {
    -1, 2, 5, 5, 4, 5, 6, 3, 7, 6
};

int main() {
    int n, V;
    n = 9;
    V = 300;
    for(int i = 1; i <= n; ++i) {
        items[i].cnt = 10;
        int num = n + 1 - i;
        for(int j = 0; j < items[i].cnt; ++j) {
            items[i].w[j] = tbl[num] * (j + 1);
            // num = 8 , j = 3
            // items[i].v[j] = "8888";
            items[i].v[j] = to_string(num);
            if(j > 0) {
                items[i].v[j] += items[i].v[j-1];
            }
        }
    }
    KnapsackGroup(n, V, items, dp);
    vType ret = inf;
    for(int i = 0; i <= V; ++i) {
        ret = opt(ret, dp[n][i]);
    }
    cout << ret << endl;
    return 0;
}