/**
   �����һ��ż��N��Ȼ��1��N/2һ�ԣ�2��N/2+1һ�ԣ�...��N/2-1��Nһ��
   ���ڸ���a/b/c����ʾ��ĳ��ż�������a��bһ�ԣ�����c��Ե����Ƕ���
   ��������ڣ����-1.
   ���ɺ����ԣ�ע�ⲻ���ڵ��ж��������ɡ�
*/
#include<bits/stdc++.h>
using namespace std;

char *__abc147, *__xyz258, __ma369[100000];
#define __hv007() ((__abc147==__xyz258) && (__xyz258=(__abc147=__ma369)+fread(__ma369,1,100000,stdin),__abc147==__xyz258) ? EOF : *__abc147++)

int getUnsigned(){
	char ch = __hv007();
	while( ch < '0' || ch > '9' ) ch = __hv007();

	int ret = (int)(ch-'0');
	while( '0' <= ( ch = __hv007() ) && ch <= '9' ) ret = (ret<<1) + (ret<<3) + (int)(ch-'0');
	return ret;
}

typedef long long llt;

llt f(llt a,llt b,llt c){
    if(a>b) swap(a, b);
    llt n = b - a;
    if(a>n&&b>n) return -1;
    if(c>n+n) return -1;
    return c > n ? c - n : c + n;
}

int main(){
    //freopen("1.txt","r",stdin);
    int nofkase = getUnsigned();
    while(nofkase--){
        int a = getUnsigned();
        int b = getUnsigned();
        int c = getUnsigned();
        printf("%lld\n", f(a,b,c));
    }
    return 0;
}

