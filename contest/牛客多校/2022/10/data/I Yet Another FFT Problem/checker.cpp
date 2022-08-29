#include <bits/stdc++.h>
#include "testlib.h"
#define MAXN 1000005
 
using namespace std;
 
int n,m;
int a[MAXN],b[MAXN];
inline int readAndCheckAnswer(InStream& in) {
	int i,j,k,l;
    i=in.readInt(-1,n);
	if (i==-1) return -1;
    if(i==0) in.quitf(_wa,"wrong form of output");
    j=in.readInt(1,n); k=in.readInt(1,m); l=in.readInt(1,m);
    if(i==j||k==l) in.quitf(_wa,"repeated indices");
    // if(i>j||k>l) in.quitf(_wa,"wrong order of indices");
    if(max(a[i]-a[j],a[j]-a[i])!=max(b[k]-b[l],b[l]-b[k])) in.quitf(_wa,"output doesn't make equal difference'");
	return 0;
}
 
int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);
 
	n = inf.readInt();
    m = inf.readInt();
	for (int i=1;i<=n;i++) a[i]=inf.readInt();
    for (int i=1;i<=m;i++) b[i]=inf.readInt();
    int ja = readAndCheckAnswer(ans);
    int pa = readAndCheckAnswer(ouf);
    if(ja != -1 && pa == -1)
        quitf(_wa, "Jury has the answer but participant has not");
    if(ja == -1 && pa != -1)
        quitf(_fail, "Participant has the answer but jury has not");
    quitf(_ok, "n=%d", n);
}
 
