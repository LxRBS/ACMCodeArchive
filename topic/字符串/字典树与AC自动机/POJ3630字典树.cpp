/*
    �������ִ�������ĳһ�����Ƿ�����һ������ǰ׺��ע�⣺�������NO
	����
	    ���� 911
		     91123426
	    ��� NO
	ʹ��Trie��������Ҫʹ��new��ʹ�þ�̬���䣬
	    �ڽ����Ĺ����м�����ɲ���
    ԭ��ֻ������һ��һά���鱣���ֵ������������ֿռ��˷Ѿ޴󣬳�����Χ
	�ڶ����汾��ÿ������node�����е�Ԫ�أ���ʱ973ms
	�����޸�Ϊ���õ��ĸ�Ԫ��֮ǰ�����㣬��ʱ157ms
	���⣬node�뿪���㹻���Ƿ����ʵ�ּ��㣿
*/
#include <string>
#include <iostream>
#include <cstring>

using namespace std;
#define SIZE    10000
#define LEAF    2
#define BRANCH  1
//char trie[SIZE];   /*��һ�����鱣���ֵ�����0Ϊ���ڵ�*/
struct node_t{
    node_t* child[10];   /*ָ�����*/
	int flag;			 /*��֦������Ҷ*/ 
}node[SIZE*100];		 /* node[0]��Ϊ����*/
int toUsed = 1;          /*���node�д��õ�Ԫ�����*/
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
		bool flag = false;  /*false��ʾû���ҵ�*/
		while(n--){
		    scanf("%s",ch);
			if ( !flag ) flag = insertfind(ch);
		}
		if ( flag ) printf("NO\n");
		else        printf("YES\n");
	}
	return 0;
}
