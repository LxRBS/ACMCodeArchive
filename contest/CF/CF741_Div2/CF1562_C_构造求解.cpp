/**
 * 给一个二进制数，要求选出两段不同的区间，要求：
 * 1 区间长度均要超过一半
 * 2 区间1表示的二进制数是区间2的二进制数的k倍，k是非负整数
 * k只需考虑012即可
 * 从前往后找0，如果没有0，就是全1，直接取两个长度一样但位置不同的区间即可
 * 如果0在后半段，就可以取出1..10和1..1两段，前者是后者的二倍
 * 如果0在前半段，就可以取出0X..X和X..X，前者是后者的一倍
*/
#include <bits/stdc++.h>
using namespace std;

int N, C;
char A[20110];
int Cnt[256];

void proc1(){
    if(0==Cnt['0']){
        printf("1 %d %d %d\n", (N+1)/2, (N+1)/2, N);
        return;
    }

    int t = 0;
    while(1){
        if(A[t]=='0') break;
        ++t;
    }

    if(t<=C){
        printf("%d %d %d %d\n", t+1, N, t+2, N);
        return;
    }

    printf("1 %d 1 %d\n", t+1, t);
}

void proc2(){
    if(0==Cnt['0']){
        printf("1 %d %d %d\n", N/2, N/2+1, N);
        return;
    }

    int t = 0;
    while(1){
        if(A[t]=='0') break;
        ++t;
    }

    if(t<C){
        printf("%d %d %d %d\n", t+1, N, t+2, N);
        return;
    }

    printf("1 %d 1 %d\n", t+1, t);
}
void proc(){
    C = N >> 1;
    Cnt['0'] = Cnt['1'] = 0;
    for(char const *p=A;*p;++p){
        ++Cnt[*p];
    }

    if(N&1) proc1();
    else proc2();
}

int main(){
    // freopen("1.txt","r",stdin);
    int nofkase;
    scanf("%d", &nofkase);
    while(nofkase--){
        scanf("%d%s", &N, A);
        proc(); 
    }
    return 0;
}