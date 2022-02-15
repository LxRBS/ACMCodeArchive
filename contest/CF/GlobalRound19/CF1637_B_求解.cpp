/**
 * ��һ�����飬������һ���걸���֣����Ҷ���û��ֵĻ���Ϊ��
 * ���ֵ�����+SIGA{ÿ�����ֵ�mex}
 * �ٶ��������ֵΪ���л����������Ǹ�����
 * ���ڸ������飬���������������ֵ֮��
 * ���Ƚ��ֵ������
 * �����������Ԫ��[a1, a2]�������Խ���𿪣�����Ҫ����
 * ����ȫ������[0, 0]����Ȼ�𿪵Ļ��Ѹ���
 * ���ں�������[a1, 0]��ͬ���𿪵Ļ��ѻ����
 * ��˶�һ��������ԣ���ֵ����ȫ�𿪵Ļ��ѣ�Ҳ���ǳ��ȼ��������
 * ���ڿ������⣬��һ��������ԣ���Ȼ����ΪN��������ֻ��1��������ΪN-1����������2��������
 * �ٿ���������⣬��һ������ּ��Σ������������left�������ұ���right������
 * �򺬸�0��������һ����(left+1)*(right+1)����
 * ע�⣬��Ϊ�����ǰ�ÿ���㶼�𿪣���������֮�以����Ӱ�졣
 * �����ּ���������
*/
#include <bits/stdc++.h>
using namespace std;

char *__abc147, *__xyz258, __ma369[100000];
#define __hv007() ((__abc147==__xyz258) && (__xyz258=(__abc147=__ma369)+fread(__ma369,1,100000,stdin),__abc147==__xyz258) ? EOF : *__abc147++)

int getInt(){
	int sgn = 1;
	char ch = __hv007();
	while( ch != '-' && ( ch < '0' || ch > '9' ) ) ch = __hv007();
	if ( '-' == ch ) {sgn = 0;ch=__hv007();}

	int ret = (int)(ch-'0');
	while( '0' <= (ch=__hv007()) && ch <= '9' ) ret = ret * 10 + (int)(ch-'0');
	return sgn ? ret : -ret;
}

#ifndef ONLINE_JUDGE
int const SIZE = 7;
#else
int const SIZE = 10010;
#endif

typedef long long llt;

int N, A[SIZE];

llt proc(){
    llt ans = 0;
    for(int i=0;i<N;++i){
        ans += (1+i)*(N-i);
    }
    for(int i=0;i<N;++i){
        if(A[i]) continue;
        ans += (i+1) * (N-i);
    }
    return ans;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif    
    int nofkase = getInt();
    while(nofkase--){
        N = getInt();
        for(int i=0;i<N;++i) A[i] = getInt();
        printf("%lld\n", proc());
    }
    return 0;
}
