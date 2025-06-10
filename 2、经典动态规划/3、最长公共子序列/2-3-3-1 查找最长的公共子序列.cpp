#include <iostream>
#include <cstring>
using namespace std;

#define maxn 1010
#define maxm 1010
#define type char

int getLCS(int n, type a[], int m, type b[], 
           int dp[maxn][maxm], char path[maxn][maxm]
          ) {
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (a[i] == b[j]) {
                dp[i][j] = dp[i-1][j-1] + 1;
                path[i][j] = 0;
            }else if(dp[i-1][j] > dp[i][j-1]) {
                dp[i][j] = 0;
                path[i][j] = 1;
            }else {
                dp[i][j] = 0;
                path[i][j] = 2;
            }
        }
    }
    return dp[n][m];
}

void constructLCS(int x, type a[], int y, type b[], 
           char path[maxn][maxm], type ans[], int& ansSize
        ) {
    int i = x, j = y;
    ansSize = 0;
    while(i && j) {
        if( path[i][j] == 0 ) {
            ans[ansSize++] = a[i];
            --i, --j;
        }else if(path[i][j] == 1) {
            --i;
        }else if(path[i][j] == 2) {
            --j;
        }
    }
    for(int i = 0; i < ansSize/2; ++i) {
        swap(ans[i], ans[ansSize-1-i]);
    }
}

int dp[maxn][maxm];
char path[maxn][maxm];

char a[maxn], b[maxm];
char ans[maxn];
int ansSize;

int main() {
    cin >> &a[1];
    cin >> &b[1];
    int n = strlen(&a[1]);
    int m = strlen(&b[1]);
    getLCS(n, a, m, b, dp, path);
    int x = 1, y = 1;
    for(int i = 1; i <= n; ++i) {
        for(int j = 1; j <= m; ++j) {
            if(dp[i][j] > dp[x][y]) {
                x = i;
                y = j;
            }
        }
    }
    constructLCS(x, a, y, b, path, ans, ansSize);
    for(int i = 0; i < ansSize; ++i) {
        cout << ans[i];
    }
    cout << endl;
    return 0;
}