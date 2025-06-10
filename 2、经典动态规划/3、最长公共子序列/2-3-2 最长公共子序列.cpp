#include <iostream>
using namespace std;

#define maxn 1010
#define maxm 1010
#define type int

int getLCS(int n, type a[], int m, type b[],
    int dp[maxn][maxm], char path[maxn][maxm]) {
        // dp[i][j] 代表 a[1:i] 和 b[1:j] 这两个数组的最长公共子序列的长度
        // return dp[n][m];
    for(int i = 1; i <= n; ++i) {
        for(int j = 1; j <= m; ++j) {
            if(a[i] == b[j]) {
                dp[i][j] = dp[i-1][j-1] + 1;
                path[i][j] = 0;
            }else if( dp[i-1][j] > dp[i][j-1] ) {
                dp[i][j] = dp[i-1][j];
                path[i][j] = 1;
            }else {
                dp[i][j] = dp[i][j-1];
                path[i][j] = 2;
            }
        }
    }
    return dp[n][m];
}

int dp[maxn][maxm];
char path[maxn][maxm];
int a[maxn], b[maxm];

int main() {
    int n, m;
    cin >> n >> m;
    for(int i = 1; i <= n; ++i) {
        cin >> a[i];
    }
    for(int i = 1; i <= m; ++i) {
        cin >> b[i];
    }
    cout << getLCS(n, a, m, b, dp, path) << endl;
    return 0;
}