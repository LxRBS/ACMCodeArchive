#include <cstdio>
#include <cstring>

int const SIZE = 100010;
char A[SIZE],B[SIZE];

int main(){
    //freopen("1.txt","r",stdin);

    while( EOF != scanf("%s%s",A,B) ){
        int la = strlen(A), lb = strlen(B);

        if ( la > lb ){
            printf("No\n");
            continue;
        }

        bool ans = false;
        int k = 0;
        for(int b=0;b<=lb;++b){        //����ƥ��A�е���ĸ������һ��̰�Ĳ���
            if ( B[b] == A[k] ) ++k;
            if ( la + 1 == k ) ans = true;
        }

        printf(ans?"Yes\n":"No\n");   //printf������һ���������ʽ��?:�����������
    }

    return 0;
}
