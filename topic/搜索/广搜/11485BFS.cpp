//数据比较弱，搜索可过 
#include <cstdio>
#include <queue>
#include <algorithm>
using namespace std;

struct _t{
	int s,e;
}A[22];
bool operator < (_t const&l,_t const&r){
	if ( l.s != r.s ) return l.s < r.s;
	return l.e < r.e;
}
int getTime(int idx){
	int r = 0;
	for(int i=A[idx].s;i<A[idx].e;++i)
		r |= 1<<i;
	return r;
}
bool isNotValid(int totalTime,int idx){
    for(int i=A[idx].s;i<A[idx].e;++i)
    	if ( totalTime & ( 1 << i ) )
    		return true;
    return false;
}
int read(){
    for(int i=0;;++i){
        int s,e;
        scanf("%d%d",&s,&e);
        if ( 0 == s && 0 == e ) return i;
        A[i].s = s;
        A[i].e = e;
    }
    return 0;
}

struct _t2{
    int ans;
    int st;
    int time;
    _t2(int a=0,int s=0,int t=0):ans(a),st(s),time(t){}
};
bool S[1<<21];
int const TimeBound = ( 1 << 10 ) - 1;
int bfs(int n){

	fill(S,S+(1<<n),false);

    queue<_t2> q;
    for(int i=0;i<n;++i){
    	q.push(_t2(1,1<<i,getTime(i)));
    	S[1<<i] = true;
    }

    int r = 1;
    while(!q.empty()){
        _t2 u = q.front();
        q.pop();

        if ( u.ans > r ) r = u.ans;

        for(int i=0;i<n;++i){
            int st = 1 << i;
            if ( ( u.st & st ) || S[u.st|st] || isNotValid(u.time,i) ) continue;
            q.push(_t2(u.ans+1,u.st|st,u.time|getTime(i)));
            S[u.st|st] = true;
        }
    }
    return r;
}
int main(){
    int nofkase;
    scanf("%d",&nofkase);
    while(nofkase--){
        int n = read();
        sort(A,A+n);
        printf("%d\n",bfs(n));
    }
    return 0;
}
