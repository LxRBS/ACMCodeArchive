/*
    在一个二维字符矩阵里面寻找指定单词
	单词的排放方式可能是横竖斜，一共有8个方向
	据说可以只用Trie树完成，利用AC自动机更容易完成
*/

#include <iostream>
#include <queue>
using namespace std;


/*trie树，node[0]是root*/
struct node_t{
	node_t* child[26]; 
	node_t* failer;     
	int num;    /*用来指示是第几个单词*/
}node[10000*51];
int toUsed = 1;

/*建立trie树*/
void insert(char const word[],int num){
	int i=0,branch;
	node_t* location = &node[0];
	while( word[i] ){
		branch = word[i] - 'A' ;
		if ( location->child[branch] ){
			;
		}else{
			memset(node+toUsed,0,sizeof(node_t));
			location->child[branch] = node + toUsed;
			toUsed++;
		}
		i++;
		location = location->child[branch];
	}
	location->num = num + 1;
}
/*建立失败指针*/
void buildAC(){
	node[0].failer = NULL;          /*root的failer为空*/
	queue<node_t*> que;
	node_t* point;
	int i,j;
	for( i=0;i<26;i++ ){
		point = node[0].child[i];   /*一级子节点的failer指向root*/
		if ( point ){
			point->failer = node;			
			que.push(point);        /*将一级子节点入队，待求其子节点的failer*/
		}
	}
	while( !que.empty() ){
		node_t* father = que.front();        /*取出1个节点*/
		que.pop();
		for( i=0;i<26;i++ ){
			point = father->child[i];
			if ( point ){   
				node_t* v = father->failer;
				while ( v && !v->child[i] ) v = v->failer;  /*如果不匹配反复寻找failer，v为空说明已经到根节点*/
				/*判断v为空一定要放在前面*/
				if ( !v ) point->failer = node;             /*如果v为空，则failer指向root*/
				else      point->failer = v->child[i];
				que.push(point);
			}
		}
	}
}
#if 1
void dispTrie(){
	int i;
	for ( i=0;i<toUsed;i++ ){
		printf("Node %d:",i);	
        printf("%3d",node[i].num);
		for(int j=0;j<26;j++){
			node_t* a = node[i].child[j]; 
			if ( a )
				printf("%2c",j+'A');

		}

		node_t* a = node[i].failer;
//		if ( a ) printf("%4d",a-node);
		printf("\n");
	}
}
#endif

#define SIZE 1001

char puzzle[SIZE][SIZE];
char testword[SIZE][SIZE];
/*用来显示结果的三元组*/
struct triplet_t{
	int row;
	int col;
	char direct;
}triplet[SIZE];

/*全局变量保存输入*/
int Row,Col,n;

/*用来指示方向变化的数组*/
int const ORIENT[8][2] = {
/*  row  col */
	-1,  0,  /*上*/
    -1,  1,  /*右上*/
	 0,  1,  /*右*/
	 1,  1,  /*右下*/
	 1,  0,  /*下*/
	 1, -1,  /*左下*/
     0, -1,  /*左*/
    -1, -1
};
/*
    根据方向direct，取（row，col）的下一个字母，
	  同时把row，col修改成下一个字母的坐标，没有则返回0
*/
char getNext(int& row,int& col,char direct){
    int d = direct - 'A';
    row = row + ORIENT[d][0];
	col = col + ORIENT[d][1];
	if ( row < 0 || row >= Row || col < 0 || col >= Col )
		return 0;
	return puzzle[row][col];
}

/*从坐标（row,col）开始沿着direct方向搜索*/
void search(int row,int col,char direct){
    int i = 0, branch;
	node_t* location = node;
    char ch = puzzle[row][col];
    do {
      branch = ch - 'A';
	  while ( location != node && !location->child[branch] )
			location = location->failer;
	  location = (location->child[branch]) ? (location->child[branch]) : node;
	  node_t* p = location;
	  while ( p != node ){     /*找遍失配链上所有的单词*/
		  if ( p->num ){       /*num不为零表示有单词产生，同时num-1指示是第几个输入的单词*/
			  int t = p->num - 1;
			  int len = strlen(testword[t]);
			  triplet[t].row = row - ( len - 1 ) * ORIENT[direct-'A'][0];
			  triplet[t].col = col - ( len - 1 ) * ORIENT[direct-'A'][1];
			  triplet[t].direct = direct;
		  }
		  p = p->failer;
		}
	} while( ch = getNext(row,col,direct) );
}
/*显示结果*/
void dispTriplet(int n){
	for ( int i=0;i<n;i++ )
		printf("%d %d %c\n",(triplet+i)->row,(triplet+i)->col,(triplet+i)->direct);
}

/*
    按照direct方向搜索矩阵
    共八个方向，为每个方向单独设置好起点即可
*/
void searchPuzzle(char direct){
	int row,col;
	if ( 'A' == direct ){
		row = Row - 1;
		for( col=0;col<Col;col++ ){
            search(row,col,direct);
        }
	}else if ( 'B' == direct ){
		col = 0;
		for(row=0;row<Row;row++) search(row,col,direct);  /*搜索起点先按行*/
		row = Row - 1;
		for(col=0;col<Col;col++) search(row,col,direct);  /*再按列*/
	}else if ( 'C' == direct ){
		col = 0;
		for(row=0;row<Row;row++) search(row,col,direct);
	}else if ( 'D' == direct ){
        col = 0;
		for(row=0;row<Row;row++) search(row,col,direct);
		row = 0;
		for(col=1;col<Col;col++) search(row,col,direct);
	}else if ( 'E' == direct ){
		row = 0;
		for(col=0;col<Col;col++) search(row,col,direct);
	}else if ( 'F' == direct ){
		row = 0;
		for(col=0;col<Col;col++) search(row,col,direct);
		col = Col - 1;
        for(row=1;row<Row;row++) search(row,col,direct);
	}else if ( 'G' == direct ){
		col = Col - 1;
		for(row=0;row<Row;row++) search(row,col,direct);
	}else if ( 'H' == direct ) {
        col = Col - 1;
		for(row=0;row<Row;row++) search(row,col,direct);
		row = Row - 1;
		for(col=0;col<Col-1;col++) search(row,col,direct);
	}
	return;
}
/*在没有失配链的情况下，从（row，col）按direct方向搜索*/
void searchTrie(int row,int col,char direct){
    int i = 0, branch;
	node_t* location = node;
    char ch = puzzle[row][col];
    do {
		branch = ch - 'A';
		if ( location->child[branch] ){
			location = location->child[branch];
			if ( location->num ){
				int t = location->num - 1;
				int len = strlen(testword[t]);
				triplet[t].row = row - ( len - 1 ) * ORIENT[direct-'A'][0];
				triplet[t].col = col - ( len - 1 ) * ORIENT[direct-'A'][1];
			    triplet[t].direct = direct;
			}
		}else{
			location = node;
		}
	} while( ch = getNext(row,col,direct) );
}
int main(){
	int i,j,d;
	scanf("%d%d%d",&Row,&Col,&n);
	for(i=0;i<Row;i++) scanf("%s",puzzle[i]);
	for(i=0;i<n;i++){
		scanf("%s",testword[i]);
		insert(testword[i],i);
	}
	buildAC();
    for(i='A';i<='H';i++) searchPuzzle(i);
/*  
    for(i=0;i<Row;i++)for(j=0;j<Col;j++)for(d='A';d<='H';d++) 这一段代码试图不用AC自动机只用Trie树，结果TLE
		searchTrie(i,j,d);
*/
		
	dispTriplet(n);
	return 0;
}
