#include <iostream>
#include <queue>
#include <set>
#include <cstring>
using namespace std;

#define  SIZE 60000

struct node_t{
    node_t* child[130];
	int order;
	node_t* failer;
}Node[SIZE];

int toUsed = 1;

void insert(char const word[],int order){
	int i=0,sn;
	node_t* loc = Node;
	while(word[i]){
		sn = word[i];
		
		if ( !loc->child[sn] ){
			loc->child[sn] = Node + toUsed;
			toUsed++;
		}
		
		loc = loc->child[sn];

		i++;
	}

	loc->order = order;
}

void buildAC(){
    Node->failer = 0;

	queue<node_t*> q;

	node_t* p;

	int i;
	for(i=0;i<130;i++){
        p = Node->child[i];
		if ( p ){
			p->failer = Node;
			q.push(p);
		}
	}

	while( !q.empty() ){
		node_t* father = q.front();
		q.pop();

		for(i=0;i<130;i++){
			p = father->child[i];
			if ( p ){
				node_t* v = father->failer;
				while( v && !v->child[i] )
					v = v->failer;

				if ( v ) p->failer = v->child[i];
				else     p->failer = Node;

				q.push(p);
			}
		}
	}

}

int search(char const word[],set<int>& s){
    int ans = 0;
	int i = 0,sn;

	node_t* loc = Node;


	while( word[i] ){
        sn = word[i];

		while( loc && !loc->child[sn] )
			loc = loc->failer;

		loc = loc ? loc->child[sn] : Node;

		node_t* p = loc;

		while( p != Node ){
			s.insert(p->order);
			p = p->failer;
		}

		i++;
	}

	return 1;
}

char P[200+2];
char T[10000+2];

int main(){
	memset(Node,0,sizeof(Node));

	int nofv;
	scanf("%d",&nofv);
	int i;
	for(i=1;i<=nofv;i++){
		scanf("%s",P);
		insert(P,i);
	}

	buildAC();

	int noft;
	scanf("%d",&noft);
	
	set<int> s;

	int ans = 0;
	for(i=1;i<=noft;i++){
		scanf("%s",T);
		s.clear();
		search(T,s);

		if ( s.size() > 1 ){
			ans++;
			set<int>::iterator it = s.begin();
			
			printf("web %d:",i);

			for(++it;it!=s.end();++it){
                printf(" %d",*it);
			}

			printf("\n");
		}
	}

	printf("total: %d\n",ans);

	return 0;
}
