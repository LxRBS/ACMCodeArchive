#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;

#define  SIZE 1000001

/*trie树，node[0]是root*/
struct node_t{
    node_t* child[26];
	node_t* failer;
	int cnt;//表示该单词在字典中出现的次数
}Node[10000*51];
int toUsed = 1;

/*建立trie树*/
void insert(char const word[]){
    node_t* loc = Node;
	for(int i=0;word[i];++i){
		int sn = word[i] - 'a' ;
        if ( !loc->child[sn] ){
        	memset(Node+toUsed,0,sizeof(node_t));
        	loc->child[sn] = Node + toUsed ++;
        }
		loc = loc->child[sn];
	}
	++loc->cnt;
}
/*建立失败指针*/
void buildAC(){
	Node[0].failer = NULL;/*root的failer为空*/
    queue<node_t*> q;
	for(int i=0;i<26;++i){//一级子节点的失败指针指向根
		node_t* p = Node[0].child[i];
		if ( p ){
            p->failer = Node;
            q.push(p);
		}
	}
	while( !q.empty() ){
		node_t* father = q.front();        /*取出1个节点*/
		q.pop();
		for(int i=0;i<26;++i){
			node_t* p = father->child[i];
			if ( p ){
				node_t* v = father->failer;
				while ( v && !v->child[i] ) v = v->failer;  /*如果不匹配反复寻找failer，v为空说明已经到根节点*/
				/*判断v为空一定要放在前面*/
				if ( !v ) p->failer = Node;             /*如果v为空，则failer指向root*/
				else      p->failer = v->child[i];
				q.push(p);
			}
		}
	}
}

/*搜索，返回匹配的单词数量*/
int search(char const word[]){
	int ans = 0;
    node_t* loc = Node;
	for(int i=0;word[i];++i){
        int sn = word[i] - 'a';
		while( loc && !loc->child[sn] )  /*沿着分支或者失败指针一直找，直到找到或者到root*/
			loc = loc->failer;
        loc = loc ? loc->child[sn] : Node;  /*定位到新的节点*/
		node_t* p = loc; /*将该节点所在的失配链的所有cnt加上*/
		while( p != Node && p->cnt >= 0 ){
			ans += p->cnt;
			p->cnt = -1;  /*表明该失配链已经匹配过了，以后不必再考虑*/
			p = p->failer;
		}
	}
	return ans;
}

char T[SIZE],Word[55];
int main(){
	int nofkase;
	scanf("%d",&nofkase);
	while(nofkase--){
		toUsed = 1;
		memset(Node,0,sizeof(node_t));

		int n;
        scanf("%d",&n);
		for(int i=0;i<n;++i){
			scanf("%s",Word);
			insert(Word);
		}
		buildAC();
        scanf("%s",T);
		printf("%d\n",search(T));
	}
	return 0;
}
