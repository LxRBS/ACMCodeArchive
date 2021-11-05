#include <cstdio>
#include <algorithm>
using namespace std;
#define SIZE 100005

int A[SIZE];//Դ���飬���Բ��� 
int C[SIZE];//Binary Indexed Tree

inline int lowbit(int x){ return x & (-x); }

//��[1,n]������� 
int query(int n){
    int sum = 0;
    while( n > 0 ){
        sum += C[n];
        n = n - lowbit(n);
    } 
    return sum;
}

//��[s,e]������� 
inline int query(int s,int e){
	return query(e) - query(s-1);
}

//�����޸ģ�����idx��λ������delta,
//SIZEΪԪ�ظ���, �������Ч�±�Ϊ[1,n] 
void modify(int idx,int delta,int n){
    while( idx <= n ){
        C[idx] += delta;
        idx += lowbit(idx);
    }
}

//����״���飬n��ʾ���� 
//ʵ������ͨ���޸�ÿһ��Ai�õ��� 
void build(int n){
	fill(C,C+n+1,0);
	for(int i=1;i<=n;++i){
        int x;
        scanf("%d",&x);
        modify(i,x,n);		
	}
} 

int N,M;
bool read(){
    if ( EOF == scanf("%d%d",&N,&M) ) return false;
    build(N);
    return true;
}
int main(){
    for(int kase=1;read();++kase){
        printf("Case %d:\n",kase);
        while( M-- ){
            char cmd[3];
            int s,e;
            scanf("%s%d%d",cmd,&s,&e);
            if ( 'C' == *cmd ){
                modify(s,e,N);
            }else{
                printf("%d\n",query(s,e));
            }
        }
    }
    
    return 0;
}
