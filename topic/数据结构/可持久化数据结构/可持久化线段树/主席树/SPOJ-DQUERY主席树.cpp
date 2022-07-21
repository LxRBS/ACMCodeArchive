/*
    ��������A����[a,b]�����ڲ�ͬԪ�ص�����
    ��׼��Ī���㷨��Ҳ������ϯ��
    ��ÿһ������[1,i]����һ���߶�����Ϊ��i���߶���
    ���Ԫ��Ai��֮ǰ��ĳ��λ��j���ֹ�����Ajɾ����Ȼ���ڽ�Ai����
    ��ѯʱ��ֻ��Ҫ����b���߶�����λ��[a,n]֮�����������
*/

#include <stdio.h>
#include <algorithm>
using namespace std;

int const SIZE = 30103;
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

//ĳ���߶�����[a,b]����ֵ
int query(int t,int s,int e,int a,int b){
    if ( a <= s && e <= b ) return Node[t].cnt;

    int mid = ( s + e ) >> 1;
    int ans = 0;
    if ( a <= mid ) ans += query(Node[t].left,s,mid,a,b);
    if ( mid < b ) ans += query(Node[t].right,mid+1,e,a,b);
    return ans;
}

int getUnsigned(){
	char ch = getchar();
	while( ch < '0' || ch > '9' ) ch = getchar();

	int ret = (int)(ch-'0');
	while( '0' <= ( ch = getchar() ) && ch <= '9' ) ret = ret * 10 + (int)(ch-'0');
	return ret;
}

int N,M,NN;
int A[SIZE],B[SIZE];
bool read(){
    if ( EOF == scanf("%d",&N) ) return false;
    for(int i=1;i<=N;++i) A[i] = B[i] = getUnsigned();

    //��ɢ��
    sort(B+1,B+N+1);
    NN = unique(B+1,B+N+1) - B - 1;

    //����
    build(Root[0],1,N);
    return true;
}

int LastPos[SIZE];
int main(){
    //freopen("1.txt","r",stdin);
    int a,b,v,t;
    while( read() ){
        fill(LastPos,LastPos+NN+1,0);

        //��Դ�����ÿ�������θ���
        for(int i=1;i<=N;++i){
            v = lower_bound(B+1,B+NN+1,A[i]) - B;

            if ( LastPos[v] ){//��Ҫһ����ʱ������
                modify(Root[i-1],t,1,N,LastPos[v],-1);
                modify(t,Root[i],1,N,i,1);
            }else{
                modify(Root[i-1],Root[i],1,N,i,1);
            }

            LastPos[v] = i;
        }

        //��ѯ
        M = getUnsigned();
        for(int i=0;i<M;++i){
            a = getUnsigned();b = getUnsigned();
            printf("%d\n",query(Root[b],1,N,a,N));
        }
    }
    return 0;
}
