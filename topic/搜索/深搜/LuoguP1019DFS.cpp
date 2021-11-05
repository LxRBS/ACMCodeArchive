#include <bits/stdc++.h>
using namespace std;

int N;
string A[30];
char S;

int Map[30][30];

//���a�Ľ�β��b�Ŀ�ͷ�غϵĳ���
//����ж�����ֿ����غϣ�ȡ����غϳ���
int f(const string&a,const string&b){
    int na = a.length();
    int nb = b.length();
    int n = min(na,nb);
    for(int i=1;i<n;++i){
        if(a.substr(na-i)==b.substr(0,i)){
            return i;
        }
    }
    return 0;
}

int Ans = 0;
int TmpAns = 0;
int Cnt[30] = {0};

//index��ʾ��ǰ��β���ǵ�index������
void dfs(int index){

    bool flag = true;
    for(int i=0;i<N;++i){
        if(0==Map[index][i]||2==Cnt[i])continue;
        flag = false;//������ٽ�����һ�εݹ�
        //��i����index����
        TmpAns += A[i].length()-Map[index][i];
        ++Cnt[i];
        //�ݹ�
        dfs(i);
        //��ԭ
        TmpAns -= A[i].length()-Map[index][i];
        --Cnt[i];
    }

    if(flag){//һ�εݹ鶼û�У���ʾ��ͷ��
        if ( Ans < TmpAns ){
            Ans = TmpAns;
        }
    }
}

int main(){
    cin>>N;
    for(int i=0;i<N;++i)cin>>A[i];
    cin>>S;

    //���һ�����������ʿ�������һ��
    for(int i=0;i<N;++i)for(int j=0;j<N;++j){
        Map[i][j] = f(A[i],A[j]);
    }

    for(int i=0;i<N;++i)if(S==A[i][0]){
        fill(Cnt,Cnt+N,0);
        Cnt[i] = 1;
        TmpAns = A[i].length();
        dfs(i);
    }
    cout<<Ans<<endl;
    return 0;
}
