/**
  字符串S只包含ABC三种字母。每次操作可以删掉一个A和一个B，或者一个B和一个C。
  问是否经过若干次操作，可以把S删成空串
  显然查看各字母的数量即可
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

#ifndef ONLINE_JUDGE
int const SIZE = 22;
#else
int const SIZE = 220;
#endif

char A[SIZE];
bool proc(){
	int acnt = 0, bcnt = 0, ccnt = 0;
	for(char const *p=A;*p;++p){
		if('A'==*p) ++acnt;
		else if('B'==*p) ++bcnt;
		else if('C'==*p) ++ccnt;
	}
	return acnt + ccnt == bcnt;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    int nofkase;
	scanf("%d", &nofkase);
	while(nofkase--){
        scanf("%s", A);
		puts(proc()?"YES":"NO");
	}
    return 0;
}