/**
 * ��H(n) = phi(n)/n
 * ��[2, N]�У�H(x)����Сֵ�������ֵ��
 * ������H(n)=\Pai{(1-1/pi)}
 * ��ˣ���xȡN������������ʱ��H(x)ȡ�����ֵ
 * ��x�Ĳ�ͬ�������������ʱ��H(x)ȡ����Сֵ
 * ����ɸ��������35000���ڵļ��ɣ�һ��3000+
 * ������Χ�������������ɡ�����֮��ľ������Ϊ200+
 * �������ж�200+������ÿ�����ѭ��3000+
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

typedef long long llt;

#ifndef ONLINE_JUDGE
int const SIZE = 35000;
#else
int const SIZE = 35000;
#endif

bool isComp[SIZE] = {false};
llt P[SIZE];
int PCnt = 0;
void sieve(){
    for(llt i=2;i<SIZE;++i){
        if ( !isComp[i] ) P[PCnt++] = i;

        for(llt j=0;j<PCnt&&i*P[j]<SIZE;++j){
            isComp[i*P[j]] = true;
            if ( 0 == i % P[j] ) break;
        }
    }
}

llt N;

vector<llt> Vec;

llt const PMax = 34981;
llt f(){
    if(N<=PMax){
		llt *p = lower_bound(P, P+PCnt, N);
		if(*p != N) --p;
		llt ans2 = *p;
		return ans2;
	}

    llt n = N;
L:
	for(int i=0;i<PCnt;++i){
		if(n % P[i] == 0){
			if(--n == PMax) return PMax;
			goto L;
		}
	}
	return n;
}

void proc(){
    if(1 == N){
		puts("-1");
		return;
	}

	auto a320 = lower_bound(Vec.begin(), Vec.end(), N);
	if(*a320 != N) --a320;
	llt ans1 = *a320;

	llt ans2 = f();

	printf("%lld %lld\n", ans1, ans2);
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif    
    sieve();
	llt tmp = 1;
	for(int i=0;;++i){
        tmp *= P[i];
		Vec.push_back(tmp);
		if(tmp > 10000000010LL) break;
	}
    int nofkase = getInt();
    while(nofkase--){
        N = getInt();
		proc();
    }
    return 0;
}
