#include <iostream>
#include <algorithm>
using namespace std;

int const SIZE = 200000 + 2;
int ST[SIZE<<2];
int A[SIZE];

inline int lson(int x){return x<<1;}
inline int rson(int x){return lson(x)|1;}
//���㸸�ڵ�
inline void _pushUp(int t){
    ST[t] = max(ST[lson(t)],ST[rson(t)]);
	return;
}
void build(int t,int s,int e){
	if ( s == e ){
		ST[t] = A[s];
		return;
	}
	//�ݹ�
	int mid = ( s + e ) >> 1;
	build(lson(t),s,mid);
	build(rson(t),mid+1,e);
	//���ϼ���
	_pushUp(t);
	return;
}
//����sn���ڵ����Ϊnum
void update(int t,int s,int e,int sn,int num){
	if ( s == e ){
		ST[t] = num;
		return;
	}
	//�ݹ�
	int mid = ( s + e ) >> 1;
	if ( sn <= mid ) update(lson(t),s,mid,sn,num);
	else             update(rson(t),mid+1,e,sn,num); 
	//������¸��ڵ�
    _pushUp(t);
}
//��ѯ[a,b]�е����ֵ
int query(int t,int s,int e,int a,int b){
	if ( a <= s && e <= b ) return ST[t];

	int mid = ( s + e ) >> 1;
	int ans = 0;
	if ( a <= mid )ans = query(lson(t),s,mid,a,b);
	if ( b > mid ){	
		int y = query(rson(t),mid+1,e,a,b);
		if ( ans < y ) ans = y;
	}
	return ans;
}

int main(){
	int n,m;
	while( EOF != scanf("%d%d",&n,&m) ){
        for(int i=1;i<=n;++i)scanf("%d",A+i);
		//����
		build(1,1,n);
		//����
		while(m--){
			char op[2];
			int a,b;
			scanf("%s%d%d",op,&a,&b);
			
			if ( 'U' == *op ){
                update(1,1,n,a,b);
			}else{
                printf("%d\n",query(1,1,n,a,b));
			}
		}
	}
	return 0;
}
