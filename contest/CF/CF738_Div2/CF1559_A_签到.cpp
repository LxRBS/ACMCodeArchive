/**
   ����һ�����飬ÿ��ѡ��һ�����䣬����������޸ĳ�������������λ��
   Ŀ���Ǿ������ɴβ�����ʹ����������������С
   �����Բ����Ĳ����ʹ�����ʵ��Ӱ������ֱ������С�
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

int N;
int A[110];

int main(){
    //freopen("1.txt","r",stdin);
    int nofkase = getUnsigned();
    while(nofkase--){
        N = getUnsigned();
        int ans = 0x7FFFFFFF;
        for(int i=1;i<=N;++i){
            ans &= (A[i] = getUnsigned());
        }
        printf("%d\n", ans);
    }
    return 0;
}

