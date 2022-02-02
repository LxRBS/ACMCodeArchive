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
typedef vector<int> IntVecTy;
typedef pair<int, int> PiiTy;

struct pair_hash{
	inline size_t operator()(const PiiTy&p)const{
		return p.first * 1331 + p.second;
	}	
};

#ifndef ONLINE_JUDGE
int const SIZE = 11;
#else
int const SIZE = 110;
#endif

int N;
char A[SIZE];

bool proc(){
    if(N >= 3) return false;
    if(1 == N) return true;
    return A[0] != A[1];
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif    
    int nofkase;
    scanf("%d", &nofkase);
	while(nofkase--){
		scanf("%d%s", &N, A);
        puts(proc()?"YES":"NO"); 
	}
    return 0;
}
