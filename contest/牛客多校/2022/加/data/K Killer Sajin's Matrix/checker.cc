#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;
/*
T :
    YES
    k:
        x y
*/
void f(string &c){
    for(char &a:c)
        if('a'<=a&&a<='z')
            a-=32;
}
int main(int argc,char** argv)
{
    registerTestlibCmd(argc,argv);//初始化 checker
    int T;
    T=inf.readInt();
    inf.readEoln();
    for(int tc=1;tc<=T;tc++){
        int n,m,k;
        n=inf.readInt(1,100'000,"n"),inf.readSpace(),m=inf.readInt(1,100'000,"m"),inf.readSpace(),k=inf.readInt(1,100'000,"k");
        inf.readEoln();
        string Ans,outAns;
        Ans=ans.readWord();
        outAns=ouf.readWord("[YyEeSsNnOo]*","outAns");
        f(Ans),f(outAns);
        if(Ans!=outAns)quitf(_wa,"Wrong answer");
        ouf.readEoln();
        ans.readEoln();
        if(Ans=="NO"){
            //ouf.readEof();
            continue;
            //quitf(_ok,"yes");
        }
        typedef pair<int,int> PII;
        set<PII> se;
        vector<int> h(n+1,1),w(m+1,1);
        for(int i=1;i<=k;i++){
            int x,y;
            x=ouf.readInt(1,n,"x"),ouf.readSpace(),y=ouf.readInt(1,m,"y"),ouf.readEoln();
            ans.readInt(1,n),ans.readSpace(),ans.readInt(1,m),ans.readEoln();
            se.insert({x,y});
            h[x]^=true,w[y]^=true;
        }
        if(se.size()!=k)quitf(_wa,"There is a repeated one");
        for(int i=1;i<=n;i++)if(h[i])quitf(_wa,"There are rows or columns that are not odd");
        for(int i=1;i<=m;i++)if(w[i])quitf(_wa,"There are rows or columns that are not odd");
    }
    ans.readEof();
    ouf.readEof();
    ans.readEof();
    quitf(_ok,"The answer right");
    return 0;
}