#include<stdio.h>
#include<cstring>
#include<algorithm>
#include<vector>
#include<map>
#include<assert.h>
#include<set>
#include<cmath>
#include<queue>
#include<cstdlib>
#include<iostream>
#include<bitset>
#include "testlib.h"
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
#define rep(i,j,k) for(int i=(int)(j);i<=(int)(k);i++)
#define per(i,j,k) for(int i=(int)(j);i>=(int)(k);i--)
using namespace std;
typedef long long LL;
typedef double db;
int lcs(string a,string b){
	static int f[1005][1005];
	int ans=0;
	memset(f,0,sizeof f);
	rep(i,0,a.size()-1)rep(j,0,b.size()-1){
		if(a[i]==b[j])f[i+1][j+1]=max(f[i+1][j+1],f[i][j]+1);
		f[i+1][j]=max(f[i+1][j],f[i][j]);
		f[i][j+1]=max(f[i][j+1],f[i][j]);
	}
	rep(i,0,a.size())rep(j,0,b.size())ans=max(ans,f[i][j]);
	return ans;
}
int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);
    int a,b,c,n;
	a=inf.readInt();
	b=inf.readInt();
	c=inf.readInt();
	n=inf.readInt();

	string fline=ans.readLine("[a-zA-Z]{1,1000}");
	if(fline=="NO"){
		string w=ouf.readLine("[a-zA-Z]{1,1000}");
		if(w!="NO"){
			quitf(_wa,"no solution but you have");
		}
		else quitf(_ok,"fine");
	}
	else{
		string s1=ouf.readLine("[a-z]{1,1000}");
		string s2=ouf.readLine("[a-z]{1,1000}");
		string s3=ouf.readLine("[a-z]{1,1000}");
		if(s1.size()!=n)quitf(_wa,"s1 size not equal to n");
		if(s2.size()!=n)quitf(_wa,"s2 size not equal to n");
		if(s3.size()!=n)quitf(_wa,"s3 size not equal to n");

		if(lcs(s1,s2)!=a)quitf(_wa,"lcs(s1,s2)!=a");
		if(lcs(s2,s3)!=b)quitf(_wa,"lcs(s2,s3)!=b");
		if(lcs(s1,s3)!=c)quitf(_wa,"lcs(s1,s3)!=c");
		quitf(_ok,"fine");
	}
}


