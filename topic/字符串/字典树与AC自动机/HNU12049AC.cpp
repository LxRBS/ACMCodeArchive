#include <iostream>
#include <queue>

using namespace std;

#define TH(x) ( 'T' == (x) ? 0 : 1 )

char Pattern[][4] = {
	"","TTT","TTH","THT","THH","HTT","HTH","HHT","HHH"
};

int Ans[9];

char Input[42];

struct node_t{
	node_t* child[2];
	int leaf;
	node_t* failer;
}Node[17];
int toUsed = 1;

void insert(int index){
	int i = 0, branch;
	node_t* loc = Node;
	while( Pattern[index][i] ){
		branch = TH(Pattern[index][i]);
		if( ! loc->child[branch] )
			loc->child[branch] = Node + toUsed++;
		++i;
		loc = loc->child[branch];
	}
    loc->leaf = index;
}

void buildAC(){
	Node->failer = NULL;
	queue<node_t*> que;
	node_t* p;
	
	for(int i=0;i<2;++i){
		p = Node->child[i];
		if ( p ){
			p->failer = Node;
			que.push(p);
		}
	}

	while( !que.empty() ){
		node_t* father = que.front();
		que.pop();

		for(int i=0;i<2;++i){
			p = father->child[i];
			if ( p ){
				node_t* v = father->failer;
				while( v && !v->child[i] ) v = v->failer;

				if ( v ) p->failer = v->child[i];
				else     p->failer = Node;

				que.push(p);
			}
		}
	}

}

void search(char const word[]){
    int i = 0,sn;
	node_t* loc = Node;

	while( word[i] ){
        sn = TH(word[i]);
		while( loc && !loc->child[sn] ) loc = loc->failer;
		loc = loc ? loc->child[sn] : Node;
		if ( loc->leaf ) Ans[loc->leaf]++;
		++i;
	}
}

void output(int kase){
	printf("%d",kase);
	for(int i=1;i<=8;++i)printf(" %d",Ans[i]);
	printf("\n");
}

int main(){
	int t;
	scanf("%d",&t);

	memset(Node,0,sizeof(Node));

	for(int i=1;i<=8;++i) insert(i);
    buildAC();

	int kase;
	for(kase=1;kase<=t;++kase){
		scanf("%*d%*c%s",Input);
		memset(Ans,0,sizeof(Ans));
		search(Input);
		output(kase);
	}
	return 0;
}