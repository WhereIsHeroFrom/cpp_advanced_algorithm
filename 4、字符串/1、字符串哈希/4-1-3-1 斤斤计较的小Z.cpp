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
/////////////////×Ö·û´®hashÄ£°å//////////////////
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
    string a, b;
    cin >> a >> b;
    init(a);
    ull v = get(0, a.size()-1);
    int len = a.size();
    int ans = 0;
    init(b);
    for(int i = 0; i + len - 1 < b.size(); ++i) {
        if( get(i, i + len - 1) == v ) {
            ++ans;
        }
    }
    cout << ans << endl;
    return 0;
}