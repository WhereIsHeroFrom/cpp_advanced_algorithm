#include <iostream>
using namespace std;

#define maxn 110

int mat[maxn][maxn];
int dp[maxn][maxn];

int main() {
    int n;
    cin >> n;
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j <= i; ++j) {
            cin >> mat[i][j];
        }
    }
    dp[0][0] = mat[0][0];
    for(int i = 0; i < n; ++i) {
        dp[i][i] = mat[i][i] + dp[i-1][i-1];
        dp[i][0] = mat[i][0] + dp[i-1][0];
        for(int j = 1; j < i; ++j) {
            dp[i][j] = mat[i][j] + max(dp[i-1][j-1], dp[i-1][j]);
        }
    }
    int ans;
    if(n % 2) {
        ans = dp[n-1][n/2];
    }else {
        ans = max(dp[n-1][n/2-1], dp[n-1][n/2]);
    }

    cout << ans << endl;

    return 0;
}