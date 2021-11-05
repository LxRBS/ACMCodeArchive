//��ȷ����
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int const SIZE = 1100;

//��������
int Up[SIZE*SIZE],Down[SIZE*SIZE],Left[SIZE*SIZE],Right[SIZE*SIZE];
//��������
int Rth[SIZE*SIZE],Cth[SIZE*SIZE];
int toUsed;

//ÿһ�е�ͷָ��
int RHead[SIZE];
//ÿһ��Ԫ�صĸ���
int CCnt[SIZE];
//���
int Ans[SIZE];
int ACnt;

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
/////////////////////////////////////////////////////////////////

//01���������
void init(int row,int cols){
    fill(CCnt,CCnt+cols+1,0);

    for(int i=0;i<=cols;++i){
        Up[i] = Down[i] = i;//���¶�ָ���Լ�
        Left[i+1] = i;
        Right[i] = i + 1;
        Cth[i] = i;//ȷ����
    }
    Left[0] = cols;
    Right[cols] = 0;//ָ��ͷ���
    toUsed = cols + 1;

    RHead[0] = 0;
    fill(RHead+1,RHead+row+2,-1);//-1��ʾͷָ��Ϊ�գ�������Ϊ�գ�������1��-1������ʾ��ʱ����ֹ�����ж�

    ACnt = 0;//
}

//���к�Ϊcol�Ŀ������row
inline void link(int row,int col){
    ++CCnt[Cth[toUsed]=col];//ָ�������У���������Ԫ�ظ�����1

    Down[toUsed] = Down[col];
    Up[Down[col]] = toUsed;
    Up[toUsed] = col;
    Down[col] = toUsed;//���ڵ�������������ʾ��������ͷ����

    if ( RHead[row] < 0 ){
        RHead[row] = Left[toUsed] = Right[toUsed] = toUsed;
    }else{
        int& h = RHead[row];
        Right[toUsed] = Right[h];
        Left[Right[h]] = toUsed;
        Left[toUsed] = h;
        Right[h] = toUsed;//���ڵ�������������ʾ��������ͷ����
    }

    Rth[toUsed++] = row;//��¼toUsed���ڵ��к�
}


int N,M;
bool read(){//M��N��
    if (EOF == scanf("%d%d",&M,&N)) return false;

    init(M,N);

    for(int i=1;i<=M;++i){
        for(int j=1;j<=N;++j){
            int t;
            scanf("%d",&t);
            if (t) link(i,j);
        }
    }
    return true;
}

void remove(int node){
    Right[Left[node]] = Right[node];
    Left[Right[node]] = Left[node];//��node����������ժ��

    for(int i=Down[node];i!=node;i=Down[i]){//����
        for(int j=Right[i];j!=i;j=Right[j]){//����
            Up[Down[j]] = Up[j];
            Down[Up[j]] = Down[j];//��j����������ժ��
            --CCnt[Cth[j]];//��Ԫ�ظ�����һ
        }
    }
}

void resume(int node){
    Right[Left[node]] = Left[Right[node]] = node;//��node�Ż�������
    for(int i=Up[node];i!=node;i=Up[i]){
        for(int j=Left[i];j!=i;j=Left[j]){
            ++CCnt[Cth[Up[Down[j]]=Down[Up[j]]=j]];//��j�Ż���������Ԫ�ظ�����1
        }
    }
}

bool dlx(){
    if ( 0 == Right[0] ){//˵��ֻʣͷ��㣬�ɹ�
        return true;
    }

    int tmp = SIZE;
    int col;
    for(int i=Right[0];i!=0;i=Right[i]){
        if ( CCnt[i] < tmp ){
            tmp = CCnt[col=i];//�ҳ�Ԫ�ظ������ٵ���
            if (1 == tmp) break;
        }
    }

    remove(col);//ɾ��

    for(int i=Down[col];i!=col;i=Down[i]){
        Ans[ACnt++] = i;//����Ϊ��
        for(int j=Right[i];j!=i;j=Right[j]){
            remove(Cth[j]);//��i��Ԫ���йص���ȫ��ɾ��
        }

        if ( dlx() ){//�ݹ�
            return true;
        }

        for(int j=Left[i];j!=i;j=Left[j]){
            resume(Cth[j]);//��ԭ
        }
        --ACnt;//��ԭ
    }
    resume(col);//��ԭ
    return false;
}

int main(){
    while( read() ) {
        printf(dlx()?"Yes, I found it\n":"It is impossible\n");
    }
    return 0;
}
