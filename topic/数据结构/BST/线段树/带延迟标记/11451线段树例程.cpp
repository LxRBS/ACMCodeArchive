//�ɶ��޸�RMQ 
#include <cstdio>
#include <climits>
#include <algorithm>
using namespace std;

#define SIZE 100005

#define lson(x) ( (x) << 1 )
#define rson(x) ( lson(x) | 1 )

int A[SIZE];//Դ���飬ʵ���Ͽ��Բ��� 
int ST[SIZE<<2];//�߶����ĳ�����Դ�����4�� 
int Delay[SIZE<<2];
int N,M;

//��Ϣ�ϴ�,t��ʾ�ڵ㣬����t�Ķ��Ӽ���t����Ϣ 
void _pushUp(int t){
	ST[t] = max(ST[lson(t)],ST[rson(t)]);
} 

//�ӳ���Ϣ�´���t��ʾ�ڵ㣬�ӽڵ�ļ�ֵ���ӳ���ϢҪ���ݸ��ڵ���ӳټ������ 
void _pushDown(int t){
    if ( 0 == Delay[t] ) return ;
    int& x = Delay[t];
    Delay[lson(t)] += x;
    ST[lson(t)] += x;
    Delay[rson(t)] += x;
    ST[rson(t)] += x;  
    x = 0;   
}

//������t��ʾ�ڵ㣬[s,e]��ʾt����������� 
void build(int t,int s,int e){
    Delay[t] = 0;
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
//[a,b]��ʾ�������󣬼���[a,b]���������ֵ 
int query(int t,int s,int e,int a,int b){
	if ( a <= s && e <= b ) return ST[t];
	_pushDown(t);
	int mid = ( s + e ) >> 1;
	int ret = INT_MIN;
	if ( a <= mid ){
		int tmp = query(lson(t),s,mid,a,b);
		if ( ret < tmp ) ret = tmp;
	}
	if ( mid < b ){
		int tmp = query(rson(t),mid+1,e,a,b);
		if ( ret < tmp ) ret = tmp;
	} 
	return ret;
} 

//�ɶ��޸�,t��ʾ�ڵ㣬[s,e]Ϊt�����������
//��Դ�����[a,b]���������������delta 
void modify(int t,int s,int e,int a,int b,int delta){
	if ( a <= s && e <= b ){
		ST[t] += delta;
		Delay[t] += delta;
		return;
	}
	_pushDown(t);
	int mid = ( s + e ) >> 1;
	if ( a <= mid ) modify(lson(t),s,mid,a,b,delta);
	if ( mid < b ) modify(rson(t),mid+1,e,a,b,delta);
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
                int delta;
                scanf("%d",&delta);
			    modify(1,1,N,a,b,delta);
            }
		}
	}
	return 0;
}
