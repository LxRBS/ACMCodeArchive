/**
 * N×N的地图，由点和#构成。可以最多选择两个原来是点的位置将其改成#
 * 问是否能够得到6个连续的#，水平、竖直、对角线和反对角线均可
 * N为1000，枚举
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
int const SIZE = 13;
#else
int const SIZE = 10030;
#endif  

int N;
char A[1010][1010];

bool procHeng(int r, int c){
	if(N - c < 6) return false;
	int cnt = 0;
	for(int i=0;i<6;++i){
		if('#'  != A[r][i+c]) ++cnt;
	}
	return cnt <= 2;
}

bool procShu(int r, int c){
	if(N - r < 6) return false;
	int cnt = 0;
	for(int i=0;i<6;++i){
		if('#' != A[r+i][c]) ++cnt;
	}
	return cnt <= 2;
}

bool procXie(int r, int c){
	if(N - c < 6 || N - r < 6) return false;
	int cnt = 0;
	for(int i=0;i<6;++i){
		if('#' != A[r+i][c+i]) ++cnt;
	}
	return cnt <= 2;
}

bool procFan(int r, int c){
	if(c < 5 || N - r < 6) return false;
	int cnt = 0;
	for(int i=0;i<6;++i){
		if('#' != A[r+i][c-i]) ++cnt;
	}
	return cnt <= 2;
}

bool proc(int r, int c){
	if(procHeng(r, c)) return true;
	if(procShu(r, c)) return true;
	if(procXie(r, c)) return true;
	if(procFan(r, c)) return true;
	return false;
}

bool proc(){
    for(int i=0;i<N;++i)for(int j=0;j<N;++j){
		if(proc(i, j)) return true;
	}
	return false;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif    
    scanf("%d", &N);
	for(int i=0;i<N;++i)scanf("%s", A[i]);
	puts(proc()?"Yes":"No");
    return 0;
}

