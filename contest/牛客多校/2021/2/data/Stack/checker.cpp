#include"testlib.h"
#include<bits/stdc++.h>
#define For(a,b,c) for(int a=b;a<=c;++a)
#define Dor(a,b,c) for(int a=b;a>=c;--a)
#define CC(_...) fprintf(stderr,_)
using namespace std;
typedef long long LL;
enum{N=1000007};
int A[N],C[N],S[N];
int main(int argc, char* argv[]) {
    registerTestlibCmd(argc,argv);
	int n=inf.readInt(),k=inf.readInt();
	int a=ans.readInt(-1,n);
	if(a<0) {
		ouf.readInt(-1,-1);
		quitf(_ok,"ok");
		exit(0);
	}
	For(i,1,k) {
		int x=inf.readInt(),y=inf.readInt();
		A[x]=y;
	}
	int t=0;
	For(i,1,n) {
		int a=ouf.readInt(1,n);
		if(a<1 || a>n) quitf(_wa,"wa");
		++C[a];
		while(t&&a<S[t]) --t;
		S[++t]=a;
		if(A[i]&&t!=A[i]) quitf(_wa,"wa");
	}
	For(i,1,n) if(!C[i]) quitf(_wa,"wa");
	quitf(_ok,"ok");
	return 0;
}
