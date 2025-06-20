///////////////////////////////////////////////////
/////////////////////区间DP模板/////////////////////
///////////////////////////////////////////////////

#include <iostream>
using namespace std;

#define maxn 210 
#define type int

int n;
int dp[maxn][maxn];
int a[maxn], sum[maxn];

// min、max、sum
type IntervalDP_Opt(type a, type b) {
    return min(a, b);
}

// 非法状态值
type IntervalDP_ValueInf() {
    return  1000000000;
}

// 初始状态值
type IntervalDP_ValueInit() {
    return 0;
}

// 计算区间 [l, r] 的值
type IntervalDP_CalcState(int l, int r) {
    type ans = IntervalDP_ValueInf();
    for(int k = l; k < r; ++k) {
        int v = dp[l][k]
        + dp[k+1][r]
        + (sum[r] - sum[l-1]);
        ans = IntervalDP_Opt(ans, v);
    }
    return ans;
}

// 固定模板，一般情况不需要修改
type IntervalDP_Solve(int maxlen, int maxr) {
    type ans = IntervalDP_ValueInf();
    // 1、枚举区间长度
    for(int i = 1; i <= maxlen; ++i) {
        // 2、枚举区间起点
        for(int j = 1; j+i-1 <= maxr; ++j) {
            int l = j;
            int r = j+i-1;
            if(i == 1) {
                dp[l][r] = IntervalDP_ValueInit();
            }else {
                dp[l][r] = IntervalDP_CalcState(l, r);
            }
            if(i == maxlen) {
                ans = IntervalDP_Opt(ans, dp[l][r]);
            }
        }
    }
    return ans;
}

///////////////////////////////////////////////////
/////////////////////区间DP模板/////////////////////
///////////////////////////////////////////////////

int main() {
    cin >> n;
    for(int i = 1; i <= n; ++i) {
        cin >> a[i];
        sum[i] = sum[i-1] + a[i];
    }
    cout << IntervalDP_Solve(n, n) << endl;
    return 0;
}