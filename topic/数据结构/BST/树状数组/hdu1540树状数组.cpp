/*
    �����������ĵ�
    Dx��ʾ�ƻ�x��x����������Ͳ�������
    Qx��ʾ��ѯx���ڵ����������ж��ٸ���
    R��ʾ�޸����һ���ƻ��ĵ�

    ��AiΪ1��ʾi���ƻ���Ϊ0��ʾ���
    Si = SIGMA[1,i];
    ����x����������Ϊ[left,right]����
    S(left-1)<S(left)=S(left+1)=.=S(x)=..=S(right)<S(right+1)
*/
#include <stdio.h>
#include <algorithm>
using namespace std;

int const SIZE = 50010;
int A[SIZE];
int C[SIZE];//��״����

inline int lowbit(int x){return x & -x;}

int query(int pos){
    int ans = 0;
    for(int i=pos;i>0;i-=lowbit(i)) ans += C[i];
    return ans;
}

inline int query(int s,int e){
    return query(e) - query(s-1);
}

void modify(int pos,int delta,int n){
    for(int i=pos;i<=n;i+=lowbit(i)) C[i] += delta;
}

int proc(int x,int n){
    if ( 1 == A[x] ) return 0;

    int tmp = query(x);
    int left = 0, right = n, mid;
    do{
        mid = ( left + right ) >> 1;
        if ( query(mid) <= tmp ) left = mid + 1;
        else right = mid - 1;
    }while(left<=right);
    int ans2 = right;

    left = 0, right = n;
    do{
        mid = ( left + right ) >> 1;
        if ( query(mid) >= tmp ) right = mid - 1;
        else left = mid + 1;
    }while(left<=right);

    return ans2 - left;
}

int Last[SIZE],LastCnt;
int main(){
    //freopen("1.txt","r",stdin);

    int n,m,x;
    char cmd[3];
    while( 2 == scanf("%d%d",&n,&m) ){
        fill(C,C+n+1,0);
        fill(A,A+n+1,0);
        LastCnt = 0;

        while(m--){
            scanf("%s",cmd);
            if ( 'D' == *cmd ){
                scanf("%d",&x);
                Last[LastCnt++] = x;
                if ( 0 == A[x] ){
                    A[x] = 1;
                    modify(x,1,n);
                }
            }else if ( 'Q' == *cmd ){
                scanf("%d",&x);
                printf("%d\n",proc(x,n));
            }else if (LastCnt){
                x = Last[--LastCnt];
                if ( 1 == A[x] ){
                    A[x] = 0;
                    modify(x,-1,n);
                }
            }
        }
    }
    return 0;
}
