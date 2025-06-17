#include <iostream>
using namespace std;

///////////////////////////////////////////////////
/////////////状压DP - 带约束的01矩阵模板/////////////
///////////////////////////////////////////////////


#define maxn 226
#define maxm 16
#define type long long
#define dptype DPType::MOD
#define mod 10007
#define MaskType (Mask::UP|Mask::LEFT|Mask::RIGHT|Mask::DOWN)
int n, m;
type dp[2][1<<maxm];
int grid[maxn][maxm];

enum DPType {
    MIN = 0,  // 求最小值
    MAX = 1,  // 求最大值
    NUM = 2,  // 求方案数
    MOD = 3,  // 求方案数并取模
};

enum GridType {
    EMPTY = -1, 
    ZERO  = 0,
    ONE   = 1,
};

enum Mask {
    UP = (1<<0),
    LEFT = (1<<1),
    DOWN = (1<<2),
    RIGHT = (1<<3),
};

// 固定模板
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

// 固定模板，如果类型不是 long long基本不需要修改
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

// 固定模板
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

// 根据 LEFT 和 UP 进行判断，不能有相邻的 ONE
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
    if(MaskType & Mask::DOWN) {
        if(r + 1 < n && grid[r+1][c] == GridType::ONE) {
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
    if(MaskType & Mask::RIGHT) {
        if(c + 1 < m && grid[r][c+1] == GridType::ONE) {
            return false;
        }
    }

    return true;
}

void MatrixPutDP_Dfs(int col, int maxcol, 
    int row, int pre, int prestate, 
    int cur, int curstate, int cnt) {
    
    if(col == maxcol) {
        dp[cur][curstate] = MatrixPutDP_opt( dp[pre][prestate], dp[cur][curstate], cnt);
        return ;
    }
    // 枚举前一行放和不放
    for(int i = 0; i < 2; ++i) {
        int pres = prestate << 1 | i;
        // 枚举这一行放和不放
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
    // 1、初始状态
    int pre = 0, cur = 1;
    for(int i = 0; i < (1<<m); ++i) {
        dp[pre][i] = MatrixPutDP_ValueInf();
    }
    dp[pre][0] = MatrixPutDP_ValueInit();
    // 2、状态转移
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < (1<<m); ++j) {
            dp[cur][j] = MatrixPutDP_ValueInf();
        }
        MatrixPutDP_Dfs(0, m, i, pre, 0, cur, 0, 0);
        swap(pre, cur);
    }
    // 3、总结状态
    type ans = MatrixPutDP_ValueInf();
    for(int j = 0; j < (1<<m); ++j) {
        ans = MatrixPutDP_opt(ans, dp[pre][j], MatrixPutDP_ValueInit());
    }
    return ans;
}

///////////////////////////////////////////////////
/////////////状压DP - 带约束的01矩阵模板/////////////
///////////////////////////////////////////////////

char mat[maxm][maxm];

int main() {
    cin >> n >> m;
    for(int i = 0; i < n; ++i) {
        cin >> mat[i];
    }
    if(n > m) {
        for(int i = 0; i < n; ++i) {
            for(int j = 0; j < m; ++j) {
                if(mat[i][j] == '0') grid[i][j] = GridType::ZERO;
                else if(mat[i][j] == '1') grid[i][j] = GridType::ONE;
                else grid[i][j] = GridType::EMPTY;
            }
        }
    }else {
        for(int i = 0; i < n; ++i) {
            for(int j = 0; j < m; ++j) {
                if(mat[i][j] == '0') grid[j][i] = GridType::ZERO;
                else if(mat[i][j] == '1') grid[j][i] = GridType::ONE;
                else grid[j][i] = GridType::EMPTY;
            }
        }
        swap(n, m);
    }
    cout << MatrixPutDP_Solve(n, m) << endl;
    return 0;
}