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
    // ct  : ��ǰ��֪���һ������������λ��
    //  r  : ��ǰ��֪���һ���������ұ߽磨��ct + p[ct]��
    // p[] : ��¼ÿ��λ�õĻ��İ뾶
    int ct = 0, r = 0, maxLen = 1;
    p[0] = 1;
    for(int i = 1; str[i]; ++i) {
        // 1.����p[i]��ʼֵ 
        if(i < r) {
            p[i] = min(p[2*ct-i], r-i);
        }else {
            p[i] = 0;
        }

        // 2.����p[i]������Ӧ�ﵽp[i]���ֵ 
        while(i-p[i]>=0 && ManacherMatch(str[i-p[i]], str[i+p[i]]) )
            ++p[i];

        // 3.����ct
        if(p[i] + i > r) {
            ct = i;
            r = p[i] + i;
        }
        // 4.��������� 
        if(2*p[i]-1 > maxLen) {
            maxLen = 2*p[i] - 1;
        }
    }
    return maxLen; 
}

/*
1�����ȣ�����Ҫ����Ӵ�һ����ż�����ȵġ�
��֤��֤�������������������£�
ԭ���� a    b    c
ȡ����1-a  1-b  1-c
��ת��1-c  1-b  1-a
��ᷢ�֣�Ҫ�� b == 1-b����Ȼ�ǲ�����ģ����Կɵã�ԭ����Ϊż����
2�����ǣ�ͬ���ķ����� �۲�ż�������
ԭ���� a    b    c    d
ȡ����1-a  1-b  1-c  1-d
��ת��1-d  1-c  1-b  1-a
�ó����ۣ�a+d==1   b+c==1
3������һ����ֻ��Ҫ��ԭ�ȵ� ������ ģ�壬�����ַ���ȵ��߼����ĳ��ַ���ӵ���1����
4�����ͳ��������ż�����ĸ��������򵥵ļ�����������
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