#include <iostream>
using namespace std;

#define maxn 2010
#define type long long
#define inf -1000000000000000000ll

type getMSS(int n, type a[], type dp[]) {
    // dp[i] 代表以第 i 个数结尾的最大子段和
    type ans = inf;
    dp[0] = 0;
    for(int i = 1; i <= n; ++i) {
        dp[i] = a[i] + max(dp[i-1], (type)0);
        ans = max(ans, dp[i]);
    }
    // 转换成前 i 个元素的最大子段和
    dp[0] = inf;
    for(int i = 1; i <= n; ++i) {
        dp[i] = max(dp[i], dp[i-1]);
    }
    return ans;
}

// dp[i][j] 代表从第i个元素
// 开始的数组的第j个元素结尾的最大子段和
type dp[maxn][maxn];
type a[maxn];

int main() {
    int n;
    cin >> n;
    for(int i = 1; i <= n; ++i) {
        cin >> a[i];
    }
    // getMSS(n,   &a[0], dp[1]);
    // getMSS(n-1, &a[1], dp[2]);
    // getMSS(n-2, &a[2], dp[3]);
    for(int i = 1; i <= n; ++i) {
        getMSS(n-i+1, &a[i-1], dp[i]);
    }
    int t;
    cin >> t;
    while(t--) {
        int l, r;
        cin >> l >> r;
        cout << dp[l][r - l + 1] << endl;
    }


    return 0;
}