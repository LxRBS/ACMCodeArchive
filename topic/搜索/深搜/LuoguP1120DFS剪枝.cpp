/**
   ���ɸ�ͬ������Сľ��������N��
   ����N�εĳ��ȣ���ԭ������С����
*/
#include <bits/stdc++.h>
using namespace std;

int N,Sum;
int A[100];
int Length,Cnt;
bool Ans;
int TT;
//Flag[i]��ʾ��i�����Ƿ�ʹ��
bool Flag[100];
//Next[i]��ʾ�������ĵ�һ����i���Ȳ�һ���Ĺ��ı��
int Next[100];

//һ��Ҫƴ��Cnt���ۣ��۳���ΪLength
//idx��ʾ��ǰƴ�ӵĲ۱�ţ���0��ʼ
//left��ʾ��ǰ��ʣ��ĳ���
//start��ʾ��Ҫ������ľ������ʼ���
void dfs(int idx,int left,int start){
    if(idx==Cnt){Ans=true;return;}

    int i = start;
    while(i<N){
        if(Flag[i]){
            ++i;
            continue;
        }
        
        //���ƴ���Ժ�ʣ�µı�A[N-1]��Ҫ�� ������ƴ
        if(((TT=left-A[i])!=0&&TT<A[N-1])) {
            i = Next[i];//��ǰ���Ȳ����ã�ֱ�ӵ���һ������
            continue;
        }
        //�ݹ�
        Flag[i] = true;
        if(TT)dfs(idx,TT,i+1);//ֱ��������ľ��
        else dfs(idx+1,Length,0);//��ͷ��ʼ
        if(Ans) return;
        //��ԭ
        Flag[i] = false;
        //���left==Length���ֲ���ƴ�ӳɹ�����˵���϶���֮ǰ������
        //���left==A[i]���ֲ���ƴ�ӳɹ�����˵��֮ǰ�϶�������
        if(left==Length||left==A[i]) return;
        i=Next[i];
    }
}

//���N�������Ƿ��ܹ�ƴ��cnt��length����
bool check(int length,int cnt){
    Length = length;
    Cnt = cnt;
    Ans = false;
    dfs(0,Length,0);
    return Ans;
}

int f(){
    for(int i=A[0];i<=Sum/2;++i){
        if(0==Sum%i&&check(i,Sum/i))return i;
    }
    return Sum;
}
int main(){
    //freopen("1.txt","r",stdin);
    scanf("%d",&N);
    int k = 0;
    for(int i=0;i<N;++i){
        int a;
        scanf("%d",&a);
        if(a<=50)A[k++]=a;
    }
    N=k;
    //�Ӵ�С�������Ŵ��
    sort(A,A+N,greater<int>());
    for(int i=0;i<N;++i){
        Next[i] = upper_bound(A,A+N,A[i],greater<int>()) - A;
    }
    Sum = accumulate(A,A+N,0);
    //�𰸱�Ȼ��A[0]��Sum֮��
    printf("%d\n",f());
    return 0;
}
