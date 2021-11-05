#include <cstdio>
#include <vector>

#define SIZE 901

int Father[SIZE];

char Flag[SIZE];
char isRoot[SIZE];

int Ans[SIZE];

struct node_t{
    int son_cnt;
	int son[SIZE];
}Node[SIZE];

int Root_Sn;

std::vector<int> Question[SIZE];

int find(int x){
    int k = Father[x];
	return k == x ? k : Father[x] = find(k);
}

void LCA(int u){
	int i,v;

	Father[u] = u;

	for(i=0;i<Node[u].son_cnt;i++){
		v = Node[u].son[i];
		
		LCA(v);

		//下面这句就是合并
		Father[v] = u;

	}

	Flag[u] = 1;

	for(i=0;i<Question[u].size();i++){
		v = Question[u][i];
		if ( Flag[v] ){
			int ans = Father[find(v)];
			Ans[ans]++;
		}
	}

}

int main(){
	int i,j,n,child;
	char ch;
	int numofq;
	int a,b;

	while( EOF != scanf("%d",&n) ){
		memset(isRoot,0,sizeof(isRoot));

		for(i=0;i<n;i++){
            scanf("%d%c%c",&child,&ch,&ch);
			scanf("%d%c",&Node[child].son_cnt,&ch);
			for(j=0;j<Node[child].son_cnt;j++){
				scanf("%d",&Node[child].son[j]);
				isRoot[Node[child].son[j]] = 1;
			}			
		}

		for(i=1;i<=n;i++)if( 0 == isRoot[i] ){
			Root_Sn = i;
			break;
		}

		for(i=1;i<=n;i++)
			Question[i].clear();
		memset(Flag,0,sizeof(Flag));
		memset(Ans,0,sizeof(Ans));
		memset(Father,0,sizeof(Father));

		scanf("%d",&numofq);
		for(i=0;i<numofq;i++){
            while ( '(' != getchar() );
			
			scanf("%d%d",&a,&b);

			Question[a].push_back(b);
			Question[b].push_back(a);
		}

		//把最后一个右括号吃掉
		scanf("%c",&ch);

		LCA(Root_Sn);

		for(i=1;i<=n;i++)if(0!=Ans[i]){
			printf("%d:%d\n",i,Ans[i]);
		}

	}
	return 0;
}