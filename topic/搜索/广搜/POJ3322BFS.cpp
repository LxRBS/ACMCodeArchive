#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;

char B[505][505];
int R,C;

bool read(){
	scanf("%d%d",&R,&C);
	if ( 0 == R && 0 == C ) return false;
	for(int i=0;i<R;++i)scanf("%s",B[i]);
	return true;
}
#define LI 0    //立
#define HENG 1  //横
#define SHU 2   //竖

int const LIDR[] = {-2,1,0,0}; //上下左右
int const LIDC[] = {0,0,-2,1};
int const LIDR2[] = {-1,2,0,0};
int const LIDC2[] = {0,0,-1,2};
int const LISTATUS[] = {SHU,SHU,HENG,HENG};

int const HENGDR[] = {-1,1,0,0};
int const HENGDC[] = {0,0,-1,2};
int const HENGDR2[] = {-1,1};
int const HENGDC2[] = {1,1};

int const SHUDR[] = {-1,2,0,0};
int const SHUDC[] = {0,0,-1,1};
int const SHUDR2[] = {-1000,-1000,1,1};
int const SHUDC2[] = {-1000,-1000,-1,1};

bool F[505][505][3];
struct _t{
	int r,c,step;
	int status;
	_t(int rr=0,int cc=0,int stp=0,int sts=0):
		r(rr),c(cc),step(stp),status(sts){}
};
//找起点
_t findStart(){
	for(int i=1;i<R;++i){
		for(int j=1;j<C;++j){
			if ( 'X' != B[i][j] ) continue;
            if ( 'X' == B[i][j+1] ){
            	F[i][j][HENG] = true;
            	return _t(i,j,0,HENG);
            }
            if ( 'X' == B[i+1][j] ){
            	F[i][j][SHU] = true;
            	return _t(i,j,0,SHU);
            }
            F[i][j][LI] = true;
            return _t(i,j,0,LI);
		}
	}
}

void disp(queue<_t> q){
	printf("Q:\n");
    while( !q.empty() ){
    	_t u = q.front();
    	printf("(%d,%d),%d,%d\n",u.r,u.c,u.step,u.status);
    	q.pop();
    }
}

void proc(){
    memset(F,0,sizeof(F));
    queue<_t> q;
    q.push(findStart());

    while( !q.empty() ){
    	//disp(q);

        _t u = q.front();
        q.pop();

        if ( LI == u.status ){
            for(int i=0;i<4;++i){//上下左右
            	int nr = u.r + LIDR[i];
            	int nc = u.c + LIDC[i];
            	int nr2 = u.r + LIDR2[i];
            	int nc2 = u.c + LIDC2[i];
            	int status = LISTATUS[i];

            	if ( '#' == B[nr][nc] || '#' == B[nr2][nc2]
				   || F[nr][nc][status] ) continue;

            	F[nr][nc][status] = true;
            	q.push(_t(nr,nc,u.step+1,status));
            }
        }else if ( HENG == u.status ){
        	for(int i=2;i<4;++i){//左右
        		int nr = u.r + HENGDR[i];
        		int nc = u.c + HENGDC[i];
        		int status = LI;

        		if ( 'O' == B[nr][nc] ){
        			printf("%d\n",u.step+1);
        			return;
        		}

        		if ( '#' == B[nr][nc] || 'E' == B[nr][nc]
			      || F[nr][nc][status] ) continue;

        		F[nr][nc][status] = true;
        		q.push(_t(nr,nc,u.step+1,status));
        	}
            for(int i=0;i<2;++i){//上下
            	int nr = u.r + HENGDR[i];
            	int nc = u.c + HENGDC[i];
            	int nr2 = u.r + HENGDR2[i];
            	int nc2 = u.c + HENGDC2[i];
            	int status = HENG;

            	if ( '#' == B[nr][nc] || '#' == B[nr2][nc2]
            	   || F[nr][nc][status] ) continue;

            	F[nr][nc][status] = true;
            	q.push(_t(nr,nc,u.step+1,status));
            }
        }else{//SHU
            for(int i=0;i<2;++i){//上下
            	int nr = u.r + SHUDR[i];
            	int nc = u.c + SHUDC[i];
            	int status = LI;

        		if ( 'O' == B[nr][nc] ){
        			printf("%d\n",u.step+1);
        			return;
        		}

            	if ( '#' == B[nr][nc] || 'E' == B[nr][nc]
            	   || F[nr][nc][status] ) continue;

            	F[nr][nc][status] = true;
            	q.push(_t(nr,nc,u.step+1,status));
            }

        	for(int i=2;i<4;++i){//左右
        		int nr = u.r + SHUDR[i];
        		int nc = u.c + SHUDC[i];
        		int nr2 = u.r + SHUDR2[i];
        		int nc2 = u.c + SHUDC2[i];
        		int status = SHU;

        		if ( '#' == B[nr][nc] || '#' == B[nr2][nc2]
			      || F[nr][nc][status] ) continue;

        		F[nr][nc][status] = true;
        		q.push(_t(nr,nc,u.step+1,status));
        	}

        }
    }

    printf("Impossible\n");
    return;
}
int main() {
	while( read() ) proc();
	return 0;
}
