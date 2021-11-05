/**
 * 给一个字符串，拆成两个序列a和b
 * 要求a的字典序尽可能小，b随意
 * 显然a序列只要取源字符串中最小的一个字母即可
 * b是剩下的n-1个
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
int const SIZE = 110;
#endif

#define fi first
#define se second

typedef long long llt;

char S[SIZE];

void proc(){
	int n = strlen(S);
	char ch = *min_element(S, S+n);
	printf("%c ", ch);
	int t = 0;
	for(int i=0;i<n;++i){
        if(t){
            printf("%c", S[i]);
		}else{
			if(S[i] == ch) t = 1;
			else printf("%c", S[i]);
		}
	}
	puts("");
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    int nofkase;
	scanf("%d", &nofkase);
	while(nofkase--){
		scanf("%s", S);
		proc();
	}
	return 0;
}