/**
  计算一遍连分数
         b1
  ---------------
           b2
  a1 + ----------
              b3
       a2 + -----
             ...

  直到an和bn，n在8以内，暴力
*/

#include <stdio.h>
using namespace std;
typedef int llt;

//iteration implementation
llt gcd(llt a,llt b){
    while( b ){
        llt r = b;
        b = a % b;
        a = r;
    }
    return a;
}

int A[11],B[11];

//计算a+u/v，结果为p/q
void add(int a,int u,int v,int&p,int&q){
    int g = gcd(u,v);
    u /= g;
    v /= g;

    q = v;
    p = a*v+u;
    g = gcd(p,q);
    p /= g;
    q /= g;
}

int main(){
    //freopen("2.txt","r",stdin);
    int nofkase;
    scanf("%d",&nofkase);
    for(int kase=1;kase<=nofkase;++kase){
        int n;
        scanf("%d",&n);
        for(int i=0;i<n;++i)scanf("%d",A+i);
        for(int i=0;i<n;++i)scanf("%d",B+i);

        if(1==n){
            int g = gcd(B[0],A[0]);
            printf("Case #%d: %d %d\n",kase,B[0]/g,A[0]/g);
            continue;
        }

        int p,q,u=A[n-1],v=1;
        for(int i=n-2;i>=0;--i){
            add(A[i],B[i+1]*v,u,p,q);
            u = p;
            v = q;
        }
        int pp = B[0] * q;
        int qq = p;
        int g = gcd(pp,qq);
        printf("Case #%d: %d %d\n",kase,pp/g,qq/g);
    }
    return 0;
}
