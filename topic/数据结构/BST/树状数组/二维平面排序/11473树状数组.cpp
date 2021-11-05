#include <cstdio>
#include <algorithm>
using namespace std;

#define SIZE 200005

//��״����
int C[SIZE] = {0};

//Դ����,Ai��ʾ����Ϊi�ĸ���
int A[SIZE] = {0};

//����x�Ķ�����λ�����λ1�������ֵ
int lowbit(int x){
    return x & ( x ^ ( x - 1 ) );
}

//���£�����idx�ڵ�ֵ����v
//��״�����ܳ���Ϊn���±귶Χ��1��n
void update(int idx,int v,int n){
	while( idx <= n ){
	    C[idx] += v;
		idx += lowbit(idx);
	}
}

//��ǰx�����
int sum(int x){
    int s = 0;
	while( x > 0 ){
	    s += C[x];
		x -= lowbit(x);
	}
    return s;
}

struct _t{
	int s,e;
	int idx;
}Node[SIZE];
bool operator < (_t const&l,_t const&r){
	if ( l.e != r.e ) return l.e > r.e;
	if ( l.s != r.s ) return l.s < r.s;
	return l.idx < r.idx;//��֤��N����ǰ��
}

struct _t2{
	int s,idx;
}Node2[SIZE];
bool operator < (_t2 const&l,_t2 const&r){
	return l.s < r.s;
}

int N,M;
void read(){
	scanf("%d%d",&N,&M);
	for(int i=0;i<N;++i){
		scanf("%d%d",&Node[i].s,&Node[i].e);
		Node[i].idx = 0;
        Node2[i].s = Node[i].s;
        Node2[i].idx = i;
	}
	for(int i=0;i<M;++i){
		scanf("%d",&Node[i+N].s);
		Node[i+N].e = Node2[i+N].s = Node[i+N].s;
		Node[i+N].idx = i + 1;
		Node2[i+N].idx = i + N;
	}
}

int Ans[SIZE];
int main(){
	int nofkase;
	scanf("%d",&nofkase);
	for(int kase=1;kase<=nofkase;++kase){
        read();
        
        //��ɢ��
	    sort(Node2,Node2+N+M);

        int k = 1;
        Node[Node2[0].idx].s = k;
        for(int i=1;i<N+M;++i){
            if ( Node2[i].s != Node2[i-1].s ) ++k;
            Node[Node2[i].idx].s = k;
        }
        fill(C,C+k+1,0);
        sort(Node,Node+N+M);

        printf("Case #%d:\n",kase);

        for(int i=0;i<N+M;++i){
            if ( Node[i].idx ){
            	Ans[Node[i].idx] = sum(Node[i].s);
            }else{
            	update(Node[i].s,1,k);
            }
        }

        for(int i=1;i<=M;++i)printf("%d\n",Ans[i]);
	}
	return 0;
}
