#include <iostream>
#include <vector>
using namespace std;

// dp[i][j] ������ i ��Ϊ����㣬��Ҫ�õ� j ���������С����
// KnapsackTree_GetAnswer ���� w ����
//////////////////////////////////////////////////////////////////////////////
///////////////////////////////// ���ϱ���ģ�� ////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

// ������ݵ���������
#define type int
// ��Ʒ���ܸ��������Ķ��������
#define maxn 5010
// �ܹ�����ѡ����������
#define maxv 5010
// ��Ʒ�ṹ��
struct Item {
    int vol;    // ÿ����Ʒ������  
    int wei;    // ÿ����Ʒ��Ȩֵ
    int edge;   // ǰ���Ȩֵ
}items[maxn];
// ���ι�ϵ��˫��ͼ��
vector<int> child[maxn];
// dp[i][j] ������iΪ���������У�ѡ�������ܺ�Ϊj����Ʒ���õ������ż�ֵ
type dp[maxn][maxv];
// sumVol[i] ���������ӽ���������
int sumVol[maxn];
// n����Ʒ���������ΪV
int n, V;

// ��ʼ״ֵ̬
// ��Ҫ������Ŀ��������޸�
type KnapsackTree_InitValue(int u) {
    return 0;
}

// �Ƿ�״ֵ̬�������ֵʱѡ��С������Сֵʱѡ���
// ��Ҫ������Ŀ��������޸�
type KnapsackTree_InfValue() {
    return 1000000000;
}

// ÿ��״̬ת�ƿ�ʼʱ��״̬�ĳ�ʼֵ
// ����Ǽӱ�ģ�壬��ֱ�ӷ��� KnapsackTree_InfValue
// �����ɾ��ģ�壬����Ҫ���� v ��ֵ�����ж�
type KnapsackTree_CurInitValue(type dpu[maxv], int v) {
    return KnapsackTree_InfValue();
}

// ״̬ת�Ʒ���
// ��Ҫ������Ŀ��������޸�
type KnapsackTree_Opt(type curVal, type preVal, type itemWei) {
    return min(curVal, preVal + itemWei);
}

// ��һ���ǳ��ؼ���Ŀ���ǰ� �������� dpu �м���������ݣ�ת�Ƶ� dp ��
// dpu ����ʱ���ݣ��ݹ������������
// dp �ǳ־û����ݣ��ݹ����һֱ����
void KnapsackTree_Post(int u, int fat, type dpu[maxv]) {
    for(int j = 0; j <= V; ++j) {
        dp[u][j] = dpu[j];
    }
    dp[u][ sumVol[u] ]   = KnapsackTree_Opt(dp[u][ sumVol[u] ], items[u].edge, 0);
    dp[u][ sumVol[u]-1 ] = KnapsackTree_Opt(dp[u][ sumVol[u]-1 ], items[u].wei, 0);
}

// ��ȡ���Ž⣬������ĿҪ��ִ���߼�
type KnapsackTree_GetAnswer(int root, int w) {
    type ans = KnapsackTree_InfValue();
    for(int i = n; i >= 0; --i) {
        if(dp[root][i] <= w) {
            return i;
        }
    }
    return 0;
}

// ģ����룬�������ø�
int KnapsackTree_Init(type dpu[2][maxv], int u) {
    int pre = 0;
    dpu[pre][0] = KnapsackTree_InitValue(u);
    for(int i = 1; i <= V; ++i) {
        dpu[pre][i] = KnapsackTree_InfValue();
    }
    return pre;
}

// ģ����룬�������ø�
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
///////////////////////////////// ���ϱ���ģ�� ////////////////////////////////
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