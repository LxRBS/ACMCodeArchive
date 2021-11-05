//状态及状态转换有点意思 
#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;

char A[12][12];
int N,M,P;
int StartR,StartC;
void read(){
	scanf("%d%d%d",&N,&M,&P);
	for(int i=0;i<N;++i){
		scanf("%s",A[i]);
        for(int j=0;j<M;++j)if('@'==A[i][j])StartR=i,StartC=j;
	}
	return;
}
struct _t{
    int r,c,t;//行、列、耗时
    int b;//当前所处的按钮
    _t(int a1=0,int a2=0,int a3=0,int a4=0):r(a1),c(a2),t(a3),b(a4){}
};

void dispQueue(queue<_t> q){
	printf("Q: %d\n",q.size());
	while( !q.empty() ){
        _t u = q.front();
        printf("(%d,%d)(time:%d)(%d)\n",u.r,u.c,u.t,u.b);
        q.pop();
	}
}
int const DR[] = {0,0,-1,1};
int const DC[] = {-1,1,0,0};
inline bool isNotValid(int r,int c){
	return r < 0 || r >= N || c < 0 || c >= M || '*' == A[r][c];
}
bool F[10][10][4];//行、列、button可决定状态
int bfs(){
    memset(F,0,sizeof(F));

    queue<_t> q;
    q.push(_t(StartR,StartC,0,0));
    F[StartR][StartC][0] = true;

    while( !q.empty() ){
    	//dispQueue(q);

    	_t u = q.front();
    	q.pop();

    	int nr,nc,nb;
    	//如果到达了panel变化的前一步
    	if ( P - 1 == u.t % P ){
            //等待，这一步相当于button减1
    		nb = u.b - 1;
    		if ( nb < 0 ) nb += 4;
    		if ( !F[u.r][u.c][nb] )
    			q.push(_t(u.r,u.c,u.t+1,nb)),F[u.r][u.c][nb] = true;

    	    //按下
    		nr = u.r + DR[u.b];
    		nc = u.c + DC[u.b];
    		if ( isNotValid(nr,nc) ) goto L1;
    		if ( '$' == A[nr][nc] ) return u.t + 1;
            if ( !F[nr][nc][nb] )//这里是nb
            	q.push(_t(nr,nc,u.t+1,nb)),F[nr][nc][nb]=true;

    		L1:
            //右移不需要
			//左移
			nb = u.b - 2;
			if ( nb < 0 ) nb += 4;
    		if ( !F[u.r][u.c][nb] )
    			q.push(_t(u.r,u.c,u.t+1,nb)),F[u.r][u.c][nb] = true;

    	}else{//仍然是三种可能
            //按下
    		nr = u.r + DR[u.b];
    		nc = u.c + DC[u.b];
    		if ( isNotValid(nr,nc) ) goto L2;
    		if ( '$' == A[nr][nc] ) return u.t + 1;
            if ( !F[nr][nc][u.b] )
            	q.push(_t(nr,nc,u.t+1,u.b)),F[nr][nc][u.b]=true;

            L2:
			//左移
			nb = u.b - 1;
			if ( nb < 0 ) nb += 4;
    		if ( !F[u.r][u.c][nb] )
    			q.push(_t(u.r,u.c,u.t+1,nb)),F[u.r][u.c][nb] = true;

    		//右移
    		nb = ( u.b + 1 ) % 4;
    		if ( !F[u.r][u.c][nb] )
    			q.push(_t(u.r,u.c,u.t+1,nb)),F[u.r][u.c][nb] = true;

    	}
    }
    return -1;
}
int main() {
	int nofkase;
	scanf("%d",&nofkase);
	while( nofkase-- ){
		read();
		int t = bfs();
		if ( -1 == t ) printf("YouBadbad\n");
		else printf("%d\n",t);
	}
	return 0;
}
