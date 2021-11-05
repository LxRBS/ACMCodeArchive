#include <cstdio>

using namespace std;

#define SIZE 101

int Ans;
char Table[SIZE][SIZE];

//深度优先搜索
void findTree(int m,int n,int icoor,int jcoor,bool flag[][SIZE]){
    if ( icoor < 0 || icoor >= m ) return;
	if ( jcoor < 0 || jcoor >= n ) return;
	if ( flag[icoor][jcoor] ) return;

	flag[icoor][jcoor] = true;

	if ( '@' != Table[icoor][jcoor] ) return;

	//搜索8邻域
	findTree(m,n,icoor-1,jcoor-1,flag);
	findTree(m,n,icoor-1,jcoor,flag);
	findTree(m,n,icoor-1,jcoor+1,flag);
	findTree(m,n,icoor,jcoor+1,flag);
	findTree(m,n,icoor+1,jcoor+1,flag);
	findTree(m,n,icoor+1,jcoor,flag);
	findTree(m,n,icoor+1,jcoor-1,flag);
	findTree(m,n,icoor,jcoor-1,flag);

    return ;
}

void proc(int m,int n){
	bool flag[SIZE][SIZE] = {0};

	for(int i=0;i<m;i++)for(int j=0;j<n;j++)if(!flag[i][j]){
		if ( '@' == Table[i][j] ){
			Ans++;
			findTree(m,n,i,j,flag);
		}
	}
}

int main(){
    int t;
	scanf("%d",&t);

	while(t--){
        int m,n;
		scanf("%d%d%*c",&m,&n);

		for(int i=0;i<m;i++)scanf("%s",Table[i]);

		Ans = 0;
		proc(m,n);
		printf("%d\n",Ans);
	}

	return 0;
}