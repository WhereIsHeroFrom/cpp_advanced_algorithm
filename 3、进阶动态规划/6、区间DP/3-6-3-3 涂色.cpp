///////////////////////////////////////////////////
/////////////////////����DPģ��/////////////////////
///////////////////////////////////////////////////

#include <iostream>
#include <cstring>
using namespace std;

#define maxn 55
#define type int

int n;
int dp[maxn][maxn];
char a[maxn];

// min��max��sum
type IntervalDP_Opt(type a, type b) {
    return min(a, b);
}

// �Ƿ�״ֵ̬
type IntervalDP_ValueInf() {
    return  1000000000;
}

// ��ʼ״ֵ̬
type IntervalDP_ValueInit() {
    return 1;
}

// �������� [l, r] ��ֵ
type IntervalDP_CalcState(int l, int r) {
    type ans = IntervalDP_ValueInf();
    for(int k = l; k < r; ++k) {
        ans = IntervalDP_Opt(ans, dp[l][k] + dp[k+1][r]);
    }
    if(a[l] == a[r]) {
        ans = IntervalDP_Opt(ans, dp[l+1][r]);
        ans = IntervalDP_Opt(ans, dp[l][r-1]);
    }
    return ans;
}

// �̶�ģ�壬һ���������Ҫ�޸�
type IntervalDP_Solve(int maxlen, int maxr) {
    type ans = IntervalDP_ValueInf();
    // 1��ö�����䳤��
    for(int i = 1; i <= maxlen; ++i) {
        // 2��ö���������
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
/////////////////////����DPģ��/////////////////////
///////////////////////////////////////////////////

int main() {
    cin >> &(a[1]);
    int n = strlen(&(a[1]));
    cout << IntervalDP_Solve(n, n) << endl;
    return 0;
}