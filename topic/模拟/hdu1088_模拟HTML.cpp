//模拟HTML
#include <cstdio>
#include <cstring>

char A[1000];
char C[85];
int IA = 0;

inline bool isTSN(char ch){
    return ' ' == ch || '\t' == ch || '\n' == ch;
}
inline bool isBr(){
    return '<' == C[0] && 'b' == C[1] && 'r' == C[2] && '>' == C[3];
}

inline bool isHr(){
    return '<' == C[0] && 'h' == C[1] && 'r' == C[2] && '>' == C[3];
}
//从A中读取单词，放在C中返回
bool getToken(){
    if ( '\0' == A[IA] ) return false;

    if ( isTSN(A[IA]) ){
        while( isTSN(A[IA]) ) ++IA;
        C[0] = ' ';
        C[1] = '\0';
        return true;
    }

    if ( '<' == A[IA] ){
        int ic = 0;
        while( '>' != A[IA] ) C[ic] = A[IA],++ic,++IA;
        C[ic] = '>';
        C[ic+1] = '\0';
        IA += 1;
        return true;
    }

    int ic = 0;
    while( '\0' != A[IA] && !isTSN(A[IA]) && '<' != A[IA] )
        C[ic] = A[IA],++ic,++IA;
    C[ic] = '\0';
    return true;
}

char B[100];
int IB = 0;



int main(){
    //freopen("1.txt","r",stdin);
    while( gets(A) ){
        IA = 0;
        while( getToken() ){
            if ( 'z' == *C ){
                int x = 5;
            }
            if ( isBr() ){
                printf("%s\n",B);
                IB = 0;
                B[0] = '\0';
            }else if ( isHr() ){
                if ( IB != 0 ){
                    printf("%s\n",B);
                    IB = 0;
                    B[0] = '\0';
                }
                for(int i=0;i<20;++i)printf("----");
                printf("\n");
            }else{
                if ( ' ' == *C ) continue;

                if ( strlen(C) + IB < 80 ){
                    if ( IB ){
                        sprintf(B+IB," ");
                        ++IB;
                    }
                    sprintf(B+IB,"%s",C);
                    IB = strlen(B);
                }else{
                    int t = strlen(B) - 1;
                    if ( ' ' == B[t] ) B[t] = '\0';
                    printf("%s\n",B);
                    sprintf(B,"%s",C);
                    IB = strlen(B);
                }
            }
        }

    }
    if ( IB ) printf("%s",B);
    printf("\n");
    return 0;
}
