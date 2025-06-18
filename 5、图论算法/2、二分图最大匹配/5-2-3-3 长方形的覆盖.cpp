#include <iostream>
#include <cstring>
#include <vector>

using namespace std;

/////////////////////////////////////////////////////////////
//////////////////����ͼ���ƥ��ģ��(�ڽӱ�) //////////////////
/////////////////////////////////////////////////////////////
// ���㷶Χ  ��ߵĵ�[1, n]���ұߵĵ�[1, m]

#define maxn 1010
#define maxm 1010

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


char c[25][25];
int dir[4][2] = {
    {0, 1}, {1, 0}, {0, -1}, {-1, 0}
};

int main() {
    int n;
    cin >> n;
    for(int i = 0; i < n; ++i) {
        cin >> c[i];
    }
    Hungarian_Initialize(n*n, n*n);
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < n; ++j) {
            if( (i+j)&1 ) {
                for(int k = 0; k < 4; ++k) {
                    int di = i + dir[k][0];
                    int dj = j + dir[k][1];
                    if(di < 0 || di == n || dj < 0 || dj == n) {
                        continue;
                    }
                    if(c[i][j] == '1' || c[di][dj] == '1') {
                        continue;
                    }
                    Hungarian_AddEdge( i*n+j+1, di*n+dj+1 );
                }
            }
        }
    }
    cout << Hungarian_GetMaxMatch() << endl;
}
