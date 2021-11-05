//成段修改RMQ 
#include <cstdio>
#include <climits>
#include <algorithm>
using namespace std;

#define SIZE 100005

#define lson(x) ( (x) << 1 )
#define rson(x) ( lson(x) | 1 )

int A[SIZE];//源数组，实际上可以不用 
int ST[SIZE<<2];//线段树的长度是源数组的4倍 
int Delay[SIZE<<2];
int N,M;

//信息上传,t表示节点，根据t的儿子计算t的信息 
void _pushUp(int t){
	ST[t] = max(ST[lson(t)],ST[rson(t)]);
} 

//延迟信息下传，t表示节点，子节点的极值与延迟信息要根据父节点的延迟计算更新 
void _pushDown(int t){
    if ( 0 == Delay[t] ) return ;
    int& x = Delay[t];
    Delay[lson(t)] += x;
    ST[lson(t)] += x;
    Delay[rson(t)] += x;
    ST[rson(t)] += x;  
    x = 0;   
}

//建树，t表示节点，[s,e]表示t所代表的区间 
void build(int t,int s,int e){
    Delay[t] = 0;
	if ( s == e ){
		scanf("%d",ST+t);
		return;
	}
	int mid = ( s + e ) >> 1;
	build(lson(t),s,mid);
	build(rson(t),mid+1,e);
	_pushUp(t);
}

//查询,t表示节点，[s,e]表示t所代表的区间
//[a,b]表示问题所求，即问[a,b]的区间最大值 
int query(int t,int s,int e,int a,int b){
	if ( a <= s && e <= b ) return ST[t];
	_pushDown(t);
	int mid = ( s + e ) >> 1;
	int ret = INT_MIN;
	if ( a <= mid ){
		int tmp = query(lson(t),s,mid,a,b);
		if ( ret < tmp ) ret = tmp;
	}
	if ( mid < b ){
		int tmp = query(rson(t),mid+1,e,a,b);
		if ( ret < tmp ) ret = tmp;
	} 
	return ret;
} 

//成段修改,t表示节点，[s,e]为t所代表的区间
//将源数组第[a,b]区间的所有数增加delta 
void modify(int t,int s,int e,int a,int b,int delta){
	if ( a <= s && e <= b ){
		ST[t] += delta;
		Delay[t] += delta;
		return;
	}
	_pushDown(t);
	int mid = ( s + e ) >> 1;
	if ( a <= mid ) modify(lson(t),s,mid,a,b,delta);
	if ( mid < b ) modify(rson(t),mid+1,e,a,b,delta);
	_pushUp(t);
}

bool read(){
	if ( EOF == scanf("%d%d",&N,&M) ) return false;
	build(1,1,N);
	return true;
}

int main(){
	for(int kase=1;read();++kase){
		printf("Case %d:\n",kase);
		for(int i=0;i<M;++i){
			int a,b;
			char cmd[3];
			scanf("%s%d%d",cmd,&a,&b);
			if ( 'Q' == *cmd ){
			    printf("%d\n",query(1,1,N,a,b));
			}else{
                int delta;
                scanf("%d",&delta);
			    modify(1,1,N,a,b,delta);
            }
		}
	}
	return 0;
}
