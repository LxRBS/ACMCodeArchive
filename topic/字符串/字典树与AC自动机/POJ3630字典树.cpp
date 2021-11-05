/*
    给定数字串，问是某一个串是否是另一个串的前缀，注意：是则输出NO
	例如
	    输入 911
		     91123426
	    输出 NO
	使用Trie树，但不要使用new，使用静态分配，
	    在建立的过程中即可完成查找
    原来只打算用一个一维数组保存字典树，后来发现空间浪费巨大，超出范围
	第二个版本，每次清零node中所有的元素，耗时973ms
	现在修改为，用到哪个元素之前才清零，耗时157ms
	另外，node须开辟足够大，是否可以实现计算？
*/
#include <string>
#include <iostream>
#include <cstring>

using namespace std;
#define SIZE    10000
#define LEAF    2
#define BRANCH  1
//char trie[SIZE];   /*用一个数组保存字典树，0为根节点*/
struct node_t{
    node_t* child[10];   /*指向儿子*/
	int flag;			 /*树枝还是树叶*/ 
}node[SIZE*100];		 /* node[0]作为树根*/
int toUsed = 1;          /*标记node中待用的元素序号*/
bool insertfind(char const word[]){
	int i = 0,sn;
	node_t* location = node;
	while( word[i] ){
		sn = word[i] - '0';
		if ( !location->child[sn] ){
			memset(&node[toUsed],0,sizeof(node_t));
			location->child[sn] = node + toUsed;
			toUsed++;
		location->child[sn]->flag = BRANCH;
		}else if ( location->child[sn]->flag & LEAF ){
			return true;
		}else{
            ;
		}
		i++;
		location = location->child[sn];
	}
	location->flag = LEAF;
	for(i=0;i<10;i++){
		if ( location->child[i] )
			return true;
	}
	return false;
}

int main(){
	char ch[11];
	int t,n;
	scanf("%d",&t);
	while(t--){
		memset(node,0,sizeof(node_t));
		scanf("%d",&n);
		bool flag = false;  /*false表示没有找到*/
		while(n--){
		    scanf("%s",ch);
			if ( !flag ) flag = insertfind(ch);
		}
		if ( flag ) printf("NO\n");
		else        printf("YES\n");
	}
	return 0;
}
