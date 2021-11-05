/*
    这个题目实际上就是求每个位置上重复次数最多的字母是什么
*/
#include <cstdio>

int M,N;
char A[100][1010];
char B[1010];
int C[128];

int main(){
    //freopen("1.txt","r",stdin);

    int nofkase;
    scanf("%d",&nofkase);

    while(nofkase--){
        scanf("%d%d",&M,&N);
        for(int i=0;i<M;++i)scanf("%s",A[i]);

        B[N] = '\0';

        int ans = 0;
        for(int i=0;i<N;++i){
            C['A'] = C['G'] = C['C'] = C['T'] = 0;
            for(int j=0;j<M;++j) ++C[A[j][i]];

            int r = C['A'];
            char ch = 'A';
            if ( r < C['C'] ) r = C['C'], ch = 'C';
            if ( r < C['G'] ) r = C['G'], ch = 'G';
            if ( r < C['T'] ) r = C['T'], ch = 'T';

            B[i] = ch;
            ans += M - r;
        }

        printf("%s\n%d\n",B,ans);
    }

    return 0;
}
