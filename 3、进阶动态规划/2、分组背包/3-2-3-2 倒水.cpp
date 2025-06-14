#include <iostream>
using namespace std;

/*
1���Ƿ�״ֵ̬Ҫ���÷ǳ�С
2�������� long long
3��ÿ����Ʒ����ѡ��ǡ��һ��
*/

#define maxn 1010
#define maxc 3
#define maxv 1010
#define inf -1000000000000000000ll
#define init 0
#define vType long long

struct Item {
    int cnt;
    int w[maxc];
    vType v[maxc];
};

vType opt(vType a, vType b) {
    if(a == inf) return b;
    if(b == inf) return a;
    return a > b ? a : b;
}

void KnapsackGroup(int n, int V, Item items[], vType dp[maxn][maxv]) {
    for(int i = 1; i <= V; ++i) {
        dp[0][i] = inf;
    }
    dp[0][0] = init;

    for(int i = 1; i <= n; ++i) {
        for(int j = 0; j <= V; ++j) {
            // ǰi����Ʒ�ճ�����Ϊj�����ż�ֵ
            // ģ����΢��һ�£���i����Ʒ������ѡ������
            dp[i][j] = inf;
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


int main() {
    int n, V;
    cin >> n >> V;
    for(int i = 1; i <= n; ++i) {
        int a, b, c, d, e;
        cin >> a >> b >> c >> d >> e;
        items[i].cnt = 3;

        items[i].w[0] = 0;
        items[i].v[0] = e;

        items[i].w[1] = a;
        items[i].v[1] = b;

        items[i].w[2] = c;
        items[i].v[2] = d;
    }
    KnapsackGroup(n, V, items, dp);
    vType ret = inf;
    for(int i = 0; i <= V; ++i) {
        ret = opt(ret, dp[n][i]);
    }
    cout << ret << endl;
    return 0;
}



