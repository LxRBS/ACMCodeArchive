//Kuhn-Munkres算法，二分图最优匹配（最小权值），slack优化
#include <cstdio>
#include <algorithm>
using namespace std;
#define SIZE 25
typedef int weight_t;

int N;

weight_t G[SIZE][SIZE];//二分图矩阵
int Link[SIZE];//Link[i]-i表示A、B中匹配的节点
bool FA[SIZE],FB[SIZE];//记录对应节点是否在增广树上

weight_t LabelA[SIZE];
weight_t LabelB[SIZE];//标号
weight_t Slack[SIZE];//B中节点可松弛的最小值

//dfs实现匈牙利算法，node为A中的节点
//返回值为是否存在增广路
bool dfs(int node){
	FA[node] = true;
	for(int i=0;i<N;++i){
		//如果Bi已在增广路
		if ( FB[i] ) continue;
			
		//如果node-i之间有存在边
		if ( LabelA[node]+LabelB[i] == G[node][i] ){
			FB[i] = true;

		    //如果找到增广路
		    if ( -1 == Link[i] || dfs(Link[i]) ){
			    Link[i] = node;
			    return true;
		    }
		}else{
		    //更新Slack
		    Slack[i] = min(Slack[i],LabelA[node]+LabelB[i]-G[node][i]);
		}
	}
	return false;
}


//KM算法最优匹配，返回最大权值和
int KM(){
	//初始化标号，LA赋关联边的最大权值，LB赋0
	fill(LabelA,LabelA+N,0);
	fill(LabelB,LabelB+N,0);
	for(int i=0;i<N;++i)for(int j=0;j<N;++j)
			LabelA[i] = max(LabelA[i],G[i][j]);
	
	//对N个点进行匹配
	for(int i=0;i<N;++i){
		fill(Slack,Slack+N,INT_MAX);

		while(1){
			fill(FA,FA+N,false);
			fill(FB,FB+N,false);

			//匹配成功
			if ( dfs(i) ) break;

			//查找顶标的可行变动值
			weight_t delta = INT_MAX;
			for(int j=0;j<N;++j)if(!FB[j]){
				delta = min(delta,Slack[j]);
			}
			//更新顶标
			for(int j=0;j<N;++j){
				if ( FA[j] ) LabelA[j] -= delta;
				if ( FB[j] ) LabelB[j] += delta;
				else Slack[j] -= delta;
			}
		}
	}

	//返回结果
	int ret = 0;
	for(int i=0;i<N;++i)
		ret += G[Link[i]][i];
	return ret;
}

int main(){
	while( EOF != scanf("%d",&N) ){
		for(int i=0;i<N;++i){
			for(int j=0;j<N;++j){
                int x;
				scanf("%d",&x);
				G[i][j] = -x;
			}
		}

		fill(Link,Link+N,-1);
		printf("%d\n",-KM());
	}
	return 0;
}
