/**
 * ����һ������A����һ�ֲ�����ÿ�ο���ѡ��һ��ż�����ȵ����䣬
 * ����һ�����ݸ��Ƶ�ǰһ�룬���ı�ǰһ�����ݡ���һ�벻�䡣
 * ������Ҫ���β��������Խ����������Ϊһ��
 * ��Ϊֻ�ܰѺ���ĸ��Ƶ�ǰ��ȥ������Ŀ��������һ��ֵ��
 * �����һ��ֵ��ʼ��̰�ļ��ɡ�
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
int const SIZE = 33;
#else
int const SIZE = 200010;
#endif

int N;
int A[SIZE];

int main() {
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif    
    int nofkase = getInt();
    while(nofkase--){
		N = getInt();
		for(int i=1;i<=N;++i) A[i] = getInt();
		if(1 == N){
			puts("0"); continue;
		}
		int cnt = 0;
		int now = N - 1;
		while(1){
            while(now >= 1 && A[now] == A[N]) --now;
			if(now == 0) break;

			++cnt;
			int start = max(1, now+1-(N-now));
			fill(A+start, A+now+1, A[N]);
			now = start - 1;
		}
		printf("%d\n", cnt);
	}	
    return 0;
}