/**
 * 给一个n位数，要求删掉其中某些数字，使其不是质数
 * 依次构造即可，如果包含1，4，6，8，9，直接把其他数字都删掉即可
 * 如果某个数字的数量超过了1个，则直接留下2个一模一样的数字即可
 * 如果有2或5，且不在开头，则留下2个数字即可
 * 再处理27和57即可。因为保证有解
*/
#include <bits/stdc++.h>
using namespace std;

int N;
char A[110];

void proc(){
    int cnt[256] = {0};
    for(const char *p=A;*p;++p){
        ++cnt[*p];
    }
    if(cnt['1']){
        printf("1\n1\n");
        return;
    }
    if(cnt['4']){
        printf("1\n4\n");
        return;
    }
    if(cnt['6']){
        printf("1\n6\n");
        return;
    }
    if(cnt['8']){
        printf("1\n8\n");
        return;
    }
    if(cnt['9']){
        printf("1\n9\n");
        return;
    }
    for(char ch='2';ch<='9';++ch){
        if(cnt[ch]>=2){
            printf("2\n%c%c\n", ch, ch);
            return;
        }
    }
    if(*A!='2'&&cnt['2']){
        printf("2\n%c2\n", *A);
        return;
    }
    if(*A!='5'&&cnt['5']){
        printf("2\n%c5\n", *A);
        return;
    }
    if(cnt['2']&&cnt['7']){
        printf("2\n27\n");
        return;
    }
    if(cnt['5']&&cnt['7']){
        printf("2\n57\n");
        return;
    }

    throw runtime_error("XXXX");
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