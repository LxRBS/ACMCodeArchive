#include <iostream>

using namespace std;

#define SIZE 2450

struct node_t{
	node_t* child[26];
	int bits;
	bool over;
}Node[SIZE];
int toUsed = 1;

void insert(char const word[]){
	node_t* loc = Node;
	int i = 0,sn;
	
	while( word[i] ){
		sn = word[i] - 'a';
		if ( !loc->child[sn] ){
			loc->child[sn] = Node + toUsed++;
		}

		loc = loc->child[sn];
		++loc->bits;

		++i;
	}
	loc->over = true;

	return;
}

void search(char const word[],char ans[]){
	int sn,i=0,k=0;
	node_t* loc = Node;

	while(word[i]){
        sn = word[i] - 'a';
		loc = loc->child[sn];
		if ( 1 == loc->bits || ( loc->over && 0 == word[i+1] ) ) {
			ans[k++] = word[i];
			ans[k] = 0;
			return;
		}else{
			ans[k++] = word[i];
		}
		++i;
	}

	return;
}

char Input[1000][22];

int main(){
//	freopen("1.txt","r",stdin);
	memset(Node,0,sizeof(Node));

    int i = 0;
	while( EOF != scanf("%s",Input+i) ){
		insert(Input[i]);
		++i;
	}

	char ans[21];
	for(int k=0;k<i;++k){
        search(Input[k],ans);
		printf("%s %s\n",Input[k],ans);
	}
	return 0;
}