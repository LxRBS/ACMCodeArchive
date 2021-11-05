/**
    ����01���������ĵ�λ�Խ���
    ���Խ��߻��߷��Խ���
    ��DijΪ��ij��β����Խ���
    ��Dij = min(D[i-1][j-1]+1,���ϱ����1�ľ��룬��������1�ľ���)
    ���Խ�������
*/
#include <bits/stdc++.h>
using namespace std;

char Z[12500];
bool A[2510][2510];
int D[2510][2510];
//Coli��ʾ��i�����Ϊ1���б��,Rowi��ʾ��i�����Ϊ1���б��
int CurLastRow[2510],CurLastCol[2510];

int dp(int n,int m){
    int mmans = min(n,m);
    int ans = 0;
    for(int i=1;i<=n;++i)if(A[i][1])D[i][1] = 1,CurLastCol[i]=1,ans=1;
    for(int i=1;i<=m;++i)if(A[1][i])D[1][i] = 1,CurLastRow[i]=1,ans=1;

    for(int i=2;i<=n;++i)
        for(int j=2;j<=m;++j){
        if(!A[i][j]) continue;
        D[i][j] = D[i-1][j-1] + 1;
        int t = j - CurLastCol[i];
        D[i][j] = min(D[i][j],t);
        t = i - CurLastRow[j];
        D[i][j] = min(D[i][j],t);
        ans = max(ans,D[i][j]);
        if(ans==mmans) return ans;
        //����
        CurLastCol[i] = j;
        CurLastRow[j] = i;
    }
    return ans;
}

int dp2(int n,int m){
    fill(CurLastCol,CurLastCol+n+1,m+1);
    memset(CurLastRow,0,sizeof(CurLastRow));
    memset(D,0,sizeof(D));

    int mmans = min(n,m);
    int ans = 0;
    for(int i=1;i<=n;++i)if(A[i][m])D[i][m] = 1,CurLastCol[i]=m,ans=1;
    for(int i=1;i<=m;++i)if(A[1][i])D[1][i] = 1,CurLastRow[i]=1,ans=1;

    for(int i=2;i<=n;++i)
        for(int j=m-1;j>=1;--j){
        if(!A[i][j]) continue;
        D[i][j] = D[i-1][j+1] + 1;
        int t = CurLastCol[i] - j;
        D[i][j] = min(D[i][j],t);
        t = i - CurLastRow[j];
        D[i][j] = min(D[i][j],t);
        ans = max(ans,D[i][j]);
        if(ans==mmans) return ans;
        //����
        CurLastCol[i] = j;
        CurLastRow[j] = i;
    }
    return ans;
}

int main(){
    //freopen("1.txt","r",stdin);
    int n,m;
    scanf("%d%d",&n,&m);
    fgets(Z,12500,stdin);
    for(int i=1;i<=n;++i){
        fgets(Z,12500,stdin);
        char *p=Z;
        int k = 1;
        while(*p){
            if(*p=='0') A[i][k++] = false;
            else if(*p=='1')A[i][k++] = true;
            ++p;
        }
    }

    int ans = dp(n,m);
    if(ans==min(n,m)){
        printf("%d\n",ans);
    }else{
        printf("%d\n",max(ans,dp2(n,m)));
    }

    return 0;
}

