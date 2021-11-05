#include <cstdio>
#include <cstring>
#define SIZE 1000000

struct node_t{
	node_t* child[26];//26个儿子
	int idx;//对应解释的序号
}Node[SIZE];
int toUsed = 1;

//idx表示单词对应解释的序号
void insert(char const word[],int idx){
    node_t* loc = Node;
    for(int i=0;word[i];++i){
    	int sn = word[i] - 'a';
    	if ( !loc->child[sn] ){
            loc->child[sn] = Node + toUsed ++;
    	}
    	loc = loc->child[sn];
    }
    loc->idx = idx;
}
//查找单词，返回解释的序号，0表示未找到
int find(char const word[]){
    node_t* loc = Node;
    for(int i=0;word[i];++i){
    	int sn = word[i] - 'a';
    	if ( !loc->child[sn] ) return 0;
    	loc = loc->child[sn];
    }
    return loc->idx;
}
char A[1000005][12] = {"eh"};
int main(){
	char ch[23],word[12];
	int idx = 1;
    while( gets(ch) && *ch ){
    	sscanf(ch,"%s%s",A[idx],word);
    	insert(word,idx);
    	++idx;
    }
    while( gets(word) ) printf("%s\n",A[find(word)]);
	return 0;
}
