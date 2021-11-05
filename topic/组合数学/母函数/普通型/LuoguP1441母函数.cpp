/**
   N�����룬�õ�M�������ܹ��Ƴ��Ĳ�ͬ��������ж��ٸ�
   NС�ڵ���20��MС�ڵ���4
   ����ȡ�����п��ܵ���ϣ���ÿһ������ʹ��ĸ�������
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

int N,M,K;
int A[20],C[20];
int Cnt[110];
//B���汣��������������
int B[5];
int Ans;
int Sum;

int X[2100],Y[2100];

//��C��ȥ��B�е����룬����ƴ���ٸ���ͬ������
int f(){
    //��C��ȡ��B
    for(int i=0;i<M;++i)--Cnt[B[i]], Sum-=B[i];

    fill(X,X+Sum+1,0);
    fill(Y,Y+Sum+1,0);

    //X���ڱ���ĸ�������˵Ľ��,Y���ڱ�����ʱ���
    X[0] = 1;
    int c,w;
    for(int i=0;i<K;++i)if(c=Cnt[w=C[i]]){
        for(int j=0;j<=Sum;++j)for(int k=0,n=min(Sum-j,c*w);k<=n;k+=w){
            Y[j+k] += X[j];
        }

        copy(Y,Y+Sum+1,X);
        fill(Y,Y+Sum+1,0);
    }

    //ͳ�ƴ�
    int ans = 0;
    for(int i=1;i<=Sum;++i)if(X[i])++ans;

    //��ԭ
    for(int i=0;i<M;++i)++Cnt[B[i]], Sum+=B[i];

    return ans;
}

//start��ʾ��ѡ����㣬cnt��ʾ�Ѿ�ѡ��cnt��
void dfs(int start,int cnt){
    if(cnt==M){
        Ans = max(Ans,f());
        return;
    }
    for(int i=start;i<N-M+cnt+1;++i){
        B[cnt] = A[i];
        dfs(i+1,cnt+1);
    }
}

int main(){
    //freopen("1.txt","r",stdin);
    N = getUnsigned();
    M = getUnsigned();
    for(int i=0;i<N;++i)++Cnt[A[i]=getUnsigned()], Sum+=A[i];

    K = 0;
    bool flag[110] = {false};
    for(int i=0;i<N;++i)if(!flag[A[i]]){
        flag[A[i]] = true;
        C[K++] = A[i];
    }

    if(0==M){
        printf("%d\n",f());
        return 0;
    }

    for(int i=0;i<N-M+1;++i){
        B[0] = A[i];
        dfs(i+1,1);
    }

    printf("%d\n",Ans);
    return 0;
}
