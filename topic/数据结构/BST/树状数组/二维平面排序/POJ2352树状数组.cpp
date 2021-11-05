/*
给定N个点。
每个点的左下方的点的数量定义为其level，
统计每个level的点的数量。
输入按照y升序给出，y相等则x升序。
*/
#include <cstdio>
#include <algorithm>
using namespace std;

#define SIZE 32002

//树状数组
int C[SIZE] = {0};

//源数组,Ai表示坐标为i的个数
int A[SIZE] = {0};

//计算x的二进制位的最低位1代表的数值
int lowbit(int x){
    return x & ( x ^ ( x - 1 ) );
}

//更新，将第idx节点值加上v
//树状数组总长度为n，下标范围从1到n
void update(int idx,int v,int n){
	while( idx <= n ){
	    C[idx] += v;
		idx += lowbit(idx);
	}
}

//对前x项求和
int sum(int x){
    int s = 0;
	while( x > 0 ){
	    s += C[x];
		x -= lowbit(x);
	}
    return s;
}

int N;
int Ans[SIZE];
int main() {
	while ( EOF != scanf("%d",&N) ){
		fill(Ans,Ans+N,0);
		fill(C,C+SIZE,0);

        for(int i=0;i<N;++i){
        	int x,y;
        	scanf("%d%d",&x,&y);
            ++x;
            ++Ans[sum(x)];
            update(x,1,SIZE);
        }

        for(int i=0;i<N;++i)printf("%d\n",Ans[i]);
	}
	return 0;
}
