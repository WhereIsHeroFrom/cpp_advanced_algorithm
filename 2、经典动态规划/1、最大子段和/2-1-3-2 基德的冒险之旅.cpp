#include <iostream>
using namespace std;

#define maxn 100010
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

void swap(int n, type a[]) {
    for(int i = 1; i <= n/2; ++i) {
        swap(a[i], a[n+1-i]);
    }
}

type dppre[maxn], dppost[maxn];
type a[maxn];





int main()
{
    int n, k;
    cin >> n >> k;
    for(int i = 1; i <= n; ++i) {
        cin >> a[i];
    }
    getMSS(n, a, dppre);
    swap(n, a);
    getMSS(n, a, dppost);
    swap(n, dppost);
    type ans = inf;
    for(int i = 1; i+k+1 <= n; ++i) {
        ans = max(ans, dppre[i] + dppost[i+k+1]);
    }
    cout << ans << endl;
    return 0;
}
