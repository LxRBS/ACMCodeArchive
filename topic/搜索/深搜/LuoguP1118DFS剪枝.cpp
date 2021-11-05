/*
    ����һ�����У��������¼��㷽��
    1 2 3 4
     3 5 7
      8 12
       20
    ���ڣ��������������
*/
#include <bits/stdc++.h>
using namespace std;

int C[20][20];
int N,Sum;
int Flag[20] = {0};
int A[20];
int TmpAns = 0,TMax,TMin,TDiff;
bool IsOver = false;

//������С���ֵ
void f(int start){
    int a[20],b[20],k=0;
    for(int i=1;i<=N;++i)if(!Flag[i]){
        b[k] = C[N-1][start+k];
        a[k++] = i;
    }
    sort(a,a+k);
    sort(b,b+k);

    TMax=TMin=0;
    for(int i=0;i<k;++i)TMax+=a[i]*b[i],TMin+=a[i]*b[k-1-i];
}

//�Ѿ�ѡ����depth��������Ҫѡ��depth
void dfs(int depth){
    if(N==depth){
        if(TmpAns==Sum){
            IsOver = true;
            printf("%d",A[0]);
            for(int i=1;i<N;++i)printf(" %d",A[i]);
            printf("\n");
        }
        return;
    }

    for(int i=1;i<=N;++i)if(!Flag[i]){
        //ѡi
        Flag[A[depth] = i] = 1;
        TmpAns +=  C[N-1][depth] * i;
        f(depth+1);
        //ͨ����֦������
        if(TMin<=(TDiff=Sum-TmpAns)&&TDiff<=TMax){
            dfs(depth+1);
        }
        //��ԭ
        Flag[i] = 0;
        TmpAns -= C[N-1][depth] * i;
        //��������
        if(IsOver) return;
    }
}
int main(){
    //freopen("1.txt","r",stdin);
    scanf("%d%d",&N,&Sum);
    //�����������
    C[0][0] = 1;
    for(int i=1;i<=N;++i){
        C[i][0] = C[i][i] = 1;
        for(int j=1;j<i;++j) C[i][j] = C[i-1][j]+C[i-1][j-1];
    }

    dfs(0);
    return 0;
}
