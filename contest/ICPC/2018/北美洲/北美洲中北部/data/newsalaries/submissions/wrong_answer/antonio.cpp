#include <bits/stdc++.h>
using namespace std;

typedef long double ld;

#define DIV0_BUG

int32_t main() { // CURSOR START
	int n; scanf("%d",&n);
	map<ld,ld> pr_per,extr;
	ld Z=0;
	for(int i=1;i<=n;i++) {
		ld l,r; scanf("%Lf%Lf",&l,&r);
		#ifndef DIV0_BUG
		if(r-l<1e-6) {
			ld m=(l+r)/2;
			if(!pr_per.count(m)) pr_per[m]=0;
			extr[m]+=1./n;
			continue;
		}
		#endif
		ld pp=1./(n*(r-l));
		pr_per[l]+=pp;
		pr_per[r]-=pp;

		ld w=r-l;
		ld dens=pp;
		Z-=dens*dens*w*w*w/6;
	}

	ld prwt_lo=0;
	ld pr_lo=0;
	// ld Z=0;
	ld dens=0;
	ld pr=0;
	for(const auto &P:pr_per) {
		ld r=P.first;
		ld l=pr;
		ld m=(l+r)/2;
		ld w=r-l;

		ld p=dens*w;
		ld mass=m*p;

		Z+=mass*pr_lo - prwt_lo*p;
		Z+=dens*dens*w*w*w/6;
		Z+=r*extr[r]*pr_lo - prwt_lo*extr[r];

		pr=r;
		dens+=P.second;
		prwt_lo+=mass;
		prwt_lo+=r*extr[r];
		pr_lo+=p;
		pr_lo+=extr[r];
	}

	cout<<fixed<<setprecision(9)<<Z<<endl;
	// dbg(prwt_lo,Z,dens,pr_lo);
}






