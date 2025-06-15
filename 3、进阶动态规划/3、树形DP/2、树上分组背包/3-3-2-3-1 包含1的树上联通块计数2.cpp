#include <iostream>
#include <vector>
using namespace std;

//////////////////////////////////////////////////////////////////////////////
///////////////////////////////// ���ϱ���ģ�� ////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

#define mod 998244353

// ������ݵ���������
#define type long long
// ��Ʒ���ܸ��������Ķ��������
#define maxn 2010
// �ܹ�����ѡ����������
#define maxv 2010
// ��Ʒ�ṹ��
struct Item {
    int vol;    // ÿ����Ʒ������  
    int wei;    // ÿ����Ʒ��Ȩֵ
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
    return 1;
}

// �Ƿ�״ֵ̬�������ֵʱѡ��С������Сֵʱѡ���
// ��Ҫ������Ŀ��������޸�
type KnapsackTree_InfValue() {
    return 0;
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
    return (curVal + preVal * itemWei % mod) % mod;
}

// ��һ���ǳ��ؼ���Ŀ���ǰ� �������� dpu �м���������ݣ�ת�Ƶ� dp ��
// dpu ����ʱ���ݣ��ݹ������������
// dp �ǳ־û����ݣ��ݹ����һֱ����
void KnapsackTree_Post(int u, type dpu[maxv]) {
    for(int j = 0; j <= V; ++j) {
        // ��ǰ�����Ʒ��ѡ
        dp[u][j] = (j==0) ? KnapsackTree_InitValue(u) : KnapsackTree_InfValue();
        // ��ǰ�����Ʒѡ
        if(j >= items[u].vol)
            dp[u][j] = KnapsackTree_Opt(dp[u][j], dpu[j-items[u].vol], items[u].wei);
    }
}

// ��ȡ���Ž⣬������ĿҪ��ִ���߼�
type KnapsackTree_GetAnswer(int root) {
    return dp[root][V];
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
    KnapsackTree_Post(u, dpu[pre]);
}

//////////////////////////////////////////////////////////////////////////////
///////////////////////////////// ���ϱ���ģ�� ////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

int main()
{
    cin >> n >> V;
    for (int i = 1; i <= n; ++i) {
        items[i].vol = items[i].wei = 1;
    }
    for (int i = 0; i < n - 1; ++i) {
        int x, y;
        cin >> x >> y;
        child[x].push_back(y);
        child[y].push_back(x);
    }
    KnapsackTree_DFS(1, 0);
    cout << KnapsackTree_GetAnswer(1) << endl;
    return 0;
}