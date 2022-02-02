/**
 * 假设一个数N，其任意一个约束D，含有7这个数字，则N认为是不好的
 * 给定N，问下一个好的数字是几
 * 筛法，规模在1E7
 * 标记出所有的好和不好的数字，
 * 再搜索一遍记录每个数字的下一个好数字即可
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

void getString(char *p){
	char ch = __hv007();
	while(!isalpha(ch)) ch = __hv007();

	*p++ = ch;
	while(isalpha(ch = __hv007())) *p++ = ch;
	*p++ = '\0';
}

typedef long long llt;

#ifndef ONLINE_JUDGE
int const SIZE = 200;
#else
int const SIZE = 10000002;
#endif

int isOK(int n){
	while(n){
        if(7 == n%10) return 1;
		n /= 10;
	}
	return 0;
}

unsigned char Flag[SIZE] = {0};
int Ans[SIZE];

void init(){
    for(int i=1;i<SIZE;++i){
		if(Flag[i]) continue;
		if(isOK(i)){
			Flag[i] = 1;
			for(int j=i+i;j<SIZE;j+=i)Flag[j] = 1;
		}
	}
	int last = SIZE - 1;
	for(int i=SIZE-1;i;--i){
        if(Flag[i]){
			Ans[i] = last;
		}else{
			Ans[i] = last = i;
		}
	}
}

int N;


int main() {
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif    
    init();
    int nofkase = getInt();
	while(nofkase--){
		N = getInt();
		printf("%d\n", Flag[N]?-1:Ans[N+1]);
	}
	return 0;
}
