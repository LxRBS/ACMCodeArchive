/**
  n���£�ÿ������di�죬ÿһ��ķ������ǵ����ڵ��µ���š�
  ����ѡ��������x�죬ʹ�÷����ܺ���󡣿��Կ���
  �򵥿��Ǿ��ܷ��֣�����ֵ��Ȼ����ĩ��ͷ����������ĩ��β��
  ��˼��2N�μ��ɡ����Կ��꣬�������Ϊԭ����2����
  ע��x�Լ��������longlong��
*/
#include <bits/stdc++.h>
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

llt getULL(){
	char ch = __hv007();
	while( ch < '0' || ch > '9' ) ch = __hv007();

	llt ret = (int)(ch-'0');
	while( '0' <= ( ch = __hv007() ) && ch <= '9' ) ret = (ret<<1) + (ret<<3) + (llt)(ch-'0');
	return ret;
}

#ifndef ONLINE_JUDGE
int const SIZE = 11;
#else
int const SIZE = 500010;
#endif

/// Di = SIGMA(di)
int A[SIZE];
int N;
llt X;
llt S[SIZE], D[SIZE];

llt proc(int idx){
    /// �ҵ�kʹ�ã�Dk<=x-1+D[idx]<D[k+1] ��һ����
    int k = upper_bound(D, D+N+N, X-1+D[idx]) - D - 1;
    llt left = X-1+D[idx]-D[k];
    llt ans = A[idx] + S[k] - S[idx] + left * (left+1) / 2;

    /// �ҵ�kʹ�� D[k-1]<D[idx+N]-x<=D[k]
    k = upper_bound(D, D+N+N, D[idx+N]-X) - D;
    left = X + D[k] - D[idx+N];
    llt tmp = S[idx+N]-S[k]+left*(A[k]+A[k]-left+1)/2;
    return max(ans, tmp);
}

llt proc(){
    llt ans = 0LL;
    for(int i=0;i<N;++i){
        ans = max(ans, proc(i));
    }
    return ans;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt","r",stdin);
#endif
    N = getUnsigned();
    X = getULL();

    A[0] = D[0] = getUnsigned();
    S[0] = (llt)A[0] * (A[0]+1) >> 1;
    for(int i=1;i<N;++i){
        D[i] = D[i-1] + (A[i] = getUnsigned());
        S[i] = S[i-1] + ((llt)A[i] * (A[i]+1) >> 1);
    }
    for(int i=N;i<N+N;++i){
        D[i] = D[i-1] + (A[i] = A[i-N]);
        S[i] = S[i-1] + ((llt)A[i] * (A[i]+1) >> 1);
    }
    cout<<proc()<<endl;
    return 0;
}
