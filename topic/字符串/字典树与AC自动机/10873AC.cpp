#include <cstdio>
#include <queue>

using namespace std;

#define SIZE 100000

struct node_t{
    node_t* child[26];
	node_t* failer;
	int length;         /*����ָʾ�����ʵĳ���*/
}Node[SIZE];

int toUsed = 1;

int Ans;

/*�����ֵ���*/
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

/*����ʧ��ָ��*/
void buildAC(){
	/*����failerָ��NULL*/
	Node->failer = 0;

	node_t* p;
	queue<node_t*> q;

	for(int i=0;i<26;i++){
		p = Node->child[i];

		/*һ���ӽڵ��failer��ָ���*/
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

				/*��������ʱ��˳��failerһֱ����*/
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

		/*�ҵ���̵ĵ��ʣ���Ϊ��һ���Ŀ�ͷ*/
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

		/*�������µ�����*/
		if ( flag ){
		    tans = i - start;
		    if ( tans > Ans ) Ans = tans;
		    
			/*�����ǰ�ҵ��ĵ���ͷ��start֮�������start*/
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

