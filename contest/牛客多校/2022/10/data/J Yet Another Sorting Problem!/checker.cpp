#include <bits/stdc++.h>
#include "testlib.h"
 
using namespace std;
 
int n,a[207],b[207],p[207],q[207];
bool vis[207][207]; 
inline int readAndCheckAnswer(int tt, InStream& in) {
	auto result=in.readToken("YES|NO");
	if (result=="NO") return -1;
	for (int i=1;i<=n;++i) a[i]=b[i], p[i]=q[i];
	for (int i=1;i<=n;++i) for (int j=1;j<=n;++j) vis[i][j]=0;
	for (int i=0;i<n*(n-1)/2;++i){
		int x=in.readInt(1,n);
		int y=in.readInt(1,n);
		if (x==y) in.quitf(_wa,"Operation %d is invalid: (%d, %d).",i,x,y);
		if (vis[x][y]) in.quitf(_wa,"Operation %d is invalid: (%d, %d) appears at least twice.",i,x,y);
		swap(a[x],a[y]);
		vis[x][y]=vis[y][x]=1;
	}
	for (int i=1;i<=n;++i) if (a[i]!=p[i]) in.quitf(_wa,"Failed to generate the desired permutation: expected %d at postiion %d, found %d",p[i],i,a[i]);
	return 0;
}
 
int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);
    int testcases = inf.readInt();
    for (int t=1;t<=testcases;++t){
        //setTestCase(t);
        n = inf.readInt();
        for(int i=1;i<=n;++i) b[i]=inf.readInt();
        for(int i=1;i<=n;++i) q[i]=inf.readInt();
 
        int ja = readAndCheckAnswer(t,ans);
        int pa = readAndCheckAnswer(t,ouf);
 
        if(ja != -1 && pa == -1)
            quitf(_wa, "Jury has the answer but participant has not");
        if(ja == -1 && pa != -1)
            quitf(_fail, "Participant has the answer but jury has not");
    }
    quitf(_ok, "Correct Solution!");
}
