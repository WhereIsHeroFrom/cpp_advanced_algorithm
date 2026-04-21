#include <iostream>
#include <cstring>
using namespace std;

#define ll long long
#define maxd 65

// 一般情况下，1个参数居多，部分情况会有两个参数
// 当需要3个参数的时候，就需要修改这个结构体了
struct DpData {
    ll data0;
    ll data1;
    static ll K;
    static ll base;
    DpData () : data0(0), data1(0) {
        init();
    }

    void init();
    ll dfsReturn(bool is_leadingZero) const;
    DpData getNextDpData(bool is_leadingZero, int digit) const;
};

// 0、修改点，主要修改 data0_max 和 data1_max 的范围
#define data0_max 305
#define data1_max 2
ll dp[maxd][2][2][data0_max][data1_max];

// 1、修改点，通过输入数据进行输入
ll DpData::K = 0;
// 2、修改点，通过题目条件进行修改，二进制就是 2，十进制就是 10，也有可能通过输入数据输入
ll DpData::base = 0;

// 3、修改点，数据的初始化，确定 data0 和 data1 表示的是什么
void DpData::init() {
    data0 = 0;   // 所有数字之和
    data1 = 0;   // 留空不用
}

// 4、修改点，dfs 返回值
ll DpData::dfsReturn(bool is_leadingZero) const {
    if(is_leadingZero) {
        // 0000000000
        return K == 0 ? 1 : 0;
    }
    return data0 == K;
}

// 5、修改点，状态转移的过程
DpData DpData::getNextDpData(bool is_leadingZero, int digit) const {
    DpData ret = *this;
    if(is_leadingZero) {
        // 0000000000
        ret.data0 = digit;
    }else {
        // 0000122313
        ret.data0 += digit;
    }
    return ret;
}

// 十进制下
// 12345
// 10893
ll dfs(
    const string& num,    // 数字字符串
    int depth,            // 当前枚举到的是第几个数位
    bool is_leadingZero,  // 默认为 true，代表前面枚举的都是0
    bool is_limit,        // 默认为 false，代表前面所有位都和 num 相等
    DpData dpdata         // 数位DP用到的核心数据结构
) {
    if(depth == num.size()) {
        return dpdata.dfsReturn(is_leadingZero);
    }
    int maxdigit = is_limit ? (DpData::base-1) : (num[depth]-'0');
    ll& ans = dp[depth][is_leadingZero][is_limit][dpdata.data0][dpdata.data1];
    if(ans != -1) {
        return ans;
    }
    ans = 0;
    for(int i = 0; i <= maxdigit; ++i) {
        ans += dfs(
            num,
            depth+1,
            is_leadingZero && (i == 0),
            is_limit || (i < maxdigit),
            dpdata.getNextDpData(is_leadingZero, i)
        );
    }
    return ans;
}


// 固定模板，不需要修改，求 [0, n] 中所有满足条件的数的数量
ll getans(ll n) {
    memset(dp, -1, sizeof(dp));
    int a[maxd], asize = 0;
    string s;
    while(n) {
        a[asize++] = n % DpData::base;
        n /= DpData::base;
    }
    if(asize == 0) {
        a[asize++] = 0;
    }
    for(int i = asize-1; i >= 0; --i) {
        s.push_back( '0' + a[i] );
    }
    DpData dpd;
    return dfs( s, 0, true, false, dpd);
}


// 固定模板，数位DP的差分操作，求 [l, r] 中所有满足条件的数的个数
ll getans(ll l, ll r) {
    return getans(r) - getans(l-1);
}

ll solve(ll a, ll b, ll k) {
    ll l = a - 1;
    ll r = b + 1;
    ll lans = getans(a-1);
    while(l + 1 < r) {
        ll mid = (l + r) >> 1;
        if( getans(mid) - lans >= k ) {
            r = mid;
        }else {
            l = mid;
        }
    }
    if( getans(r) - lans >= k ) {
        return r;
    }
    return -1;
}

int main() {
    ll l, r, b, m, k;
    cin >> l >> r >> b >> m >> k;
    DpData::base = b;
    DpData::K = m;
    ll ans = solve(l, r, k);
    if(ans == -1) {
        cout << "No" << endl;
    }else {
        cout << ans << endl;
    }
    return 0;
}