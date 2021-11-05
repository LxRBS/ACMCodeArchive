#include <cstdio>
#include <cstring>
#define SIZE 55480

struct node_t{
	node_t* child[10];//10个儿子
	bool flag;//用于标记是否为单词
}Node[SIZE];
int toUsed;
//插入的同时即可查找
bool insertfind(char const word[]){
	int i=0,sn;
    node_t* loc = Node;
	while( word[i] ){
		sn = word[i] - '0';
		if ( !loc->child[sn] )loc->child[sn] = Node + toUsed ++;
		loc = loc->child[sn];
	    ++i;
		if ( loc->flag ) return true;
	}
	//当前单词插入完成，设置标记位
	loc->flag = true;
	
	//检查后续 
	for(i=0;i<10;i++)if(loc->child[i])
		return true;
	return false;
}

int main(){
    int nofkase;
	scanf("%d",&nofkase);
	while(nofkase--){
		memset(Node,0,sizeof(Node));
		toUsed = 1;
		bool flag = false;
		int n;
        scanf("%d",&n);
		while(n--){
			char s[12];
            scanf("%s",s);
            if ( !flag )flag = insertfind(s);
		}
		printf(flag?"NO\n":"YES\n");
	}
	return 0;
}
