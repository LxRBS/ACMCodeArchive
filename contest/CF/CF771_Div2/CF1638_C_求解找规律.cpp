/**
 * ����һ�����У���ÿ��Ai��ʾͼ�ϵ�һ���㣬���Ai��Aj������Ծ����ߣ�
 * �ʣ���ͼ�м�����ͨ��
 * ��A1=k������Կ϶�A1���ڵ���ͨ����������k��λ��֮��
 * �����Կ϶�2~k��Χ��������A1��ͬһ����ͨ����
 * ����ֻ��Ҫ��ÿһ��Ai��¼��������ͨ���ܹ���������ұ߽缴��
*/
#include <bits/stdc++.h>
using namespace std;

char *__abc147, *__xyz258, __ma369[100000];
#define __hv007() ((__abc147==__xyz258) && (__xyz258=(__abc147=__ma369)+fread(__ma369,1,100000-1,stdin),__abc147==__xyz258) ? EOF : *__abc147++)

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
int const SIZE = 17;
#else
int const SIZE = 100110;
#endif

int N, A[SIZE];

int proc(){
	int anchor = 0, ans = 0;
	for(int i=1;i<=N;++i){
		if(i > anchor){
			++ans; anchor = i;
		}
		if(A[i] >= anchor) anchor = A[i];
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
		for(int i=1;i<=N;++i)A[i]=getInt();
		printf("%d\n", proc());
	}
    return 0;
}
