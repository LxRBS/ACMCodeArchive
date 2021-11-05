/*
    ����һ����ĳ�����
    �ٸ������ɸ�С�����Σ�
    ������ѡ����ٸ�С�����Σ�����ǡ�ø��Ǵ󳤷���
    ��ȷ����
*/

#include <stdio.h>
#include <algorithm>
using namespace std;

int const SIZE_OF_COLS = 1010;
int const SIZE_OF_ROWS = 510;
int const INF = 1000000000;

//��������
int Up[SIZE_OF_ROWS*SIZE_OF_COLS];
int Down[SIZE_OF_ROWS*SIZE_OF_COLS];
int Right[SIZE_OF_ROWS*SIZE_OF_COLS];
int Left[SIZE_OF_ROWS*SIZE_OF_COLS];
//�ڵ�i���ڵ�����
int Rth[SIZE_OF_ROWS*SIZE_OF_COLS];
int Cth[SIZE_OF_ROWS*SIZE_OF_COLS];
//�������ͷָ��
int RHead[SIZE_OF_ROWS];
//ÿһ�е�Ԫ�صĸ���
int CCnt[SIZE_OF_COLS];

int toUsed;
int Ans;

//��ʼ��DLX����ı����У�1 based
void init(int rows,int cols){
    fill(CCnt,CCnt+cols+1,0);

    for(int i=0;i<=cols;++i){
        Up[i] = Down[i] = i;//���¶�ָ���Լ�
        Right[Left[i+1] = i] = i+1;
        Cth[i] = i;         //ȷ����
    }

    Right[Left[0] = cols] = 0;
    toUsed = cols;

    fill(RHead+1,RHead+rows+2,-1);
    Ans = -1;
}

//��λ��(row,col)��Ϊ1
inline void link(int row,int col){
    Rth[++toUsed] = row;
    ++CCnt[Cth[toUsed]=col];//ȷ������

    Up[Up[Down[toUsed] = Down[col]] = toUsed] = col;
    Down[col] = toUsed;//���ڵ�������������ʾ��������ͷ����

    if( RHead[row] < 0 ){
        RHead[row] = Left[toUsed] = Right[toUsed] = toUsed;
    }else{
        int const & h = RHead[row];
        Left[Left[Right[toUsed] = Right[h]] = toUsed] = h;
        Right[h] = toUsed;//���ڵ�������������ʾ��������ͷ����
    }
}

void remove(int node){
    Left[Right[Left[node]] = Right[node]] = Left[node];//��node����������ժ��

    //��ÿһ����nodeͬ�еĽڵ�i
    for(int i=Down[node];i!=node;i=Down[i]){
        //��ÿһ����ڵ�iͬ�еĽڵ�j
        for(int j=Right[i];j!=i;j=Right[j]){
            Down[Up[Down[j]] = Up[j]] = Down[j];//��j����������ժ��
            --CCnt[Cth[j]];
        }
    }
}

void resume(int node){
    Left[Right[node]] = Right[Left[node]] = node;
    for(int i=Up[node];i!=node;i=Up[i])for(int j=Left[i];j!=i;j=Left[j])
        ++CCnt[ Cth[ Up[Down[j]] = Down[Up[j]] = j ] ];
}

//d�ǵ�ǰɾ��������
void dlx(int d){
    if(Ans != -1 && Ans <= d)return;

    if(Right[0] == 0){
        Ans = d;
        return;
    }

    int col, tmp = INF;
    //�ҵ���Ԫ�����ٵ���
    for(int i=Right[0];i!=0;i=Right[i])
        if( CCnt[i] < tmp && 1 == ( tmp = CCnt[col=i] ) ) break;

    remove(col);

    //�ӵ�col���У�ѡ��ĳһ�ڵ������н���ɾ��
    for(int i=Down[col];i!=col;i=Down[i]){
        for(int j=Right[i];j!=i;j=Right[j])remove(Cth[j]);
        dlx(d+1);
        for(int j=Left[i];j!=i;j=Left[j])resume(Cth[j]);
    }

    resume(col);
}

int N,M,P;
void read(){
    scanf("%d%d%d",&N,&M,&P);

    init(P,N*M);

    int x1,y1,x2,y2;
    for(int i=1;i<=P;++i){
        scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
        for(int x=x1;x<x2;++x)for(int y=y1;y<y2;++y){
            link(i,y*N+x+1);
        }
    }
}

int main(){
    int nofkase;
    scanf("%d",&nofkase);
    while(nofkase--){
        read();
        dlx(0);
        printf("%d\n",Ans);
    }
    return 0;
}
