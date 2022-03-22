/**
 * 平面上从原点出发，给定操作序列。要么往前走一，要么转方向
 * 模拟
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
int const SIZE = 45;
#else
int const SIZE = 1E5+5;
#endif

int N;
char A[SIZE];

pair<int, int> proc(){
	int x = 0, y = 0;
	int t = 0;
	for(int i=0;i<N;++i){
		if('S' == A[i]){
            if(0 == t){
                x += 1;
			}else if(1 == t){
                y -= 1;
			}else if(2 == t){
                x -= 1;
			}else if(3 == t){
                y += 1;
			}else{
				throw runtime_error("XX");
			}
		}else{
			t = (t+1)%4;
		}
	}
	return {x, y};
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif    
    scanf("%d%s", &N, A);
	auto p = proc();
	printf("%d %d\n", p.first, p.second);
    return 0;
}