#include <stdio.h>
#include <string.h>

#define  MAXSIZE  100

struct node_t{
	struct node_t* child[26];
	int cnt;
	char str[101];
}Node[MAXSIZE];

int toUsed = 1;

void insert(char const word[],int fr){
	int i=0,sn;
	struct node_t* location = Node;
	while( word[i] ){
		sn = word[i] - 'a';
		if ( !location->child[sn] ){
			location->child[sn] = Node + toUsed;
			toUsed++;

			strcpy(location->child[sn]->str,location->str);
		}

		location = location->child[sn];

		*(location->str + i) = word[i];
		location->cnt += fr;

		i++;
	}
}

char const TABLE[][5] = {
    "",
	"",
	"abc",
	"def",
	"ghi",
	"jkl",
	"mno",
	"pqrs",
	"tuv",
	"wxyz"
};

struct node_t* Pt[MAXSIZE];

void find(char const word[]){
	int i = 0;
	int ans = 0;
	int size = 3;
    int idx;

	struct node_t* p = 0;
	struct node_t* location;
	
	int ihead = 0,itail = 0;
	Pt[itail++] = Node; 

	while( word[i] != '1' ){
        idx = word[i] - '0';
		if ( 7 == idx || 9 == idx ) size = 4;
		else                        size = 3;

		p = 0;
		ans = 0;

		int tail = itail;
		for(;ihead<tail;ihead++){
            location = Pt[ihead];
		
			int ii;
			for(ii=0;ii<size;ii++){
				int sn = TABLE[idx][ii] - 'a';

				if ( !location->child[sn] ) continue;

				Pt[itail++] = location->child[sn];

				int cnt = location->child[sn]->cnt;
                if ( cnt > ans ){
					ans = cnt;
					p = location->child[sn];
				}
			}
		}
	

		if ( p ) printf("%s\n",p->str);
		else     printf("MANUALLY\n");
         
		i++;
	}
}

int main(){
	int nofs;
	int is;
	char word[101];
	
	scanf("%d",&nofs);
	
	for(is=1;is<=nofs;is++){
		int nofword,noftest;
		int fr;
        
		memset(Node,0,sizeof(Node));
		
		scanf("%d",&nofword);
		while(nofword--){
			scanf("%s%d",word,&fr);
			insert(word,fr);
		}

		printf("Scenario #%d:\n",is);

		scanf("%d",&noftest);
		while(noftest--){
			scanf("%s",word);
			memset(Pt,0,sizeof(Pt));
			find(word);
			printf("\n");
		}
		printf("\n");
	}
	return 0;
}