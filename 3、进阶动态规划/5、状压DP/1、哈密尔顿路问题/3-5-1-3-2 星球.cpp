#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;


///////////////////////////////////////////////////
///////////////״ѹDP - ���ܶ���·ģ��///////////////
///////////////////////////////////////////////////

/*
1����һ����ȷ�� maxn �Ĵ�С
2���ڶ�����ȷ�� type ������
3����������ȷ�� dptype ����
4�����Ĳ���ʵ�������������뺯����dis_func
5�����岽������ HamiltonDP_Solve
*/

#define maxn 18
#define type double
#define dptype DPType::MIN
typedef type(*dis_func) (int a, int b);

enum DPType {
    MIN = 0,  // ����Сֵ
    MAX = 1,  // �����ֵ
    NUM = 2,  // �󷽰���
};

// dp[i][j] etc, i = 1101, j = 2
// �����Ѿ�������0��2��3�������㣬����һ��������2�����Ž�
type dp[1<<maxn][maxn];
// dis[i][j] ����� i->j �ľ���
type dis[maxn][maxn];

// �̶�ģ��
type HamiltonDP_opt( type a, type b, type c) {
    if (dptype == DPType::MIN) {
        return min(a, b + c);
    }else if(dptype == DPType::MAX) {
        return max(a, b + c);
    }else if(dptype == DPType::NUM) {
        return a + b * c;
    }
}

// �̶�ģ�壬������Ͳ��� long long��������Ҫ�޸�
type HamiltonDP_ValueInf() {
    if (dptype == DPType::MIN) {
        return 1000000000;
    }else if(dptype == DPType::MAX) {
        return -1000000000;
    }else if(dptype == DPType::NUM) {
        return 0;
    }
}

// �̶�ģ��
type HamiltonDP_ValueInit() {
    if (dptype == DPType::MIN) {
        return 0;
    }else if(dptype == DPType::MAX) {
        return 0;
    }else if(dptype == DPType::NUM) {
        return 1;
    }
}

// �̶�ģ�壬�������������ľ���
// dis_func ����Ҫ����ʵ�����
void HamiltonDP_initEdges(int n, dis_func df) {
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < n; ++j) {
            dis[i][j] = df(i, j);
        }
    }
}

// �̶�ģ�壬��ʼ������״̬
// �������� [0, n)
void HamiltonDP_Init(int n, dis_func df) {
    memset(dp, -1, sizeof(dp));
    HamiltonDP_initEdges(n, df);
}

// �̶�ģ�壬�󲿷��������Ҫ�޸�
// state �������Ƶ�1101 ���� 0��2��3 ���������Ѿ�������
//     n ���ܹ����ٸ�����
//   pre ��·���ϵ���һ������
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
///////////////״ѹDP - ���ܶ���·ģ��///////////////
///////////////////////////////////////////////////

int x[maxn], y[maxn], z[maxn], w[maxn+1];


type d(int a, int b) {
    int ans = (x[a]-x[b])*(x[a]-x[b])
    + (y[a]-y[b])*(y[a]-y[b])
    + (z[a]-z[b])*(z[a]-z[b]);
    return sqrt(ans + 0.0) * w[b];
}

int main() {
    int n;
    cin >> n;
    for(int i = 0; i < n; ++i) {
        cin >> x[i] >> y[i] >> z[i] >> w[i];
    }
    printf("%.2lf\n", HamiltonDP_Solve(d, n, false, -1));
    return 0;
}