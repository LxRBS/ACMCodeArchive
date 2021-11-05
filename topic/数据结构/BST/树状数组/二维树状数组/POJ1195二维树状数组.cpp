/*
     ��ά��״����
     �������
     �������
*/
#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;

int const SIZE = 2010;

int C[SIZE][SIZE];//��״����

inline int lowbit(int x){return x&-x;}

//�����(1,1)��(x,y)֮��ĺ�
int query(int x,int y){
    int ans = 0;
    for(int i=x;i>0;i-=lowbit(i)){
        for(int j=y;j>0;j-=lowbit(j)){
            ans += C[i][j];
        }
    }
    return ans;
}

inline int query(int left,int bottom,int right,int top){
    return query(right,top) - query(left-1,top) + query(left-1,bottom-1) - query(right,bottom-1);
}

void modify(int x,int y,int delta,int n){
    for(int i=x;i<=n;i+=lowbit(i)){
        for(int j=y;j<=n;j+=lowbit(j)){
            C[i][j] += delta;
        }
    }
}

int main(){
    //freopen("1.txt","r",stdin);

    int cmd,s;
    scanf("%d%d",&cmd,&s);
    memset(C,0,sizeof(C));

    while( scanf("%d",&cmd) && cmd != 3 ){
        if ( 1 == cmd ){
            int x,y,a;
            scanf("%d%d%d",&x,&y,&a);
            modify(++x,++y,a,s);
        }else{
            int l,b,r,t;
            scanf("%d%d%d%d",&l,&b,&r,&t);
            printf("%d\n",query(++l,++b,++r,++t));
        }
    }
    return 0;
}
