#include<bits/stdc++.h>

using namespace std;
typedef long long ll;
const int maxn=500005;
const int N=26;
 
struct Palindromic_Tree{
    int next[maxn][26], fail[maxn], cnt[maxn], num[maxn], len[maxn], S[maxn];
    int last, n, p;
    int get(int l){
        for(int i=0;i<N;i++) 
            next[p][i]=0;
        cnt[p]=0;
        num[p]=0;
        len[p]=l;
        return p++;
    }

    void init(void){
        p=0;
        get(0);
        get(-1);
        last=0;
        n=0;
        S[n]=-1;
        fail[0]=1;
    }
    int get_fail(int x){
        while(S[n-len[x]-1]!=S[n]) 
            x=fail[x];
        return x;
    }
 
    int add(int c){
        S[++n]=c;
        int cur=get_fail(last);
        if (!next[cur][c])
        {
            int now=get(len[cur]+2);
            fail[now]=next[get_fail(fail[cur])][c];
            next[cur][c]=now;
            num[now]=num[fail[now]]+1;
        }
        last=next[cur][c];
        cnt[last]++;
        return num[last];
    }
}pam;

signed main() {
    int n;
    cin>>n;
    pam.init();
    string str;
    cin>>str;
    long long cntk=0;
    long long cntf=0;
    long long cntc=0;
    int len=n;
    int last=0;

    for(int i=0;i<len;i++) {
        last=pam.add(int(str[i])-97);
        if(str[i]=='k')
            cntk+=ll(last);
        if(str[i]=='f')
            cntf+=ll(last);
        if(str[i]=='c')
            cntc+=ll(last);
    }
    cout<<cntk<<" "<<cntf<<" "<<cntc<<endl;
    return 0;
}
