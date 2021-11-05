#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

#define  SIZE 1000001

struct node_t{
    node_t* child[2];
}Node[SIZE];
int toUsed = 1;

//插入单词，单词已存在返回false
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
//返回最小表示在s中的序号，s是已经重复二次的字符串
//n为未重复之前的长度
int miniPre(char const s[],int n){
    int i = 0, j = 1;
    int k = 0;
    while( 1 ){
    	while( s[i+k] == s[j+k] && k < n ) ++k;
    	if ( k == n )return i;//此处可返回i、j任意一个
    	if ( s[i+k] > s[j+k] ) i += k + 1;
    	else j += k + 1;
    	if ( i >= n || j >= n ) return i < j ? i : j;//此处要返回小的
    	if ( i == j ) ++j;//强制j后移一位
    	k = 0;
    }
    return -1;//这里不会到达
}

char A[205];
int proc(){
    int n = strlen(A);
    copy(A,A+n,A+n);
    A[n+n] = '\0';
    int x = miniPre(A,n);
    A[x+n] = '\0';
    //将最小表示插入字典树
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
