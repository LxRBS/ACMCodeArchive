#include <cstdio>
#include <cstring>
#define SIZE 505

int Father[SIZE] = {0};
bool IsNot[SIZE] = {false};

void init(int n){
	for(int i=1;i<=n;++i)Father[i]=i;
	memset(IsNot,0,sizeof(IsNot));
}
int find(int x){
	return x == Father[x] ? x : Father[x] = find(Father[x]);
}
void unite(int x,int y){
    int xx = find(x);
    int yy = find(y);
    Father[yy] = xx;
    if ( xx == yy || IsNot[yy] )//说明这一块不是树
        IsNot[xx] = true;
}

int N,M;
bool read(){
	scanf("%d%d",&N,&M);
	if ( 0 == N && 0 == M ) return false;
	init(N);
    for(int i=0;i<M;++i){
    	int a,b;
    	scanf("%d%d",&a,&b);
    	unite(a,b);
    }
    return true;
}
char const A[2][30] = {
	"No trees.",
	"There is one tree."
};
int main(){
	for(int kase=1;read();++kase){
        int ret = 0;
        for(int i=1;i<=N;++i){
        	int x = find(i);
        	if ( !IsNot[x] ) ++ret, IsNot[x] = true;
        }
        printf("Case %d: ",kase);
        if ( ret <= 1 ) printf("%s\n",A[ret]);
        else printf("A forest of %d trees.\n",ret);
	}
	return 0;
}
