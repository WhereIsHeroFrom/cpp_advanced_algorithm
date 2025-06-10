#include <iostream>
using namespace std;

#define maxn 300010
int a[maxn];

// ���ģ��������������������е�
// ���Ҫ�󵥵�������ֻ��Ҫ�� a[i] <= g[mid] �ĳ� a[i] < g[mid]
int getLIS(int n, int a[], int dp[]) {
    // g[i] ������Ϊ i ������������е�
    // ���һ������ʲô
    int g[maxn], gSize = 0;
    for(int i = 0; i < n; ++i) {
        // g[] = {1, 4, 5, 7, 8}   
        int l = -1, r = gSize;
        while(l + 1 < r) {
            int mid = (l + r) >> 1;
            if( a[i] <= g[mid] ) {
                r = mid;
            }else {
                l = mid;
            }
        }
        // l + 1 == r
        if(r == gSize) {
            g[gSize++] = a[i];
        }else {
            g[r] = a[i];
        }
        dp[i] = gSize;
    }
    return gSize;
}

int dp[maxn];

int main() {
    int n;
    cin >> n;
    for(int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    cout << getLIS(n, a, dp) << endl;
    return 0;
}