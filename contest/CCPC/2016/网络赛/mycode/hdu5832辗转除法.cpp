//һ���ر����������ǲ���137��73�Ĺ�����
#include <stdio.h>
char A[10000010];

bool f(){
    int ans = 0;
    for(char*p=A;*p;++p){
        ans = ( ans * 10 + ( *p - '0' ) ) % 10001;
    }
    return 0 == ans;
}
int main(){
    int n;
    for(int kase=1;EOF!=scanf("%s",A);++kase){
        printf("Case #%d: ",kase);
        printf(f()?"YES\n":"NO\n");
    }
    return 0;
}
