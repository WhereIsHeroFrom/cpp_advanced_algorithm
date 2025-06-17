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
#include <vector>
#include <algorithm>
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

int n;
struct Pair {
    ull val;
    int pos;
};

bool cmp(const Pair& a, const Pair&b) {
    if(a.val == b.val) {
        return a.pos < b.pos;
    }
    return a.val < b.val;
}

bool check(int len) {
    vector<Pair> v;
    // 1、获取所有长度为 len 的子串的哈希值
    for(int i = 0; i + len - 1 < n; ++i) {
        ull val = get(i, i + len-1);
        v.push_back( {val, i} );
    }
    // 2、把所有子串的哈希值相等的元素排在一起，并且位置按递增排序
    sort(v.begin(), v.end(), cmp);
    // 3、找到所有子串哈希值相等的元素，判断位置是否重叠，如果一旦发现不重叠，返回true
    for(int i = 0; i < v.size(); ++i) {
        int j = i+1;
        for(; j < v.size(); ++j) {
            if( v[j].val != v[i].val ) {
                i = j - 1;
                break;
            }
            if(v[j].pos - v[i].pos >= len) {
                return true;
            }
        }
    }
    // 4、如果找不到，返回 false
    return false;
}


int main() {
    string s;
    cin >> s;
    n = s.size();
    init(s);
    int l = -1, r = n/2 + 1;
    while(l + 1 < r) {
        int mid = (l + r) / 2;
        if(check(mid)) {
            l = mid;
        }else {
            r = mid;
        }
    }
    cout << l << endl;
    return 0;
}