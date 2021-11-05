#include <iostream>

using namespace std;

struct node_t{
	node_t* child[2];
	bool leaf;
}Node[10000];

int toUsde = 1;

bool insert(char const word[]){
    node_t* loc = Node;
	int i = 0;
	int sn;
	bool flag = true;

	while( word[i] ){
        sn = word[i] - '0';
		if ( !loc->child[sn] ){
			loc->child[sn] = Node + toUsde++;
			flag = false;
		}
		loc = loc->child[sn];
		if ( loc->leaf ) return true;
		++i;
	}
	loc->leaf = true;
	return flag;
}
char Input[1000];
int main(){
	int kase = 0;
	bool flag=false;
	memset(Node,0,sizeof(Node));

	while( EOF != scanf("%s",Input) ){
		if ( '9' == Input[0] ){
            ++kase;
			printf("Set %d is ",kase);
			if ( flag ) printf("not ");
			printf("immediately decodable\n");
			memset(Node,0,sizeof(Node));
			flag = false;
		}
		if ( !flag ) flag = insert(Input);
	}

	return 0;
}