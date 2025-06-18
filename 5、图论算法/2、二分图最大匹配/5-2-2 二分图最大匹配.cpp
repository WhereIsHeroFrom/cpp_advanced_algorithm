#include <iostream>
#include <cstring>
#include <vector>

using namespace std;

/////////////////////////////////////////////////////////////
//////////////////����ͼ���ƥ��ģ��(�ڽӱ�) //////////////////
/////////////////////////////////////////////////////////////
// ���㷶Χ  ��ߵĵ�[1, n]���ұߵĵ�[1, m]

#define maxn 510
#define maxm 510

vector<int> adj[maxn];     // �ڽӱ�
int pre[maxm];             // �������㷨������·ʱ��pre����
bool visit[maxm];          // �������㷨������·ʱ��visit����
int n, m;                  // ���ҵ㼯����Ŀ

// ��ʼ������ͼ
void Hungarian_Initialize(int n_, int m_) {
    n = n_;
    m = m_;
    memset(pre, -1, sizeof(pre));
    for (int i = 1; i <= n; ++i) {
        adj[i].clear();
    }
}

void Hungarian_AddEdge(int u, int v) {
    adj[u].push_back(v);
}

bool Hungarian_findMatch(int u) {
    for (int i = 0; i < adj[u].size(); ++i) {
        int v = adj[u][i];
        if (!visit[v]) {
            visit[v] = true;
            int vpre = pre[v];
            pre[v] = u;
            if (vpre == -1 || Hungarian_findMatch(vpre)) {
                return true;
            }
            pre[v] = vpre;
        }
    }
    return false;
}

// ��ȡ���ƥ����
int Hungarian_GetMaxMatch() {
    int cnt = 0;
    for (int i = 1; i <= n; ++i) {
        memset(visit, false, sizeof(visit));
        if (Hungarian_findMatch(i)) {
            ++cnt;
        }
    }
    return cnt;
}
/////////////////////////////////////////////////////////////
//////////////////����ͼ���ƥ��ģ��(�ڽӱ�) //////////////////
/////////////////////////////////////////////////////////////

int main() {
    int n, m, k;
    cin >> n >> m >> k;
    Hungarian_Initialize(n, m);
    for(int i = 0; i < k; ++i) {
        int x, y;
        cin >> x >> y;
        Hungarian_AddEdge(x, y);
    }
    cout << Hungarian_GetMaxMatch() << endl;
}    
