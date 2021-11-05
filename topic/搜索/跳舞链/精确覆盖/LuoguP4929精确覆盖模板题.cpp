/**
    ��ȷ����ģ����
*/
#include <stdio.h>
#include <algorithm>
using namespace std;

int const SIZE_OF_COLS = 1010;
int const SIZE_OF_ROWS = 1010;
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
int AnsRows[SIZE_OF_ROWS];

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
bool dlx(int d){
    if(Right[0] == 0){
        Ans = d;
        return true;
    }

    int col, tmp = INF;
    //�ҵ���Ԫ�����ٵ���
    for(int i=Right[0];i!=0;i=Right[i])
        if( CCnt[i] < tmp && 1 == ( tmp = CCnt[col=i] ) ) break;

    remove(col);

    //�ӵ�col���У�ѡ��ĳһ�ڵ������н���ɾ��
    for(int i=Down[col];i!=col;i=Down[i]){
        AnsRows[d] = Rth[i];
        for(int j=Right[i];j!=i;j=Right[j])remove(Cth[j]);
        if ( dlx(d+1) ) return true;
        for(int j=Left[i];j!=i;j=Left[j])resume(Cth[j]);
    }

    resume(col);
    return false;
}

int N,M;
bool read(){
    if (EOF == scanf("%d%d",&N,&M)) return false;

    init(N,M);

    int a;
    for(int i=1;i<=N;++i)for(int j=1;j<=M;++j){
        scanf("%d",&a);
        if(a) link(i,j);
    }
    return true;
}

int main(){
    //freopen("1.txt","r",stdin);
    while( read() ) {
        dlx(0);

        if ( -1 != Ans ){
            //printf("%d",Ans);
            for(int i=0;i<Ans;++i){
                printf("%d ",AnsRows[i]);
            }
            printf("\n");
        }else{
            printf("No Solution!\n");
        }
    }
    return 0;
}

/////////////////////////////////��ʾ
void dispNode(int node){
    printf("%d:(%d,%d)(%d,%d,%d,%d)\n",node,Rth[node],Cth[node],Up[node],Down[node],Left[node],Right[node]);
}
void dispRow(int row){
    int h = RHead[row];
    dispNode(h);
    for(int r=Right[h];r!=h;r=Right[r]){
        dispNode(r);
    }
}
void dispCol(int col){
    dispNode(col);
    for(int c=Down[col];c!=col;c=Down[c]){
        dispNode(c);
    }
}
void disp(char const* p){
    printf("cross:\n");
    if ('r' == *p){
        for(int r=0;RHead[r]!=-1;++r){
            dispRow(r);
        }
    }else if ('c' == *p){
        dispNode(0);
        for(int i=Right[0];i;i=Right[i]){
            dispCol(i);
        }
    }else{
        ;
    }
}
