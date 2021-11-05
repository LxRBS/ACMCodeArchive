/**
   N��M�ľ��Ρ��ڵ�һ��ѡȡ���ɸ��㽨����ˮ��
   ˮ���Զ�����ʹ���ȥ��Ŀ����ʹ�����һ����ˮ
   �����һ���Ƿ���ȫ������ˮ������ǣ������ٵ���ˮ������
   �������û��ˮ�ĸ��������Ƕ���
   ��ÿ��Ŀ��Ϊ���������������ܷ����ӵ�Դͷ�������ѵõ�������µĴ�
   ���ڿ϶�����£�������һ����С����
   Ҳ������DP����Ϊÿһ��Դͷ���ǵ�Ŀ���Ȼ��������
*/
#include <bits/stdc++.h>
using namespace std;

int getUnsigned(){
	char ch = getchar();
	while( ch < '0' || ch > '9' ) ch = getchar();

	int ret = (int)(ch-'0');
	while( '0' <= ( ch = getchar() ) && ch <= '9' ) ret = ret * 10 + (int)(ch-'0');
	return ret;
}


const int SIZE = 501;
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

//��ʼ����01����Ĵ�СΪrows��cols,1 based
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

int const DR[] = {-1,1,0,0};
int const DC[] = {0,0,-1,1};

int N,M;
int A[510][510];
int CurCol;
bool Used[501][500];
bool IsOK;

void dfs(int r,int c){
    Used[r][c] = true;

    if(0==r){//�ҵ�һ��Դͷ
        //��c��Դͷ���Ը��ǵ�CurCol��Ŀ��
        link(c+1,CurCol+1);
        IsOK = true;
    }

    for(int i=0;i<4;++i){
        int nr = r + DR[i];
        int nc = c + DC[i];
        if(0<=nr&&nr<N&&0<=nc&&nc<M&&!Used[nr][nc]&&A[r][c]<A[nr][nc]){
            dfs(nr,nc);
        }
    }
}

int main(){
    //freopen("1.txt","r",stdin);
    N = getUnsigned();
    M = getUnsigned();
    for(int i=0;i<N;++i)for(int j=0;j<M;++j){
        A[i][j] = getUnsigned();
    }

    init(M,M);

    int cnt = 0;
    //���յ㿪ʼ���������ܴ�������ˮ
    for(CurCol=0;CurCol<M;++CurCol){
        memset(Used,0,sizeof(Used));
        IsOK = false;
        dfs(N-1,CurCol);
        if(!IsOK) ++cnt;
    }

    if(cnt){
        printf("0\n%d\n",cnt);
        return 0;
    }

    dlx(0);
    printf("1\n%d\n",Ans);

    return 0;
}
