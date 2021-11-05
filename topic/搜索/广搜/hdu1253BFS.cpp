#include <cstdio>
#include <queue>
#include <utility>
using namespace std;

int D[50][50][50];
int A,B,C,T;

bool isValid(int x,int y,int z){return x >= 0 && x < A && y >= 0 && y < B && z >= 0 && z < C;}
inline int tr(int x,int y,int z){return (x<<12)|(y<<6)|z;}
inline int getX(int idx){return (idx&0x3F000)>>12;}
inline int getY(int idx){return (idx&0xFC0)>>6;}
inline int getZ(int idx){return idx&0x3F;}

typedef pair<int,int> pii;

int DX[] = {-1,1,0,0,0,0};
int DY[] = {0,0,-1,1,0,0};
int DZ[] = {0,0,0,0,-1,1};

int bfs(){
	if ( 1 == A && 1 == B && 1 == C ) return 0;

    queue<pii> q;
	q.push(pii(0,0));
	D[0][0][0] = 1;

	while( !q.empty() ){
        int coor = q.front().first;
		int step = q.front().second;
        q.pop();
		if ( step >= T ) continue;

		int x = getX(coor);
		int y = getY(coor);
		int z = getZ(coor);

		for(int i=0;i<6;++i){
			int dx = x + DX[i];
			int dy = y + DY[i];
			int dz = z + DZ[i];

			if ( A - 1 == dx && B - 1 == dy && C - 1 == dz ) return step + 1;

			if ( !isValid(dx,dy,dz) || 1 == D[dx][dy][dz] ) continue;

			q.push(pii(tr(dx,dy,dz),step+1));
			D[dx][dy][dz] = 1;
		}
	}

	return -1;
}
int main(){
	int nofkase;
	scanf("%d",&nofkase);
	while(nofkase--){
		scanf("%d%d%d%d",&A,&B,&C,&T);
		for(int i=0;i<A;++i)for(int j=0;j<B;++j)for(int k=0;k<C;++k)
			scanf("%d",D[i][j]+k);
		if ( 1 == D[A-1][B-1][C-1] || A + B + C - 3 > T ) printf("-1\n");
		else printf("%d\n",bfs());
	}
	return 0;
}