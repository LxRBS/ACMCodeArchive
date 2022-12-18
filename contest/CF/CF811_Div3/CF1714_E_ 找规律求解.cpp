/**
 * 给定一个数组，对Ai可以做操作令Ai += Ai % 10
 * 可以进行任意次操作，问能令所有Ai相等
 * 很显然，对10倍数无法改变其值，对5倍数，只能将其加5。
 * 对其他尾数，简单计算一下就能发现他们都能到达10k+2的位置
 * 然后10k+2的位置可以去向10(k+2)+2的位置，即10的倍的奇偶保持不变
 * 因此对所有尾数保存它到2的10的倍数，然后看是否统一
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
int const SIZE = 14;
#else
int const SIZE = 2E5+10;
#endif

int N;
int A[SIZE];

bool check50(){
	unordered_set<int> s5, s0;
	for(int i=0;i<N;++i){
		int left = A[i] % 10;
		if(left != 5 && left != 0) return false;
		if(5 == left){
			s5.insert(A[i] / 10);
			if(s5.size() > 1) return false;
		}else{
            s0.insert(A[i] / 10);
			if(s0.size() > 1) return false;  
		}
	}
	if(s5.empty() || s0.empty()) return true;
	if(*s5.begin() + 1 != *s0.begin()) return false;
	return true;
}

bool proc(){
	if(1 == N) return true;
	if(check50()) return true;

	for(int i=0;i<N;++i){
		int left = A[i] % 10;
		if(left == 5 || left == 0) return false;
	}	

	unordered_set<int> s;
	for(int i=0;i<N;++i){
		int left = A[i] % 10;
		int bei = A[i] / 10;
		if(1 == left){
			s.insert(bei+2);
		}else if(2 == left){
			s.insert(bei+2); 
		}else if(3 == left){
			s.insert(bei+1);
		}else if(4 == left){
            s.insert(bei+2); 
		}else if(6 == left){
			s.insert(bei+1);
		}else if(7 == left){
			s.insert(bei+3);
		}else if(8 == left){
			s.insert(bei+2); 
		}else if(9 == left){
			s.insert(bei+3);
		}else{
			// while(1);
			throw runtime_error("XX");
		}
	}
	int ans = 0;
	for(int i: s){
		if(3 == (ans |= (i&1)?1:2)){
			return false;
		}
	}
	return true;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    int nofkase = getInt();
	while(nofkase--){
        N = getInt();
		for(int i=0;i<N;++i) A[i] = getInt();
		puts(proc()?"Yes":"No");
	}
    return 0;
}
