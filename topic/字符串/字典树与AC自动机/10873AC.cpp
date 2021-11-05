#include <cstdio>
#include <queue>

using namespace std;

#define SIZE 100000

struct node_t{
    node_t* child[26];
	node_t* failer;
	int length;         /*用来指示本单词的长度*/
}Node[SIZE];

int toUsed = 1;

int Ans;

/*建立字典树*/
void insert(char const word[]){
	int i=0,sn;
	node_t* location = Node;

	while( word[i] ){
		sn = word[i] - 'A';

		if ( NULL == location->child[sn] ){
			location->child[sn] = Node + toUsed;
			toUsed++;
		}

		location = location->child[sn];
		i++;
	}

	location->length = i;
}

/*建立失败指针*/
void buildAC(){
	/*根的failer指向NULL*/
	Node->failer = 0;

	node_t* p;
	queue<node_t*> q;

	for(int i=0;i<26;i++){
		p = Node->child[i];

		/*一级子节点的failer都指向根*/
		if ( p ){
			p->failer = Node;
			q.push(p);
		}
	}

	while( !q.empty() ){
		node_t* father = q.front();
		q.pop();

		for(int i=0;i<26;i++){
			p = father->child[i];

			if ( p ){
				node_t* v = father->failer;

				/*条件允许时，顺着failer一直往下*/
				while( v && !v->child[i] )
					v = v->failer;

				if ( v ) p->failer = v->child[i];
				else     p->failer = Node;

				q.push(p);
			}
		}
	}

}

void search(char const word[]){
    int tans;
	int i=0,sn;
	node_t* loc = Node;
	int start = 0;

	while( word[i] ){
		sn = word[i] - 'A';

        while( loc && !loc->child[sn] )
			loc = loc->failer;

		loc = loc ? loc->child[sn] : Node;

		/*找到最短的单词，作为下一个的开头*/
		int shortest = 102;
		bool flag = false;
		node_t* p = loc;
		while( p != Node ){
			if ( p->length && shortest > p->length ){
				shortest = p->length;
				flag = true;
			}
			p = p->failer;
		}

		/*表明有新的区间*/
		if ( flag ){
		    tans = i - start;
		    if ( tans > Ans ) Ans = tans;
		    
			/*如果当前找到的单词头在start之后则更新start*/
			if ( tans + 1 >= shortest )
				start = i + 2 - shortest;
			
		}

		i++;
		
	}

    tans = i - start;
    if ( tans > Ans ) Ans = tans;

}

char T[100001];
char FW[101];

int main(){
	int t;
	scanf("%d",&t);

	while(t--){
        int n,m;
		scanf("%d%d%s",&n,&m,T);

		memset(Node,0,sizeof(Node));
		toUsed = 1;

		for(int i=0;i<m;i++){
			scanf("%s",FW);
			insert(FW);
		}

		buildAC();

		Ans = 0;
		search(T);
		
		printf("%d\n",Ans);
	}

	return 0;
}

