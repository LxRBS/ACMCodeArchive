#include <cstdio>
#include <cctype>
#define MN 100000

using ll = __int128;
using ld = long double;

namespace GTI
{
	char gc(void)
   	{
		const int S = 1 << 16;
		static char buf[S], *s = buf, *t = buf;
		if (s == t) t = buf + fread(s = buf, 1, S, stdin);
		if (s == t) return EOF;
		return *s++;
	}
	ll gti(void)
   	{
		ll a = 0, b = 1, c = gc();
		for (; !isdigit(c); c = gc()) b ^= (c == '-');
		for (; isdigit(c); c = gc()) a = a * 10 + c - '0';
		return b ? a : -a;
	}
	int gts(char *s)
   	{
		int len = 0, c = gc();
		for (; isspace(c); c = gc());
		for (; c != EOF && !isspace(c); c = gc()) s[len++] = c;
		s[len] = 0;
		return len;
	}
	int gtl(char *s)
   	{
		int len = 0, c = gc();
		for (; isspace(c); c = gc());
		for (; c != EOF && c != '\n'; c = gc()) s[len++] = c;
		s[len] = 0;
		return len;
	}
}
using GTI::gti;
using GTI::gts;
using GTI::gtl;

int a[MN+5];

void solve(){
	int n;
	ll s_xy=0,s_x=0,s_y=0,s_x2=0;
	n = gti();
	for(int i=1;i<=n;i++){
		a[i] = gti();
		s_xy += (ll)i*a[i];
		s_x += i;
		s_y += a[i];
		s_x2 += (ll)i*i; 
	}
	ld k = (ld)(n*s_xy-s_x*s_y)/(n*s_x2-(s_x)*(s_x));
	ld b = ((ld)s_y/n)-k*((ld)s_x/n);
	ld ans = 0;
	for(int i=1;i<=n;i++){
		ld y = k*i+b;
		ans += (y-a[i])*(y-a[i]);
	}
	printf("%.15Lf\n",ans);
}

int main(){
	int T;
	T = gti();
	while(T--) solve();
}
