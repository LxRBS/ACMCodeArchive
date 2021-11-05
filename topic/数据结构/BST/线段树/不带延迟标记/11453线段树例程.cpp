//�����޸�RMQ 
#include <cstdio>
#include <climits>
#include <algorithm>
using namespace std;

int const SIZE = 100005;

inline int lson(int x){return x<<1;}
inline int rson(int x){return lson(x)|1;}

int A[SIZE];//Դ���飬ʵ���Ͽ��Բ��� 
int ST[SIZE<<2];//�߶����ĳ�����Դ�����4�� 
int N,M;

//��Ϣ�ϴ�,t��ʾ�ڵ㣬����t�Ķ��Ӽ���t����Ϣ 
void _pushUp(int t){
	ST[t] = max(ST[lson(t)],ST[rson(t)]);
} 

//������t��ʾ�ڵ㣬[s,e]��ʾt����������� 
void build(int t,int s,int e){
	if ( s == e ){
		scanf("%d",ST+t);
		return;
	}
	int mid = ( s + e ) >> 1;
	build(lson(t),s,mid);
	build(rson(t),mid+1,e);
	_pushUp(t);
}

//��ѯ,t��ʾ�ڵ㣬[s,e]��ʾt�����������
//[a,b]��ʾ�������󣬼���[a,b]����������ֵ 
int query(int t,int s,int e,int a,int b){
	if ( a <= s && e <= b ) return ST[t];
	int mid = ( s + e ) >> 1;
	int ret = INT_MIN;
	if ( a <= mid ){
		int tmp = query(lson(t),s,mid,a,b);
		if ( tmp > ret ) ret = tmp;
	} 
	if ( mid < b ){
		int tmp = query(rson(t),mid+1,e,a,b);
		if ( tmp > ret ) ret = tmp;
	} 
	return ret;
} 

//�����޸�,t��ʾ�ڵ㣬[s,e]Ϊt�����������
//��Դ�����idxλ���ϵ�������delta 
void modify(int t,int s,int e,int idx,int delta){
	if ( s == e ){
		ST[t] += delta;
		return;
	}
	int mid = ( s + e ) >> 1;
	if ( idx <= mid ) modify(lson(t),s,mid,idx,delta);
	else modify(rson(t),mid+1,e,idx,delta);
	_pushUp(t);
}

bool read(){
	if ( EOF == scanf("%d%d",&N,&M) ) return false;
	build(1,1,N);
	return true;
}

int main(){
	for(int kase=1;read();++kase){
		printf("Case %d:\n",kase);
		for(int i=0;i<M;++i){
			int a,b;
			char cmd[3];
			scanf("%s%d%d",cmd,&a,&b);
			if ( 'Q' == *cmd ){
			    printf("%d\n",query(1,1,N,a,b));
			}else{
			    modify(1,1,N,a,b);
			}			    
		}
	}
	return 0;
}
