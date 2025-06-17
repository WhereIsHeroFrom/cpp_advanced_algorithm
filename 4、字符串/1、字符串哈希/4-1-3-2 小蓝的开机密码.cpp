/*
hash(0, 0) = s[0]
hash(0, 1) = s[0] * B + s[1]
hash(0, 2) = s[0] x B^2 + s[1] x B + s[2]
hash(0, r)   = sum( s[i] * B^(r-i) | 0 <= i <= r )
hash(0, l-1) = sum( s[i] * B^(l-1-i) | 0 <= i <= l-1 )
hash(0, l-1) * B^{r-l+1} = sum( s[i] * B^(l-1-i) | 0 <= i <= l-1 ) * B^{r-l+1}
                         = sum( s[i] * B^(r-i) | 0 <= i <= l-1 )

hash(0, r) - hash(0, l-1) * B^{r-l+1}
=     sum( s[i] * B^(r-i) | 0 <= i <= r ) - sum( s[i] * B^(r-i) | 0 <= i <= l-1 )
=     sum( s[i] * B^(r-i) | l <= i <= r )             
*/
#include <iostream>
using namespace std;

////////////////////////////////////////////////
/////////////////字符串hash模板//////////////////
////////////////////////////////////////////////
#define maxn 1000010
#define ull unsigned long long
#define B 271
ull Power[maxn];
ull Hash[maxn];

void init(const string& s) {
    Power[0] = 1;
    Hash[0] = s[0];
    for(int i = 1; i < s.size(); ++i) {
        Hash[i] = Hash[i-1] * B + s[i];
        Power[i] = Power[i-1] * B;
    }
}
ull get(int l, int r) {
    // Hash[r] - Hash[l-1] * B ^ {r-l+1}
    if(l == 0) {
        return Hash[r];
    }
    return Hash[r] - Hash[l-1] * Power[r-l+1];
}
////////////////////////////////////////////////

int main() {
    string s;
    cin >> s;
    int n = s.size();
    init(s);
    // 1、逆序枚举满足条件的长度，如果发现有一个长度满足条件，直接跳出
    int l = -1, r = n/2 + 1;
    while(l + 1 < r) {
        int i = (l + r) / 2;
        bool check = false;
        for(int j = 0; j + 2*i - 1 < n; ++j) {
            int L = j;
            int R = j + i - 1;
            ull v = get(L, R);
            for(int k = R+1; k + i - 1 < n; ++k) {
                if(v == get(k, k + i - 1)) {
                    check = true;
                    break;
                }
            }
            if(check) break;
        }
        if(check) {
            l = i;
        }else {
            r = i;
        }
    }
    cout << l << endl;
    return 0;
}
