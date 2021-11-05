/*
    M��N�ĸ��ӣ�ÿ�������кڰ���ɫ
    ��ʼ��һ��״̬
    ÿ��һ�����ӻ�ͬʱ������������
    ����ô�����ܽ����и��Ӷ���ɰ�ɫ
    ����ж�⣬����ֵ���С��

    ��˹��Ԫ�������жϽ�����������Ǻ���ȷ���ֵ���С�Ľ�
    ʵ���ϸ������໥������
    �����ȷ����һ������η�ת�ģ���ô����ÿһ�еķ�ת��ȷ����
    ������ٵ�һ�е����п��ܵķ�ת���
    ʹ��״̬ѹ������ʾ��ת���
*/

#include <stdio.h>
#include <string.h>

int M,N;
int A[17][17];
int B[17][17];
int C[17][17];
int Ans;

int const DR[] = {-1,1,0,0};
int const DC[] = {0,0,-1,1};

void flip(int r,int c){
    A[r][c] ^= 1;
    for(int i=0;i<4;++i){
        int dr = r + DR[i];
        int dc = c + DC[i];
        if ( 0 <= dr && dr < M && 0 <= dc && dc < N ) A[dr][dc] ^= 1;
    }
}

void proc(int status){
    //��B������A
    memcpy(A,B,sizeof(B));

    int tmp[17][17] = {0};

    int cnt = 0;

    //���ȴ����0��
    for(int i=0;i<N;++i){
        if ( (1<<i) & status ){
            flip(0,i);
            tmp[0][i] = 1;
            ++cnt;
        }
        if ( Ans <= cnt ) return;
    }

    //1~M-1��
    for(int i=1;i<M;++i){
        //ÿһ��
        for(int j=0;j<N;++j){
            if ( A[i-1][j] ){
                flip(i,j);
                tmp[i][j] = 1;
                ++cnt;
            }
        }
        if ( Ans <= cnt ) return;
    }

    //������һ��
    for(int i=0;i<N;++i)if(A[M-1][i]) return;
    Ans = cnt;
    memcpy(C,tmp,sizeof(tmp));
}

int main(){
    //freopen("1.txt","r",stdin);
    scanf("%d%d",&M,&N);
    for(int i=0;i<M;++i)for(int j=0;j<N;++j)scanf("%d",B[i]+j);

    //��ÿһ��״̬i��1����ת
    //������˳��ͷ����ֵ���
    Ans = 3000;
    for(int i=0;i<(1<<N);++i){
        proc(i);
    }

    //�����
    if ( 3000 == Ans ){
        printf("IMPOSSIBLE\n");
        return 0;
    }

    //printf("%d\n",Ans);
    for(int i=0;i<M;++i){
        printf("%d",C[i][0]);
        for(int j=1;j<N;++j)printf(" %d",C[i][j]);
        putchar('\n');
    }
    return 0;
}
