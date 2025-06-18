#include <iostream>
#include <cstring>

using namespace std;

#define MAXN 1000010
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
    if(a == b) {
        return a == SPLIT;
    }
    return (a - '0') + (b - '0') == 1; 
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

/*
1、首先，满足要求的子串一定是偶数长度的。
反证法证明，假设是奇数，如下：
原串： a    b    c
取反：1-a  1-b  1-c
反转：1-c  1-b  1-a
你会发现，要求 b == 1-b，显然是不合理的，所以可得，原串必为偶数。
2、于是，同样的方法， 观察偶数情况：
原串： a    b    c    d
取反：1-a  1-b  1-c  1-d
反转：1-d  1-c  1-b  1-a
得出结论：a+d==1   b+c==1
3、这样一来，只需要把原先的 马拉车 模板，两边字符相等的逻辑，改成字符相加等于1即可
4、最后统计这样的偶数串的个数，做简单的计数操作即可
*/


char str[MAXN];

int main() {
    int n;
    cin >> n;
    cin >> str;
    Manacher(str);
    long long ans = 0;
    for(int i = 0; str[i]; i += 2) {
        ans += p[i]/2;
    }
    cout << ans << endl;
    return 0;
} 