#include <iostream>
#include <cstring>

using namespace std;

#define MAXN 2000010
#define SPLIT '$'
int p[MAXN];
char strTmp[MAXN];

void ManacherPre(char *str) {
    strcpy(strTmp, str);
    int i;
    for(i = 0; strTmp[i]; ++i) {
        str[2*i] = SPLIT;
        str[2*i+1] = strTmp[i];
    }
    str[2*i] = SPLIT;
    str[2*i+1] = '\0';
}

bool ManacherMatch(char a, char b) {
    return a == b;
}

int Manacher(char *str) {
    ManacherPre(str);
    // ct  : 当前已知最右回文区域的中心位置
    //  r  : 当前已知最右回文区域的右边界（即ct + p[ct]）
    // p[] : 记录每个位置的回文半径
    int ct = 0, r = 0, maxLen = 1;
    p[0] = 1;
    for(int i = 1; str[i]; ++i) {
        // 1.计算p[i]初始值 
        if(i < r) {
            p[i] = min(p[2*ct-i], r-i);
        }else {
            p[i] = 0;
        }

        // 2.扩张p[i]，以适应达到p[i]最大值 
        while(i-p[i]>=0 && ManacherMatch(str[i-p[i]], str[i+p[i]]) )
            ++p[i];

        // 3.更新ct
        if(p[i] + i > r) {
            ct = i;
            r = p[i] + i;
        }
        // 4.更新最长回文 
        if(2*p[i]-1 > maxLen) {
            maxLen = 2*p[i] - 1;
        }
    }
    return maxLen; 
}

char str[MAXN];
int sum[MAXN];

int getsum(int l, int r) {
    int pre = 0;
    if(l) {
        pre = sum[l-1];
    }
    return sum[r] - pre;
}

/*
1、由于反异或操作只能进行最多一次，所以我们可以挑选其中一段来进行反异或操作，
而剩下的段，统计 1 的个数就可以了，于是问题就转变成如何找到需要反异或操作的那一段；
2、考虑下面这种情况，首先考虑奇数：
a b c d e
^ ^ ^ ^ ^
e d c b a
满足可以反异或的前提是：中间这个位置必须是 0；因为自己异或自己必然是 0
然后由于异或满足交换律，也就是 b^d == d^b ，所以就转变成了求回文串的过程中；
同样偶数也是一样的，只不过偶数不需要判断 中间位置是 0 的情况；
3、利用 manacher 计算出每个位置作为回文串中心的最大半径 p[i]
求区间 [i, i+p[i]-1] 中的 1 的个数，代表 反异或 操作之前需要的 1；
求区间 [i-p[i]+1, i+p[i]-1] 以外 1 的个数，代表不进行反异或操作的段中需要的 1；
两者累加即可
*/


int main()
{
    cin >> str;
    Manacher(str);
    int n = strlen(str);
    for(int i = 1; i < n; ++i) {
        sum[i] = sum[i-1] + (str[i] == '1');
    }
    int ret = sum[n-1];
    for(int i = 0; i < n; ++i) {
        if(i & 1) {
            // 奇数位置，以数字为中心
            if( str[i] == '1' ) {
                // 中间数不可能为 1，因为自己异或自己一定是 0
                continue;
            }
        }else {
            // 偶数位置，以 '$' 为中心
        }
        // 统计 [i, i+p[i]-1] 的 1 的个数
        //     再统计这个回文串 [i-p[i]+1, i+p[i]-1] 以外1的个数
        int ans = getsum(i, i+p[i]-1) + getsum(0, n-1) - getsum(i-p[i]+1, i+p[i]-1);
        ret = min(ret, ans);
    }
    cout << ret << endl;
    return 0;
}