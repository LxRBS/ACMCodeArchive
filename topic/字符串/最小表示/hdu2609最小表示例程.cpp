#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

#define  SIZE 1000001

struct node_t{
    node_t* child[2];
}Node[SIZE];
int toUsed = 1;

//���뵥�ʣ������Ѵ��ڷ���false
bool insert(char const word[]){
	bool ret = false;
    node_t* loc = Node;
	for(int i=0;word[i];++i){
		int sn = word[i] - '0' ;
        if ( !loc->child[sn] ){
        	memset(Node+toUsed,0,sizeof(node_t));
        	loc->child[sn] = Node + toUsed ++;
        	ret = true;
        }
		loc = loc->child[sn];
	}
	return ret;
}
//������С��ʾ��s�е���ţ�s���Ѿ��ظ����ε��ַ���
//nΪδ�ظ�֮ǰ�ĳ���
int miniPre(char const s[],int n){
    int i = 0, j = 1;
    int k = 0;
    while( 1 ){
    	while( s[i+k] == s[j+k] && k < n ) ++k;
    	if ( k == n )return i;//�˴��ɷ���i��j����һ��
    	if ( s[i+k] > s[j+k] ) i += k + 1;
    	else j += k + 1;
    	if ( i >= n || j >= n ) return i < j ? i : j;//�˴�Ҫ����С��
    	if ( i == j ) ++j;//ǿ��j����һλ
    	k = 0;
    }
    return -1;//���ﲻ�ᵽ��
}

char A[205];
int proc(){
    int n = strlen(A);
    copy(A,A+n,A+n);
    A[n+n] = '\0';
    int x = miniPre(A,n);
    A[x+n] = '\0';
    //����С��ʾ�����ֵ���
    return insert(A+x) ? 1 : 0;
}
int main(){
	int n;
	while( EOF != scanf("%d",&n) ){
		toUsed = 1;
		memset(Node,0,sizeof(node_t));
		int ret = 0;
		for(int i=0;i<n;++i){
            scanf("%s",A);
            ret += proc();
		}
		printf("%d\n",ret);
	}
	return 0;
}
