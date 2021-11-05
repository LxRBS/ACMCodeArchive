#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
int W,H;
char B[22][22];
int DX[] = {-1,1,0,0};//上下左右
int DY[] = {0,0,-1,1};
bool isValid(int x,int y){return x >= 0 && x < H && y >= 0 && y < W;}
int bfs(int x,int y){
	int ret = 0;
	vector<int>  q;
    q.push_back(x*W+y);
    B[x][y] = '#';

	while( !q.empty() ){
        int t = q.back();
		q.pop_back();
        
		++ret;
		int x = t / W;
		int y = t % W;
		

		for(int i=0;i<4;++i){
			int dx = x + DX[i];
			int dy = y + DY[i];

			if ( !isValid(dx,dy) || B[dx][dy] != '.' ) continue;

			q.push_back(dx*W+dy);
			B[dx][dy] = '#';
		}
	}
	return ret;
}
int main(){
	while( scanf("%d%d",&W,&H) && W && H ){
        for(int i=0;i<H;++i)scanf("%s",B[i]);
		//查找起点
        int x,y;
		for(x=0;x<H;++x){
			y = find(B[x],B[x]+W,'@') - B[x];
			if ( y != W ) break;
		}

		//搜索
		printf("%d\n",bfs(x,y));
	}
	return 0;
}