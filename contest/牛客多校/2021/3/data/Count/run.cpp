//Awwawa! Dis cold yis ratten buy tEMMIE!
#include <bits/stdc++.h>
#define ll long long
#define maxn 100005 /*rem*/
#define mod 998244353
#define db double
#define vi vector<int>
#define pb push_back
#define mp make_pair
#define pi pair<int, int>
#define fi first
#define se second

template <typename T> bool chkmax(T &x,T y){return x<y?x=y,true:false;}
template <typename T> bool chkmin(T &x,T y){return x>y?x=y,true:false;}

using namespace std;
ll ksm(ll a, ll b) {
   if (!b) return 1;
   ll ns = ksm(a, b >> 1);
   ns = ns * ns % mod;
   if (b & 1) ns = ns * a % mod;
   return ns;
}

inline char nc() {
	static char buf[100000],*p1,*p2;
	return p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++;
}
int red() {
	int x=0; char s=nc();
	while(s<'0'||s>'9') s=nc();
	while(s>='0'&&s<='9') x=((x+(x<<2))<<1)+s-'0',s=nc();
	return x;
}
int rc() {
	char s=nc();
	while(s!='C'&&s!='R'&&s!='Q') s=nc();
	return s;
}
int main() {
	for (int i = 1; i <= 13; i++) {
		char s[50];
		sprintf(s, "std.exe < count%d.in > count%d.ans", i, i);
		system(s);
	}
	return 0;
}

