///////////////////////////////////////////////////
/////////////////////����DPģ��/////////////////////
///////////////////////////////////////////////////

#include <iostream>
using namespace std;

#define maxn 210 
#define type int

int n;
int dp[maxn][maxn];
int a[maxn], mul[maxn][maxn];

// min��max��sum
type IntervalDP_Opt(type a, type b) {
    return max(a, b);
}

// �Ƿ�״ֵ̬
type IntervalDP_ValueInf() {
    return  0;
}

// ��ʼ״ֵ̬
type IntervalDP_ValueInit() {
    return 0;
}

// �������� [l, r] ��ֵ
type IntervalDP_CalcState(int l, int r) {
    type ans = IntervalDP_ValueInf();
    for(int k = l; k < r; ++k) {
        // dp[l][k] ... dp[k+1][r]
        int a = mul[l][k];
        int b = mul[k+1][r];
        int v = dp[l][k] + dp[k+1][r] + a*b/10;
        ans = IntervalDP_Opt(ans, v);
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
    cin >> n;
    int n2 = n*2;
    for(int i = 1; i <= n; ++i) {
        cin >> a[i];
        a[n+i] = a[i];
    }
    for(int i = 1; i <= n2; ++i) {
        mul[i][i-1] = 1;
        for(int j = i; j <= n2; ++j) {
            mul[i][j] = mul[i][j-1] * a[j] % 10;
        }
    }
    cout << IntervalDP_Solve(n, n2) << endl;
    return 0;
}