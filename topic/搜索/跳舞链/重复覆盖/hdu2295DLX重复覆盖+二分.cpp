/*
    N������M�����ܵ��״�վλ�ã�
    �������ֻ�ܽ���K���״�
    ���״�����̽��뾶��ʹ��N�����ж��ڷ�Χ֮��

    ������ĳ��ж������⣺
    ���ڸ����İ뾶R���ܷ������K���״︲�����г���

    ���״ﵱ���У����е�����
    ��i���״��ܹ����ǵ�j�����У���ʾ(i,j)Ϊ1
    Ȼ����һ���ظ����ǣ�������Ҫ�����п��Ը���������
    ��������С�ڵ���K����ʾ�ð뾶����

    �����һ����������
    �뾶1000��Ȼ�Ǵ𰸣�0��Ȼ���Ǵ𰸣���һ��������������Сֵ
*/

#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;

double const EPS = 1E-9;
inline bool is0(double x){return -EPS<x&&x<EPS;}
//x<y����-1��x==y����0��x>y����1
inline int cmp(double x,double y){
    if ( is0(x-=y) ) return 0;
    return x > EPS ? 1 : -1;
}

int const SIZE = 60;
int const INF = 1000000;

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

inline double dist2(double x1,double y1,double x2,double y2){
    double x = x1 - x2;
    double y = y1 - y2;
    return x * x + y * y;
}

int N,M,K;
double XC[60],YC[60];
double XR[60],YR[60];
bool read(){
    scanf("%d%d%d",&N,&M,&K);
    for(int i=1;i<=N;++i)scanf("%lf%lf",XC+i,YC+i);
    for(int i=1;i<=M;++i)scanf("%lf%lf",XR+i,YR+i);
    return true;
}

//radiusΪ�״��̽��뾶
bool check(double radius){
    //��ʼ��ʮ������
    init(M,N);//�д����״�д������

    radius *= radius;
    //��ÿһ���״���ڰ뾶radius������£��ܹ�������Щ����
    for(int i=1;i<=M;++i){
        for(int j=1;j<=N;++j){
            if ( 1 != cmp(dist2(XR[i],YR[i],XC[j],YC[j]),radius) ){
                link(i,j);
            }
        }
    }

    //����
    dlx(0);

    return Ans <= K;
}

double proc(){
    double left = 0.0, right = 1000.0, mid;
    do{
        mid = left + ( right - left ) * 0.5;
        if ( check(mid) ) right = mid - EPS;
        else left = mid + EPS;
    }while( right - left > EPS );
    return left;
}

int main(){
    int nofkase;
    scanf("%d",&nofkase);
    while(nofkase--){
        read();
        printf("%.6f\n",proc());
    }
    return 0;
}

