/*
    ������������ɸ�����
    ÿ�ι������Թ�����һ��С����
    ������Ҫ�������ٴ�

    ��ÿһ�ι���������һ�У������������ɸ�1��ʾԴ�����еĹ���
    ����ѡ������п��԰����е�1����ס
    �ظ�����
*/

#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;

const int SIZE = 300;
const int INF = 1000000000;

//��������
int Up[SIZE*SIZE],Down[SIZE*SIZE],Right[SIZE*SIZE],Left[SIZE*SIZE];
//��������
int Rth[SIZE*SIZE],Cth[SIZE*SIZE];
//ÿһ�е�ͷָ��
int RHead[SIZE];
//ÿһ��Ԫ�صĸ���
int CCnt[SIZE];
int toUsed;
int Ans;

//��ʼ����01����Ĵ�СΪrows��cols
void init(int rows,int cols){
    fill(CCnt,CCnt+cols+1,0);
    for(int i = 0;i <= cols;++i){
        Up[i] = Down[i] = i;//���¶�ָ���Լ�
        Left[i+1] = i;
        Right[i] = i+1;
    }
    Right[cols] = 0; Left[0] = cols;
    toUsed = cols;

    RHead[0] = 0;
    fill(RHead+1,RHead+rows+2,-1);
    Ans = INF;
}

//��λ��(row,cols)��Ϊ1
inline void link(int row,int col){
    ++CCnt[Cth[++toUsed]=col];//ָ�������У���������Ԫ�ظ�����1
    Rth[toUsed] = row;        //ָ��������

    Down[toUsed] = Down[col];
    Up[Down[col]] = toUsed;
    Up[toUsed] = col;
    Down[col] = toUsed;  //���ڵ�������������ʾ��������ͷ����

    if(RHead[row] < 0){
        RHead[row] = Left[toUsed] = Right[toUsed] = toUsed;
    }else{
        int const&h = RHead[row];
        Right[toUsed] = Right[h];
        Left[Right[h]] = toUsed;
        Right[Left[toUsed] = h] = toUsed;//���ڵ�������������ʾ��������ͷ����
    }
}

//ɾ��node�ڵ��ͬ�нڵ�
void remove(int node){
    for(int i = Down[node];i != node;i = Down[i])
        Left[Right[i]] = Left[i], Right[Left[i]] = Right[i];
}

//�ָ�node�ڵ��ͬ�нڵ�
void resume(int node){
    for(int i = Up[node];i != node;i = Up[i])
        Left[Right[i]] = Right[Left[i]] = i;
}

bool Flag[SIZE] = {false};

//���ۺ��������ٻ�Ҫɾ���ٴΣ�
int f(){
    int ret = 0;
    //����������Ȼ���ڵĽڵ���Ϊtrue
    for(int i = Right[0]; i != 0;i = Right[i])Flag[i] = true;

    //���ڱ������е�ÿһ���ڵ�
    for(int i = Right[0]; i != 0;i = Right[i])if(Flag[i]){
        ret++;
        Flag[i] = false;

        //ͬһ�е���ȫ����Ϊfalse��������
        for(int j = Down[i];j != i;j = Down[j])for(int k = Right[j];k != j;k = Right[k])
            Flag[Cth[k]] = false;
    }

    return ret;
}

//d�Ѿ�ɾ��������
void dlx(int d){
    if(d + f() >= Ans)return;
    if(Right[0] == 0){
        if(d < Ans)Ans = d;
        return;
    }

    //����Ԫ�����ٵ���
    int col,tmp = INF;
    for(int i=Right[0];i!=0;i=Right[i]){
        if ( CCnt[i] < tmp && 1 == (tmp = CCnt[col=i]) ) break;
    }

    //�Ե�col�е�ÿһ��
    for(int i = Down[col];i != col;i = Down[i]){
        //ɾ��i�����е�ȫ���ڵ�
        remove(i);
        for(int j = Right[i];j != i;j = Right[j])remove(j);

        dlx(d+1);

        //�ָ�
        for(int j = Left[i];j != i;j = Left[j])resume(j);
        resume(i);
    }
}

int N,M,NN,MM;
int A[20][20];
//int id[20][20];

bool read(){
    if ( 2 != scanf("%d%d",&N,&M) ) return false;

    int sz = 0;
    for(int i=0;i<N;++i)for(int j=0;j<M;++j){
        scanf("%d",A[i]+j);
        if( 1 == A[i][j] ) A[i][j] = (++sz);
    }
    scanf("%d%d",&NN,&MM);

    init((N-NN+1)*(M-MM+1),sz);

    sz = 1;
    for(int i=0;i<=N-NN;++i)for(int j=0;j<=M-MM;++j){
        for(int x=i,n=i+NN;x<n;++x)for(int y=j,m=j+MM;y<m;++y){
            if(A[x][y]) link(sz,A[x][y]);
        }
        sz++;
    }

    return true;
}

int main(){
    while( read() ){
        dlx(0);
        printf("%d\n",Ans);
    }
    return 0;
}
