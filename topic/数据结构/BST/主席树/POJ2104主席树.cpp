/*
    ��ϯ��
    ��̬�����k������
    ��Դ�����ÿ������[1,x]��x=1,2,...,n
    ����n���߶������߶�����¼[s,e]������һ���ж��ٸ���ͬ����
    �õ�b���߶�����ȥ��a-1���߶��������ܵõ�Դ����[a,b]������һ���ж��ٸ���
*/

#include <stdio.h>
#include <algorithm>
using namespace std;

int const SIZE = 100003;
struct node_t{
    int left; //�����
    int right;//�Ҷ���
    int cnt;  //��ǰ�ڵ��Ӧ�����ڲ�ͬ���ĸ���
}Node[SIZE*20];
int toUsed = 0;
int Root[SIZE];//���ڵ�

inline int _newNode(){
    Node[toUsed].left = Node[toUsed].right = Node[toUsed].cnt = 0;
    return toUsed++;
}

//tΪ���ڵ��ָ��,[s,e]Ϊ����
//������ʱ��cntȫΪ0
void _build(int&t,int s,int e){
    t = _newNode();
    if ( s == e ) return;

    int mid = ( s + e ) >> 1;
    _build(Node[t].left,s,mid);
    _build(Node[t].right,mid+1,e);
}

inline void build(int&t,int s,int e){
    toUsed = 0;
    _newNode();
    _build(t,s,e);
}

void modify(int old,int&t,int s,int e,int pos,int delta){
    Node[t=_newNode()] = Node[old];
    Node[t].cnt += delta;
    if ( s == e ) return;

    int mid = ( s + e ) >> 1;
    if ( pos <= mid ) modify(Node[old].left,Node[t].left,s,mid,pos,delta);
    else modify(Node[old].right,Node[t].right,mid+1,e,pos,delta);
}

//t1Ϊt1ʱ�̵��߶�����t2Ϊt2ʱ�̵��߶�����t2>t1
//kΪҪ��ѯ�ĵ�k�󣬴�1��ʼ
int query(int t1,int t2,int s,int e,int k){
    if ( s == e ) return s;

    int x = Node[Node[t2].left].cnt - Node[Node[t1].left].cnt;
    int mid = ( s + e ) >> 1;
    return x >= k ? query(Node[t1].left,Node[t2].left,s,mid,k) : query(Node[t1].right,Node[t2].right,mid+1,e,k-x);
}

int getInt(){
	int sgn = 1;
	char ch = getchar();
	while( ch != '-' && ( ch < '0' || ch > '9' ) ) ch = getchar();
	if ( '-' == ch ) {sgn = 0;ch=getchar();}

	int ret = (int)(ch-'0');
	while( '0' <= (ch=getchar()) && ch <= '9' ) ret = ret * 10 + (int)(ch-'0');
	return sgn ? ret : -ret;
}

int N,M;
int A[SIZE],B[SIZE];
bool read(){
    if ( EOF == scanf("%d%d",&N,&M) ) return false;
    for(int i=1;i<=N;++i) A[i] = B[i] = getInt();
    return true;
}

int main(){
    int a,b;
    while( read() ){
        //��ɢ��
        sort(B+1,B+N+1);
        int n = unique(B+1,B+N+1) - B - 1;

        //����
        build(Root[0],1,n);

        //��Դ�����ÿ�������θ���
        for(int i=1;i<=N;++i){
            int pos = lower_bound(B+1,B+n+1,A[i]) - B;
            modify(Root[i-1],Root[i],1,n,pos,1);
        }

        //��ѯ
        for(int i=0;i<M;++i){
            a = getInt();b = getInt();
            printf("%d\n",B[query(Root[a-1],Root[b],1,n,getInt())]);
        }
    }
    return 0;
}