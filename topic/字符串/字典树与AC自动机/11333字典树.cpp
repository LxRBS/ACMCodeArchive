#include <cstdio>
#include <algorithm>
using namespace std;

#define SIZE 500000

struct _t{
	_t* son[26];
	int cnt;
	void clear(){fill(son,son+26,(_t*)0);cnt=0;}
}Node[SIZE];
int toUsed;

void insert(char const word[]){
    int k = 0;
	_t* loc = Node;
	while( word[k] ){
        int sn = word[k] - 'a';
		if( ! loc->son[sn] ){
			Node[toUsed].clear();
			loc->son[sn] = Node + toUsed ++;
		}
		loc = loc->son[sn];
		++loc->cnt;
		++k;
	}
}

int Ans;
void dfs(_t* p){
	Ans += p->cnt;
	if ( 1 == p->cnt ) return;
	for(int i=0;i<26;++i)if(p->son[i])
		dfs(p->son[i]);
}

char A[1002];
int main(){
	int nofkase;
	scanf("%d",&nofkase);
	while(nofkase--){
		toUsed = 1;
		Node->clear();

		int n;
		scanf("%d",&n);
		for(int i=0;i<n;++i){
			scanf("%s",A);
			insert(A);
		}

		Ans = 0;
		dfs(Node);
		printf("%d\n",Ans);
	}
	return 0;
}