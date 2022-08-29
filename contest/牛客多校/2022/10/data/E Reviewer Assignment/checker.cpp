#include <bits/stdc++.h>
#include "testlib.h"
#define MAXN 405
 
using namespace std;
 
int n,m;
string str[MAXN];
int ja[MAXN],pa[MAXN];
vector<int> readAndCheckAnswer(InStream& in) {
    vector<int> ret(n+1,0),cnt(m,0); 
    int x=in.readInt(-1,m,"x");
    // printf("x=%d\n",x);
	if (x==-1) {ret[0]=-1; return ret;}
    else if(x==0) in.quitf(_wa,"wrong format, 0 received");
    else 
    {
        if(str[1][x-1]=='0') in.quitf(_wa,"%d %d assignment not allowed",1,x);
        else cnt[x-1]++;
    }
    // puts("done1");
    for(int i=2;i<=n;i++)
    {
        x=in.readInt(1,m,"x");
        // printf("i=%d x=%d\n",i,x);
        if(str[i][x-1]=='0') in.quitf(_wa,"%d %d assignment not allowed",i,x);
        else cnt[x-1]++;
    }
    // puts("done2");
    for(int i=0;i<m;i++) ret[cnt[i]]++;
    for (int j=n;j>0;--j) ret[j-1]+=ret[j];
	return ret;
}
 
int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);
 
	n = inf.readInt();
    m = inf.readInt();
    inf.readEoln();
	for (int i=1;i<=n;i++) str[i]=inf.readString();
    vector<int> ja = readAndCheckAnswer(ans);
    vector<int> pa = readAndCheckAnswer(ouf);
    assert(ja.size()>=1);
    assert(pa.size()>=1);
    if(ja[0] != -1 && pa[0] == -1)
        quitf(_wa, "Jury has the answer but participant has not");
    if(ja[0] == -1 && pa[0] != -1)
        quitf(_fail, "Participant has the answer but jury has not");
    for(int i=1;i<=n;i++)
    {
        if(ja[i]>pa[i])
        {
            quitf(_wa, "Jury has better assignment");
        }
        else if(ja[i]<pa[i])
        {
            for (int i=1;i<=n;++i){
                printf("%d %d %d\n",i,ja[i],pa[i]);
            }
            quitf(_fail, "Participant has better assignment");
        }
    }
    quitf(_ok, "n=%d", n);
}
