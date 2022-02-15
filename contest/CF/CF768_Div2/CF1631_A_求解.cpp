/**
 * 给定A、B两个数组，对每一个i，均可以交换Ai和Bi，也可以不换
 * 求min(max(Ai)*max(Bi))
 * 对每一对Ai和Bi，将大数放到A，小数放到B
 * 然后计算max(Ai)*max(Bi)即可
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
int const SIZE = 110;
#endif

int N;
typedef pair<int, int> pii;
pii A[SIZE];

int main() {
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif    
    int nofkase = getInt();
    while(nofkase--){
		N = getInt();
		for(int i=0;i<N;++i)A[i].first = getInt();
		for(int i=0;i<N;++i)A[i].second = getInt();
		if(1 == N){
			printf("%d\n", A[0].first * A[0].second);
			continue;
		}
        
		int maxv = -1, max2 = -1;
		for(int i=0;i<N;++i){
			maxv = max(maxv, max(A[i].first, A[i].second));
			max2 = max(max2, min(A[i].first, A[i].second));
		}
        printf("%d\n", maxv * max2);
	}	
    return 0;
}