#include <stdio.h>
#include <string.h>

struct node_t{
	struct node_t* child[26];
	int cnt;
}Node[500000]; 

int toUsed = 1;

void insert(char const word[]){
	int i = 0, sn;
	struct node_t* location = Node;
	while( word[i] ){
		sn = word[i] - 'a';

		//�����ǰ��֧��û�з����ڴ棬�����һ���ڴ棬��
		if ( !location->child[sn] ){
			location->child[sn] = Node + toUsed;
			toUsed++;
		}

		location = location->child[sn];
		
		//ÿ��һ����ĸ�ͼ�1
		location->cnt++;
		
		i++;
	}
	return;
}

int find(char const word[]){
	struct node_t* location = Node;
	int i = 0, sn;
	while( word[i] ){
		sn = word[i] - 'a';

		//���û�����ڴ棬��֤�������ֵ�����
		if ( !location->child[sn] )
			return 0;

		location = location->child[sn];

		i++;
	}
	return location->cnt;
}

int main(){
	char ch[11];
    memset(Node,0,sizeof(Node));
	
	while(1){
		gets(ch);
		if ( 0 == ch[0] ) break;
		insert(ch);
	}
	
	while( EOF != scanf("%s",ch) ){
        printf("%d\n",find(ch));
	}
	
	return 0;
}
