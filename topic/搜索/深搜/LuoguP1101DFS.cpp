#include <bits/stdc++.h>
using namespace std;

int N;
char A[110][110];
int F[256] = {0};
bool G[110][110] = {false};//Ϊ���ʾijλ�õ���ĸ��Ҫ����

bool f(int r,int c,int dr,int dc){
    //�ݹ��������
    if('g'==A[r][c]) {
        G[r][c] = true;
        return true;
    }

    int nr = r + dr;
    int nc = c + dc;
    if(nr<0||nr>=N||nc<0||nc>=N)return false;

    bool flag = false;
    if(F[A[r][c]] == A[nr][nc]) flag = f(nr,nc,dr,dc);
    if(flag) G[r][c] = true;
    return flag;
}

int main(){
    //freopen("1.txt","r",stdin);
    F['y']='i';
    F['i']='z';
    F['z']='h';
    F['h']='o';
    F['o']='n';
    F['n']='g';
    F['g']=1;

    scanf("%d",&N);
    for(int i=0;i<N;++i)scanf("%s",A[i]);

    //����һ��Ԥ����
    for(int i=0;i<N;++i)for(int j=0;j<N;++j)if(!F[A[i][j]])A[i][j] = '*';

    //��ÿһ������8�����������
    for(int i=0;i<N;++i)for(int j=0;j<N;++j)if('y'==A[i][j]){
        bool flag = false;
        flag |= f(i,j,-1,0);//��
        flag |= f(i,j,1,0);//��
        flag |= f(i,j,0,-1);//��
        flag |= f(i,j,0,1);//��
        flag |= f(i,j,-1,-1);//����
        flag |= f(i,j,1,-1);//����
        flag |= f(i,j,-1,1);//����
        flag |= f(i,j,1,1);//����
        G[i][j] = flag;
    }

    //��һ������
    for(int i=0;i<N;++i)for(int j=0;j<N;++j)if(!G[i][j])A[i][j]='*';
    //���
    for(int i=0;i<N;++i)printf("%s\n",A[i]);
    return 0;
}
