/*
    ��һ����ά�ַ���������Ѱ��ָ������
	���ʵ��ŷŷ�ʽ�����Ǻ���б��һ����8������
	��˵����ֻ��Trie����ɣ�����AC�Զ������������
*/

#include <iostream>
#include <queue>
using namespace std;


/*trie����node[0]��root*/
struct node_t{
	node_t* child[26]; 
	node_t* failer;     
	int num;    /*����ָʾ�ǵڼ�������*/
}node[10000*51];
int toUsed = 1;

/*����trie��*/
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
/*����ʧ��ָ��*/
void buildAC(){
	node[0].failer = NULL;          /*root��failerΪ��*/
	queue<node_t*> que;
	node_t* point;
	int i,j;
	for( i=0;i<26;i++ ){
		point = node[0].child[i];   /*һ���ӽڵ��failerָ��root*/
		if ( point ){
			point->failer = node;			
			que.push(point);        /*��һ���ӽڵ���ӣ��������ӽڵ��failer*/
		}
	}
	while( !que.empty() ){
		node_t* father = que.front();        /*ȡ��1���ڵ�*/
		que.pop();
		for( i=0;i<26;i++ ){
			point = father->child[i];
			if ( point ){   
				node_t* v = father->failer;
				while ( v && !v->child[i] ) v = v->failer;  /*�����ƥ�䷴��Ѱ��failer��vΪ��˵���Ѿ������ڵ�*/
				/*�ж�vΪ��һ��Ҫ����ǰ��*/
				if ( !v ) point->failer = node;             /*���vΪ�գ���failerָ��root*/
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
/*������ʾ�������Ԫ��*/
struct triplet_t{
	int row;
	int col;
	char direct;
}triplet[SIZE];

/*ȫ�ֱ�����������*/
int Row,Col,n;

/*����ָʾ����仯������*/
int const ORIENT[8][2] = {
/*  row  col */
	-1,  0,  /*��*/
    -1,  1,  /*����*/
	 0,  1,  /*��*/
	 1,  1,  /*����*/
	 1,  0,  /*��*/
	 1, -1,  /*����*/
     0, -1,  /*��*/
    -1, -1
};
/*
    ���ݷ���direct��ȡ��row��col������һ����ĸ��
	  ͬʱ��row��col�޸ĳ���һ����ĸ�����꣬û���򷵻�0
*/
char getNext(int& row,int& col,char direct){
    int d = direct - 'A';
    row = row + ORIENT[d][0];
	col = col + ORIENT[d][1];
	if ( row < 0 || row >= Row || col < 0 || col >= Col )
		return 0;
	return puzzle[row][col];
}

/*�����꣨row,col����ʼ����direct��������*/
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
	  while ( p != node ){     /*�ұ�ʧ���������еĵ���*/
		  if ( p->num ){       /*num��Ϊ���ʾ�е��ʲ�����ͬʱnum-1ָʾ�ǵڼ�������ĵ���*/
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
/*��ʾ���*/
void dispTriplet(int n){
	for ( int i=0;i<n;i++ )
		printf("%d %d %c\n",(triplet+i)->row,(triplet+i)->col,(triplet+i)->direct);
}

/*
    ����direct������������
    ���˸�����Ϊÿ�����򵥶����ú���㼴��
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
		for(row=0;row<Row;row++) search(row,col,direct);  /*��������Ȱ���*/
		row = Row - 1;
		for(col=0;col<Col;col++) search(row,col,direct);  /*�ٰ���*/
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
/*��û��ʧ����������£��ӣ�row��col����direct��������*/
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
    for(i=0;i<Row;i++)for(j=0;j<Col;j++)for(d='A';d<='H';d++) ��һ�δ�����ͼ����AC�Զ���ֻ��Trie�������TLE
		searchTrie(i,j,d);
*/
		
	dispTriplet(n);
	return 0;
}
