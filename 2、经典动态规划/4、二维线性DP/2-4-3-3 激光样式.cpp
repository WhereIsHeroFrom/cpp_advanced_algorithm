#include <iostream>
using namespace std;

int dp[31][2];
// dp[i][0] 代表第i个激光器关闭的方案数
// dp[i][1] 代表第i个激光器打开的方案数
// dp[30][0] + dp[30][1];

int main() {
    dp[1][0] = 1;
    dp[1][1] = 1;
    for(int i = 2; i <= 30; ++i) {
        dp[i][0] = dp[i-1][0] + dp[i-1][1];
        dp[i][1] = dp[i-1][0];
    }
    cout << dp[30][0] + dp[30][1] << endl;
    return 0;
}