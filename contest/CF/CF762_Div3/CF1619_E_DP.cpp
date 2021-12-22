/**
   给定一个数组A，每一次操作可以任选一个Ai，将其数值加1。
   问：欲使mex(A)=0，最少需要几次操作;mex(A)=1要几次；mex(A)=2,3,4,...,n各要几次，无解输出-1
   考虑mex(A) = i，则0~i-1每个值至少有一个元素，i值无元素。
   首先求出数组C，Ci = 值小于等于i的元素数量，则当C[i-1] < i时，i及其以后无解。
   其次，令Ui等于从0~i每个值至少有一个所用的最少操作数量，则
             U[i-1], 当有元素的值为i
      Ui =  
             U[i-1] + i - k, 其中k是距离i最近的，有多个元素的值为k，这个k可以暴力维护，感觉不会到达平方
   Vi则是清空i值元素需要的最少操作数量，其实就是i值元素的数量
   令Bi为所求，则Bi = U[i-1] + Vi
   最后注意要longlong
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
int const SIZE = 140;
#else
int const SIZE = 210010;
#endif

int N;
int A[SIZE];
llt B[SIZE];
llt C[SIZE];

llt U[SIZE], V[SIZE];
int T[SIZE];

map<int, int> MM;

void proc(){
    auto it = MM.find(0);
	if(it == MM.end()){
		C[0] = V[0] = 0;
	}else{
		C[0] = V[0] = it->second;
	}
	U[0] = 0;
	int prek = -1;
	B[0] = V[0];
	T[0] = C[0];
	if(C[0]>1) prek = 0;

	for(int i=1;i<=N;++i){
        it = MM.find(i);
		if(it == MM.end()){
			C[i] = C[i-1] + 0;
		}else{
            C[i] = C[i-1] + it->second;
		}
	}

	for(int i=1;i<=N;++i){
		if(C[i-1]<i){
			fill(B+i, B+N+1, -1);
			break;
		}
        it = MM.find(i);
		if(it==MM.end()){
			T[i] = 0;
			V[i] = 0;
            while(T[prek]==1) --prek;
			--T[prek];
			U[i] = U[i-1] + i - prek;
			T[i] = 1;
		}else{
			T[i] = it->second;
			V[i] = it->second;
			U[i] = U[i-1];
            if(T[i]>1) prek = i;
		}
		B[i] = U[i-1] + V[i];
	}
	printf("%lld", B[0]);
	for(int i=1;i<=N;++i)printf(" %lld", B[i]);
	printf("\n");
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif    
    int nofkase = getUnsigned();
	while(nofkase--){
		MM.clear();
		N = getUnsigned();
		for(int i=0;i<N;++i) ++MM[A[i] = getUnsigned()];
		proc();
	}
    return 0;
}
