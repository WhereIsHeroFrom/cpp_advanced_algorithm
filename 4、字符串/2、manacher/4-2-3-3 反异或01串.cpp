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
1�����ڷ�������ֻ�ܽ������һ�Σ��������ǿ�����ѡ����һ�������з���������
��ʣ�µĶΣ�ͳ�� 1 �ĸ����Ϳ����ˣ����������ת�������ҵ���Ҫ������������һ�Σ�
2����������������������ȿ���������
a b c d e
^ ^ ^ ^ ^
e d c b a
������Է�����ǰ���ǣ��м����λ�ñ����� 0����Ϊ�Լ�����Լ���Ȼ�� 0
Ȼ������������㽻���ɣ�Ҳ���� b^d == d^b �����Ծ�ת���������Ĵ��Ĺ����У�
ͬ��ż��Ҳ��һ���ģ�ֻ����ż������Ҫ�ж� �м�λ���� 0 �������
3������ manacher �����ÿ��λ����Ϊ���Ĵ����ĵ����뾶 p[i]
������ [i, i+p[i]-1] �е� 1 �ĸ��������� ����� ����֮ǰ��Ҫ�� 1��
������ [i-p[i]+1, i+p[i]-1] ���� 1 �ĸ������������з��������Ķ�����Ҫ�� 1��
�����ۼӼ���
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
            // ����λ�ã�������Ϊ����
            if( str[i] == '1' ) {
                // �м���������Ϊ 1����Ϊ�Լ�����Լ�һ���� 0
                continue;
            }
        }else {
            // ż��λ�ã��� '$' Ϊ����
        }
        // ͳ�� [i, i+p[i]-1] �� 1 �ĸ���
        //     ��ͳ��������Ĵ� [i-p[i]+1, i+p[i]-1] ����1�ĸ���
        int ans = getsum(i, i+p[i]-1) + getsum(0, n-1) - getsum(i-p[i]+1, i+p[i]-1);
        ret = min(ret, ans);
    }
    cout << ret << endl;
    return 0;
}