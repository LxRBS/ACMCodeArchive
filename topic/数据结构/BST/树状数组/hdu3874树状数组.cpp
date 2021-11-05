//求区间和，但重复的数不计入和
//使用离线算法，相当于单点更新成段求和，所以使用树状数组 
#include <cstdio>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

typedef long long llt;
int const SIZE = 50005;

int N,M;
int A[SIZE];
llt C[SIZE];//树状数组 

inline int lowbit(int x){ return x & (-x); }

//求[1,n]的区间和 
llt query(int n){
    llt sum = 0LL;
    while( n > 0 ){
        sum += C[n];
        n = n - lowbit(n);
    } 
    return sum;
}

//求[s,e]的区间和 
inline llt query(int s,int e){
	return query(e) - query(s-1);
}

//单点修改，将第idx个位置增加delta,
//SIZE为元素个数, 数组的有效下标为[1,n] 
void modify(int idx,int delta,int n){
    while( idx <= n ){
        C[idx] += delta;
        idx += lowbit(idx);
    }
}

struct _t{
	int l,r;//区间[l,r] 
}Q[200005];

int Pos[1000006];//Pos[i]表示i出现的最后位置 
llt Ans[200005];
map<int,vector<int> > Map;
map<int,vector<int> >::const_iterator It;

bool read(){
	scanf("%d",&N);
	for(int i=1;i<=N;++i)scanf("%d",A+i);

	Map.clear();
	fill(Pos,Pos+1000006,0);
	fill(C,C+N+1,0);

	scanf("%d",&M);
	for(int i=0;i<M;++i){
		scanf("%d%d",&Q[i].l,&Q[i].r);
		Map[Q[i].r].push_back(i);
	}
	return true;
}
void proc(){
	//从左到右将源数组的数插入树状数组 
	for(int i=1;i<=N;++i){
		int lastpos = Pos[A[i]];
		if ( lastpos ) modify(lastpos,-A[i],N);
		modify(i,A[i],N);
		Pos[A[i]] = i;
		It = Map.find(i);
		if ( Map.end() == It ) continue;
		vector<int>const& v = It->second;
		for(unsigned j=0;j<v.size();++j){
			int idx = v[j];
			int s = Q[idx].l;
			int e = Q[idx].r;
			Ans[idx] = query(s,e);
		}
	}
}
int main(){
	int t;
	scanf("%d",&t);
	while(t--){
		read();
		proc();
        for(int i=0;i<M;++i)printf("%I64d\n",Ans[i]);
	}
	return 0;	
}
