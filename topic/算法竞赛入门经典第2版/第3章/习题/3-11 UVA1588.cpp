/*
    这个题目实际上就是要求：对每个位置a的高度加b的高度要小于4。a和b不一定要对齐
    注意用字符串读入，所以不是小于4或者小于'4'，而是小于'2'+'2'
*/
#include <cstdio>
#include <cstring>

int const TT = '2' + '2';

char A[110],B[110];

bool isOK(int idx,char a[],int la,char b[],int lb){
    for(int i=idx,j=0;i<la&&j<lb;++i,++j){
        int t = a[i] + b[j];
        if ( t >= TT ) return false;
    }
    return true;
}

int proc(char a[],char b[]){
    int la = strlen(a);
    int lb = strlen(b);

    int r = la + lb;
    for(int i=0;i<la;++i){
        if ( !isOK(i,a,la,b,lb) ) continue;

        int t = la;
        if ( lb > la - i ) t += lb - ( la - i );
        if ( t < r ) r = t;
    }
    return r;
}

int main(){
    //freopen("1.txt","r",stdin);
    while( EOF != scanf("%s%s",A,B) ){
        int a = proc(A,B);
        int b = proc(B,A);
        printf("%d\n",a<b?a:b);
    }
    return 0;
}
