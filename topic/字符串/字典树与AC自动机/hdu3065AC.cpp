#include <iostream>
#include <queue>
#include <cstring>
using namespace std;

#define  SIZE 60000

struct node_t{
    node_t* child[26];
	node_t* failer;
	int order;
}Node[SIZE];

int toUsed = 1;

void insert(char const word[],int order){
	int i = 0,sn;
	node_t* loc = Node;

	while( word[i] ){
		sn = word[i] - 'A';
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
	
	node_t* p;
	queue<node_t*> q;

	int i;
	for(i=0;i<26;i++){
        p = Node->child[i];
		if ( p ){
			p->failer = Node;
			q.push(p);
		}
	}

	while( !q.empty() ){
		node_t* father = q.front();
		q.pop();

		for(i=0;i<26;i++){
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

int Cnt[1000+2];
char P[1000+2][51];
char T[2000000+2];

void search(char const word[]){
   int i = 0,sn;
   node_t* loc = Node;

   while( word[i] ){
	   sn = word[i] - 'A';
	   
	   if ( sn < 0 || sn >= 26 ){
		   loc = Node;
		   i++;
		   continue;
	   }

	   while( loc && !loc->child[sn] )
		   loc = loc->failer;

	   loc = loc ? loc->child[sn] : Node;

	   node_t* p = loc;
	   while( p != Node ){
	       Cnt[p->order]++;
		   p = p->failer;
	   }
	   i++;
   }
}



int main(){
	int nofv;
	while ( EOF != scanf("%d",&nofv)){
		memset(Cnt,0,sizeof(Cnt));
		memset(Node,0,sizeof(Node));
		memset(P,0,sizeof(P));
		memset(T,0,sizeof(T));

		toUsed = 1;
	
		int i;
		for(i=1;i<=nofv;i++){
			scanf("%s",P[i]);
			insert(P[i],i);
		}

		buildAC();

		scanf("%s",T);
		search(T);

		for(i=1;i<=nofv;i++)if(Cnt[i]){
			printf("%s: %d\n",P[i],Cnt[i]);
		}
	}

	return 0;
}
