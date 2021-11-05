#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;

#define  SIZE 1000001

/*trie����node[0]��root*/
struct node_t{
    node_t* child[26];
	node_t* failer;
	int cnt;//��ʾ�õ������ֵ��г��ֵĴ���
}Node[10000*51];
int toUsed = 1;

/*����trie��*/
void insert(char const word[]){
    node_t* loc = Node;
	for(int i=0;word[i];++i){
		int sn = word[i] - 'a' ;
        if ( !loc->child[sn] ){
        	memset(Node+toUsed,0,sizeof(node_t));
        	loc->child[sn] = Node + toUsed ++;
        }
		loc = loc->child[sn];
	}
	++loc->cnt;
}
/*����ʧ��ָ��*/
void buildAC(){
	Node[0].failer = NULL;/*root��failerΪ��*/
    queue<node_t*> q;
	for(int i=0;i<26;++i){//һ���ӽڵ��ʧ��ָ��ָ���
		node_t* p = Node[0].child[i];
		if ( p ){
            p->failer = Node;
            q.push(p);
		}
	}
	while( !q.empty() ){
		node_t* father = q.front();        /*ȡ��1���ڵ�*/
		q.pop();
		for(int i=0;i<26;++i){
			node_t* p = father->child[i];
			if ( p ){
				node_t* v = father->failer;
				while ( v && !v->child[i] ) v = v->failer;  /*�����ƥ�䷴��Ѱ��failer��vΪ��˵���Ѿ������ڵ�*/
				/*�ж�vΪ��һ��Ҫ����ǰ��*/
				if ( !v ) p->failer = Node;             /*���vΪ�գ���failerָ��root*/
				else      p->failer = v->child[i];
				q.push(p);
			}
		}
	}
}

/*����������ƥ��ĵ�������*/
int search(char const word[]){
	int ans = 0;
    node_t* loc = Node;
	for(int i=0;word[i];++i){
        int sn = word[i] - 'a';
		while( loc && !loc->child[sn] )  /*���ŷ�֧����ʧ��ָ��һֱ�ң�ֱ���ҵ����ߵ�root*/
			loc = loc->failer;
        loc = loc ? loc->child[sn] : Node;  /*��λ���µĽڵ�*/
		node_t* p = loc; /*���ýڵ����ڵ�ʧ����������cnt����*/
		while( p != Node && p->cnt >= 0 ){
			ans += p->cnt;
			p->cnt = -1;  /*������ʧ�����Ѿ�ƥ����ˣ��Ժ󲻱��ٿ���*/
			p = p->failer;
		}
	}
	return ans;
}

char T[SIZE],Word[55];
int main(){
	int nofkase;
	scanf("%d",&nofkase);
	while(nofkase--){
		toUsed = 1;
		memset(Node,0,sizeof(node_t));

		int n;
        scanf("%d",&n);
		for(int i=0;i<n;++i){
			scanf("%s",Word);
			insert(Word);
		}
		buildAC();
        scanf("%s",T);
		printf("%d\n",search(T));
	}
	return 0;
}
