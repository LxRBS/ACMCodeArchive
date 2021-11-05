/*
给定N个区间[s,e]。
如果a区间能够真包含b区间，则称a比b强壮。
对每一个区间，问比其强壮的区间有多少个
*/
#include <cstdio>
#include <algorithm>
using namespace std;

#define SIZE 100005

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

struct _t{
	int s,e;
	int idx;
}Node[SIZE];
bool operator < (_t const&l,_t const&r){
	if ( l.e != r.e ) return l.e > r.e;
	return l.s < r.s;
}

int N;
int Ans[SIZE];
int main() {
	while ( scanf("%d",&N) && N ){
		for(int i=0;i<N;++i){
            scanf("%d%d",&Node[i].s,&Node[i].e);
            ++Node[i].s;
            Node[i].idx = i;
		}
		sort(Node,Node+N);
		fill(C,C+SIZE,0);

		Ans[Node[0].idx] = sum(Node[0].s);
		update(Node[0].s,1,SIZE);
		for(int i=1;i<N;++i){
			if ( Node[i].s == Node[i-1].s && Node[i].e == Node[i-1].e )
				Ans[Node[i].idx] = Ans[Node[i-1].idx];
			else
                Ans[Node[i].idx] = sum(Node[i].s);
            update(Node[i].s,1,SIZE);
		}

		for(int i=0;i<N-1;++i)printf("%d ",Ans[i]);
		printf("%d\n",Ans[N-1]);
	}
	return 0;
}
