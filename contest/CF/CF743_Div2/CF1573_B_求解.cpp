/**
 * �������飬A��1,3,5,...,2n-1
 * B��2,4,6,...,2n
 * ��ֻ�����ڸ��������ڲ���������������
 * ������Ҫ���ٲ�ʹ��A������ֵ���С��B����
 * ֻ��Ҫ��ÿһ��bi���ҵ���һ��С������aj��Ȼ�����i+j-2����Сֵ����
 * ֱ�Ӽ�����N^2�ġ�������״�����϶��֣�ͬʱҪ�仯����˳��
 * ��i��N��1�������ӦB��������2i��A��������2i-1
 * ��ÿһ��i��ȡ����PosB�����ҵ���һ������С��PosA������PosBi+PosAi-2����Сֵ����
 * ��P����ΪPosA�����ǰ׺�ͣ���i-Pi��Ȼ�ǲ����ģ�ֻҪ�ҵ���һ��Ϊ1��λ�ü��ɡ� 
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

#ifndef ONLINE_JUDGE
int const SIZE = 10;
#else 
int const SIZE = 100100;
#endif

int N, NN;
int A[SIZE], B[SIZE], C[SIZE];
int PosA[SIZE], PosB[SIZE];
int Flag[SIZE];

inline int lowbit(int x){return x & -x;}
void modify(int x){for(;x<=N;x+=lowbit(x))C[x] += 1;};
int query(int x){int ans=0;for(;x;x-=lowbit(x))ans+=C[x];return ans;}

int f(){
    int left = 1, right = N, mid;
    do{
         mid = (left + right) >> 1;
         if(query(mid) == mid) left = mid + 1;
         else right = mid - 1;
    }while(left<=right);
    return left;
}

int proc(){
    fill(C, C+N+1, 0);
    int ans = N - 1;
    for(int t,i=N;i;--i){
        t = f();
        ans = min(ans, PosB[i]-1+t-1);
        modify(PosA[i]);
    }
    return ans;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    int nofkase = getUnsigned();
	while(nofkase--){
        N = getUnsigned();
		for(int i=1;i<=N;++i)PosA[((A[i] = getUnsigned())+1)>>1] = i;
		for(int i=1;i<=N;++i)PosB[(B[i] = getUnsigned())>>1] = i;
		printf("%d\n", proc());
	}
	return 0;
}