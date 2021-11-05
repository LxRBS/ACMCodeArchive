#include <bits/stdc++.h>
using namespace std;

int N;
string A[30];
char S;

int Map[30][30];

//检查a的结尾与b的开头重合的长度
//如果有多个部分可以重合，取最短重合长度
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

//index表示当前结尾的是第index个单词
void dfs(int index){

    bool flag = true;
    for(int i=0;i<N;++i){
        if(0==Map[index][i]||2==Cnt[i])continue;
        flag = false;//标记至少进行了一次递归
        //将i接在index后面
        TmpAns += A[i].length()-Map[index][i];
        ++Cnt[i];
        //递归
        dfs(i);
        //还原
        TmpAns -= A[i].length()-Map[index][i];
        --Cnt[i];
    }

    if(flag){//一次递归都没有，表示到头了
        if ( Ans < TmpAns ){
            Ans = TmpAns;
        }
    }
}

int main(){
    cin>>N;
    for(int i=0;i<N;++i)cin>>A[i];
    cin>>S;

    //检查一下哪两个单词可以连在一起
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
