/**
   给定4个矩形的尺寸，问能不能从中选3个拼成一个大矩形
   暴力枚举
   如果能够，只有2种可能，按行数划分
   1行，abc
   2行，ab/c
*/
#include <stdio.h>
#include <algorithm>
using namespace std;

int W[4],H[4];

//排成一行，则必然3者有同一尺寸
bool f1(int const w[],int const h[]){
    int t = w[0];
    bool flag = true;
    for(int i=1;i<3;++i){
        if(t==w[i]||t==h[i])continue;
        flag = false;
        break;
    }
    if(flag) return true;
    t = h[0];
    for(int i=1;i<3;++i){
        if(t==w[i]||t==h[i])continue;
        return false;
    }
    return true;
}

//验证w和h里面的两个数加起来是否等于dw或者dh，且剩下的两个数相等
bool f2(int const w[],int const h[],int dw,int dh){
    if(h[0]==h[1]&&(w[0]+w[1]==dw||w[0]+w[1]==dh)) return true;
    if(h[0]==w[1]&&(w[0]+h[1]==dw||w[0]+h[1]==dh)) return true;
    if(w[0]==h[1]&&(h[0]+w[1]==dw||h[0]+w[1]==dh)) return true;
    return w[0]==w[1]&&(h[0]+h[1]==dw||h[0]+h[1]==dh);
}
//排成2行，则必然2者之和等于第3者
bool f2(int const w[],int const h[]){
    for(int i=0;i<3;++i){
        int a[2],b[2],k=0;
        for(int j=0;j<3;++j)if(i!=j){
            a[k] = w[j];
            b[k++] = h[j];
        }
        if(f2(a,b,w[i],h[i])) return true;
    }
    return false;
}

//将第n个矩形拿出来，看剩下的3个能否构成大矩形
bool f(int n){
    int k = 0;
    int w[3],h[3];
    for(int i=0;i<4;++i)if(i!=n){
        w[k] = W[i];
        h[k++] = H[i];
    }
    return f1(w,h)||f2(w,h);
}
bool f(){
    for(int i=0;i<4;++i)if(f(i)){
        return true;
    }
    return false;
}

int main(){
    //freopen("1.txt","r",stdin);
    int nofkase;
    scanf("%d",&nofkase);
    while(nofkase--){
        for(int i=0;i<4;++i)scanf("%d%d",W+i,H+i);
        printf(f()?"Yes\n":"No\n");
    }
    return 0;
}
