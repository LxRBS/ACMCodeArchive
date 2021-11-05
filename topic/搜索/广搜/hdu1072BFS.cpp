#include <queue>
#include <cstdio>
using namespace std;

//�Թ�
int A[8][8];
int Row,Col;
//������
int StartR,StartC;

int DR[] = {0,0,-1,1};
int DC[] = {1,-1,0,0};

struct _t{
    int r,c;//����
	int left;//ʣ��ʱ��
	int total;//��ʱ��
	_t(int x=0,int y=0,int z=0,int w=0):r(x),c(y),left(z),total(w){}
};

inline bool isNotValid(int r,int c){
	return r < 0 || c < 0 || r >= Row || c >= Col;
}

int bfs(){
	queue<_t> q;
	q.push(_t(StartR,StartC,6));

	while( !q.empty() ){
		_t u = q.front();
		q.pop();

		for(int i=0;i<4;++i){
			int dr = u.r + DR[i];
			int dc = u.c + DC[i];

			//���Ϸ����߷�
			if ( isNotValid(dr,dc) || 0 == A[dr][dc] || 1 == u.left
			  || ( 2 == u.left && 3 > A[dr][dc] ) ) continue;

			//����
			if ( 3 == A[dr][dc] && u.left > 1 ) return u.total+1;

			//��һ��
			if ( 4 == A[dr][dc] ) A[dr][dc]=0,q.push(_t(dr,dc,6,u.total+1));
			else q.push(_t(dr,dc,u.left-1,u.total+1));
		}
		
	}

	return -1;
}

int main(){
	int nofkase;
	scanf("%d",&nofkase);
	while(nofkase--){
		scanf("%d%d",&Row,&Col);
		for(int r=0;r<Row;++r)for(int c=0;c<Col;++c){
			scanf("%d",A[r]+c);
			if( 2 == A[r][c] ) StartR=r,StartC=c;			
		}

		int ret = bfs();
		printf("%d\n",ret);
	}
	return 0;
}