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

int main() {
    int n, m;
    cin >> n >> m;
    cin >> str;
    Manacher(str);
    while(m--) {
        int l, r;
        cin >> l >> r;
        l = 2*l - 1;
        r = 2*r - 1;
        int mid = (l + r) / 2;
        if(mid + p[mid] - 1 >= r) {
            cout << "Yes" << endl;
        }else {
            cout << "No" << endl;
        }
    }
    return 0;
}