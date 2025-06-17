#include <iostream>
using namespace std;

///////////////////////////////////////////////////
/////////////״ѹDP - ��Լ����01����ģ��/////////////
///////////////////////////////////////////////////
//// ���е�1�������ڣ��󷽰��������ֵ����Сֵ�ȵ� ////
/*
1���󷽰�����ȡģ������ dptype ѡ�� DPType::MOD
2������1��GridType����EMPTY��������ZERO
3������ (Mask::UP|Mask::LEFT) ����Լ������ ONE
*/

#define maxn 13
#define maxm 13
#define type long long
#define dptype DPType::MOD
#define mod 100000000
#define MaskType (Mask::UP|Mask::LEFT)
int n, m;
type dp[2][1<<maxm];
int grid[maxn][maxm];

enum DPType {
    MIN = 0,  // ����Сֵ
    MAX = 1,  // �����ֵ
    NUM = 2,  // �󷽰���
    MOD = 3,  // �󷽰�����ȡģ
};

enum GridType {
    EMPTY = -1, 
    ZERO  = 0,
    ONE   = 1,
};

enum Mask {
    UP = (1<<0),
    LEFT = (1<<1),
};

// �̶�ģ��
type MatrixPutDP_opt( type cur, type pre, type curOneCount) {
    if (dptype == DPType::MIN) {
        return min(cur, pre + curOneCount);
    }else if(dptype == DPType::MAX) {
        return max(cur, pre + curOneCount);
    }else if(dptype == DPType::NUM) {
        return cur + pre;
    }else {
        return (cur + pre) % mod;
    }
}

// �̶�ģ�壬������Ͳ��� long long��������Ҫ�޸�
type MatrixPutDP_ValueInf() {
    if (dptype == DPType::MIN) {
        return 1000000000;
    }else if(dptype == DPType::MAX) {
        return -1000000000;
    }else if(dptype == DPType::NUM) {
        return 0;
    }else if(dptype == DPType::MOD) {
        return 0;
    }
}

// �̶�ģ��
type MatrixPutDP_ValueInit() {
    if (dptype == DPType::MIN) {
        return 0;
    }else if(dptype == DPType::MAX) {
        return 0;
    }else if(dptype == DPType::NUM) {
        return 1;
    }else if(dptype == DPType::MOD) {
        return 1;
    }
}

// ���� LEFT �� UP �����жϣ����������ڵ� ONE
bool MatrixPutDP_canPut(int prestate, int curstate, int r, int c) {
    if( grid[r][c] != GridType::EMPTY ) {
        return false;
    }
    if(MaskType & Mask::UP) {
        if(r > 0 && grid[r-1][c] == GridType::ONE) {
            return false;
        }
        if(prestate & 1) {
            return false;
        }
    }
    if(MaskType & Mask::LEFT) {
        if(c > 0 && grid[r][c-1] == GridType::ONE) {
            return false;
        }
        if( (curstate>>1) & 1 ) {
            return false;
        }
    }
    return true;
}


void MatrixPutDP_Dfs(int col, int maxcol, 
    int row, int pre, int prestate, 
    int cur, int curstate, int cnt) {
    
    if(col == maxcol) {
        dp[cur][curstate] = MatrixPutDP_opt( dp[cur][curstate], dp[pre][prestate], cnt);
        return ;
    }
    // ö��ǰһ�зźͲ���
    for(int i = 0; i < 2; ++i) {
        int pres = prestate << 1 | i;
        // ö����һ�зźͲ���
        for(int j = 0; j < 2; ++j) {
            int curs = (curstate << 1 | j);
            if(j == GridType::ONE) {
                if( !MatrixPutDP_canPut(pres, curs, row, col) ) {
                    continue;
                }
            }
            MatrixPutDP_Dfs(col+1, maxcol, row, pre, pres, cur, curs, cnt + j);
        }
    }
}

type MatrixPutDP_Solve(int n, int m) {
    // 1����ʼ״̬
    int pre = 0, cur = 1;
    for(int i = 0; i < (1<<m); ++i) {
        dp[pre][i] = MatrixPutDP_ValueInf();
    }
    dp[pre][0] = MatrixPutDP_ValueInit();
    // 2��״̬ת��
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < (1<<m); ++j) {
            dp[cur][j] = MatrixPutDP_ValueInf();
        }
        MatrixPutDP_Dfs(0, m, i, pre, 0, cur, 0, 0);
        swap(pre, cur);
    }
    // 3���ܽ�״̬
    type ans = MatrixPutDP_ValueInf();
    for(int j = 0; j < (1<<m); ++j) {
        ans = MatrixPutDP_opt(ans, dp[pre][j], MatrixPutDP_ValueInit());
    }
    return ans;
}

///////////////////////////////////////////////////
/////////////״ѹDP - ��Լ����01����ģ��/////////////
///////////////////////////////////////////////////

int main() {
    cin >> n;
    m = n;
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < m; ++j) {
            int x;
            cin >> x;
            if(x == 1) grid[i][j] = EMPTY;
            else grid[i][j] = ZERO;
        }
    }
    cout << MatrixPutDP_Solve(n, m) << endl;
    return 0;
}