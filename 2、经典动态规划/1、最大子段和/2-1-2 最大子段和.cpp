#include <iostream>
using namespace std;

#define maxn 200010
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
    return ans;
}

type dp[maxn];
type a[maxn];

int main() {
    int n;
    cin >> n;
    for(int i = 1; i <= n; ++i) {
        cin >> a[i];
    }
    cout << getMSS(n, a, dp) << endl;
    return 0;
}