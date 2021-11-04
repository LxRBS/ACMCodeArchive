/**
 * ����һ��N����A���ٸ���һ��K��ÿ�β������Խ�һ����СԪ�ؼ�1��Ҳ���Խ�һ�����Ԫ�ؼ�1
 * ������Ҫ���β�����ʹ��������������K����ȵ�Ԫ��
 * ����ȷ�������ȵ�Ԫ�ص�ȡֵһ�����Ѿ�������ԭ�����е�
 * ������Auniqueһ�£����Ҽ�¼ai������cnti
 * Bi��ʾ�������Ҽ��㵽λ��iʱ����Ҫ�Ĳ�������
 * BCnti��ʾ��iʱ��ֵ����ai����һ���ж��ٸ�
 * Ci��CCnti��ʾ�����������
 * Di��ʾ��aiΪĿ���������������С����������Di���ڼ��������
 * ���󲿷ּ��ɣ������ȫ�����ϲ��ִ���
 * ���Ҳ��ּ��ɣ����ҵ�ȫ�����ϲ��ִ���
 * minDi���Ǵ�
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
int const SIZE = 21;
#else 
int const SIZE = 200100;
#endif

typedef long long llt;

int N, K;
llt A[SIZE];
unordered_map<llt, int> Cnt;

llt B[SIZE], C[SIZE];
int BCnt[SIZE], CCnt[SIZE];

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    N = getInt();
    K = getInt();
    bool flag = false;
    for(int i=1;i<=N;++i) if(++Cnt[A[i] = getInt()]>=K) flag=true;
    if(flag){
        puts("0"); return 0;
    }

    sort(A+1, A+N+1);
    N = unique(A+1, A+N+1) - A - 1;

    B[1] = 0; BCnt[1] = Cnt[A[1]];
    for(int i=2;i<=N;++i){
        B[i] = B[i-1] + BCnt[i-1] * (A[i] - A[i-1]);
        BCnt[i] = BCnt[i-1] + Cnt[A[i]];
    }
    C[N] = 0; CCnt[N] = Cnt[A[N]];
    for(int i=N-1;i>=1;--i){
        C[i] = C[i+1] + CCnt[i+1] * (A[i+1] - A[i]);
        CCnt[i] = CCnt[i+1] + Cnt[A[i]];
    }
    llt ans = 0x3F3F3F3F3F3F3F3F;
    for(int tmp, i=1;i<=N;++i){
        tmp = BCnt[i] - K;
        if(tmp >= 0){ // ���󲿷ּ���
            ans = min(ans, B[i]-tmp);
        }else{ // ����ȫ�����ϴ��ҵĲ���
            tmp = CCnt[i] - Cnt[A[i]] + tmp;
            ans = min(ans, B[i] + C[i] - tmp);
        }
        tmp = CCnt[i] - K;
        if(tmp >= 0){ // ���Ҳ��ּ��ɣ�������ҵ�ȫ���������� 
            ans = min(ans, C[i] - tmp);
        }
    }
    cout<<ans<<endl;
    return 0;
}
