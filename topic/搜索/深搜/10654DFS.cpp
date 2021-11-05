#include <cstdio>
typedef int llt;
char W[12],X[12];
llt A[] = {
	1,10,100,1000,10000,100000,1000000,10000000,
    100000000,1000000000
};
inline bool read(){
	scanf("%s",W);
	if ( '#' == *W ) return false;
	scanf("%s",X);
	return true;
}
//depth表示搜索深度，cnt表示问号的剩余个数
llt dfs(int depth,int cnt,int const length){
	if ( length == depth ) return 0;
	
	if ( '?' != W[depth] ){
	    if ( W[depth] > X[depth] ) return A[cnt];
	    if ( W[depth] < X[depth] ) return 0;
	    return dfs(depth+1,cnt,length);
	}

	int ret = '9' - X[depth];
	return ret * A[cnt-1] + dfs(depth+1,cnt-1,length);
}

inline void solve(){
	int cnt = 0, len = 0;
	for(char*p=W;*p;++p){
		++len;
		if ( '?' == *p ) ++cnt;
	}
    printf("%d\n",dfs(0,cnt,len));
}

int main(){
	while( read() ) solve();
	return 0;
}