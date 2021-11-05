#include <cstdio>
#include <algorithm>
#include <numeric>
using namespace std;

#define SIZE 2502
int Father[SIZE];//并查集数组
//初始化
void init(int n){for(int i=0;i<n;Father[i]=i++);}
//查找
int find(int x){return x == Father[x] ? x : Father[x] = find(Father[x]);}
//合并
void unite(int x,int y){x=find(x),y=find(y),Father[y]=x;}

//标识数组，Flagij表示字母i在j方向有出口，上下左右
int Flag[11][4] = {
   1,0,1,0,
   1,0,0,1,
   0,1,1,0,
   0,1,0,1,
   1,1,0,0,
   0,0,1,1,
   1,0,1,1,
   1,1,1,0,
   0,1,1,1,
   1,1,0,1,
   1,1,1,1
};
int OPOS[] = {1,0,3,2};//相对位置
//判断a在b的pos位置是否联通
bool isCon(char a,char b,int pos){
    return  Flag[a-'A'][OPOS[pos]] && Flag[b-'A'][pos]; 
}

char S[52][52];
int Ans[SIZE] = {0};
int main(){
	int n,m;
	while( scanf("%d%d",&m,&n) ){
		if ( n < 0 && m < 0 ) return 0;
		for(int i=0;i<m;++i)scanf("%s",S[i]);

		init(n*m);
		
		//对每一格看是否与右、下联通
		for(int i=0;i<m-1;++i)for(int j=0;j<n-1;++j){
			if(isCon(S[i][j],S[i][j+1],2))unite(i*n+j,i*n+j+1);
			if(isCon(S[i][j],S[i+1][j],0))unite(i*n+j,i*n+n+j);
		}

		//最后一行只看右
		for(int i=0;i<n-1;++i)if(isCon(S[m-1][i],S[m-1][i+1],2))
			unite((m-1)*n+i,(m-1)*n+i+1);

        //最后一列
		for(int i=0;i<m-1;++i)if(isCon(S[i][n-1],S[i+1][n-1],0))
			unite(i*n+n-1,i*n+n+n-1);

        fill(Ans,Ans+n*m,0);
		for(int i=0;i<n*m;++i)Ans[find(i)] = 1;
		printf("%d\n",accumulate(Ans,Ans+n*m,0));
	}
	return 0;
}