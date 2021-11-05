/**
    N�����У����ֳ�r����
    ͬһ���ݵĳ���֮��ĵ�·��Ϊ�ڲ���·
    Ҫ��ÿ�������������ڲ���·Ϊż��
    ��������������С��r�Ƕ��٣����Ҹ�������
    NΪ2000
    ����r=2���������xiΪ��i���������Ĳ��֣���xiȡֵ��ΧΪ0��1
    ���ڶ���Ϊż���ĵ㣬�����ڵ��SIGMA(xj)=0
    ���ڶ���Ϊ�����ĵ㣬�����ڵ��SIGMA(xj)=1+xi
    ����֤���÷���һ���н⣬���Դ𰸲���1����2
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

int N,M;
int Deg[2020];

///�ж�1�������Ƿ����
bool isOK1(){
    for(int i=1;i<=N;++i)if(Deg[i]&1)return false;
    return true;
}

int const SIZE_OF_COLUMN = 2001;

//a���������x�ǽ�
//cntOfEq�Ƿ��̵ĸ�����cntOfUnknown��δ֪���ĸ���
int Gauss(int(*a)[SIZE_OF_COLUMN],int x[],int cntOfEq,int cntOfUnknown){
    int row = 0, col = 0;
    for(;row<cntOfEq&&col<cntOfUnknown;++row,++col){
        //������Ԫ���˴�Ϊ1����
        int maxr = row;
        while( maxr < cntOfEq && 0 == a[maxr][col] ) ++maxr;

        //���е�row�м�����ȫΪ0����Ҫ���ǵ�row�е���һ��
        if ( maxr == cntOfEq ) {
            --row;
            continue;
        }

        //����
        if ( maxr != row ){
            for(int j=col;j<=cntOfUnknown;++j){
                swap(a[row][j],a[maxr][j]);
            }
        }

        //����row�����µ��еĵ�col������
        for(int i=row+1;i<cntOfEq;++i)if(a[i][col]){
            for(int j=col;j<=cntOfUnknown;++j){
                a[i][j] ^= a[row][j];
            }
        }
    }

    //disp(a,cntOfEq,cntOfUnknown);

    //*
    //���ȫ0�е��������Ƿ�ҲΪ0
    for(int i=row;i<cntOfEq;++i){
        if ( a[i][col] ) return -1;//�޽�
    }//*/

    //�õ�����һ����
    for(int i=cntOfEq-1;i>=0;--i){
        //��ÿһ��ȡ��һ��δ֪��
        //������Ҫô�Ѿ����,Ҫô�����ɱ�Ԫ��ȡ0
        int k = i;
        while(k<cntOfUnknown&&a[i][k]==0) ++k;
        if(k==cntOfUnknown) continue;

        x[k] = a[i][cntOfUnknown];
        for(int j=k+1;j<cntOfUnknown;++j){
            x[k] ^= ( x[j] && a[i][j] );
        }
    }

    return cntOfUnknown - row;//���ر�Ԫ�ĸ���������Ϊ0��Ψһ��
}

int A[SIZE_OF_COLUMN][SIZE_OF_COLUMN];
int X[SIZE_OF_COLUMN];
vector<int> Graph[SIZE_OF_COLUMN];

int main(){
    //freopen("1.txt","r",stdin);
    int nofkase = getUnsigned();
    while(nofkase--){
        fill(Deg,Deg+(N = getUnsigned())+1,0);
        M = getUnsigned();
        for(int i=1;i<=N;++i)Graph[i].clear();

        for(int a,b,i=0;i<M;++i){
            ++Deg[a = getUnsigned()];
            ++Deg[b = getUnsigned()];
            Graph[a].push_back(b);
            Graph[b].push_back(a);
        }

        ///���1�������Ƿ����
        if(isOK1()){
            puts("1");
            putchar('1');
            for(int i=2;i<=N;++i)putchar(' '),putchar('1');
            puts("");
            continue;
        }

        ///�з���
        for(int i=0;i<N;++i)fill(A[i],A[i]+N+1,0);
        fill(X,X+N,0);

        for(int i=1;i<=N;++i){
            if(Deg[i]&1){//����
                for(auto v: Graph[i]){
                    A[i-1][v-1] = 1;
                }
                A[i-1][i-1] = A[i-1][N] = 1;
            }else{//ż��
                for(auto v: Graph[i]){
                    A[i-1][v-1] = 1;
                }
            }
        }

        ///�ⷽ��
        int t = Gauss(A,X,N,N);
        if(t==-1) throw runtime_error("XXXX");
        ///���
        puts("2");
        printf("%d",X[0]?1:2);
        for(int i=1;i<N;++i){
            printf(" %d",X[i]?1:2);
        }
        puts("");
    }
    return 0;
}
