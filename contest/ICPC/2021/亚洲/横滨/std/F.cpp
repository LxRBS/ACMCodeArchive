#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int maxn=1.5e5+5,Bsz=400;
int TMPS[Bsz][3][Bsz*2+5];
struct block{
	int sum,tag,odd;
	int l,r;
	int *cnt0,*cnt1;
	int *pre;
}a[Bsz];
int n,tot,v[maxn];
char s[maxn];
void updateAll(int p) {
	for(int i=-Bsz;i<=Bsz+1;i++) a[p].cnt0[i]=a[p].cnt1[i]=a[p].pre[i]=0;
	a[p].sum=a[p].odd=0;
	for(int i=a[p].l;i<=a[p].r;i++) {
		if(a[p].tag) v[i]=-v[i];
		a[p].sum+=v[i];
		if(a[p].sum%2) a[p].cnt1[a[p].sum]++;
		else a[p].cnt0[a[p].sum]++;
		a[p].pre[a[p].sum]+=a[p].sum;
	}
	for(int i=-Bsz;i<=Bsz+1;i++) {
		a[p].cnt0[i]+=a[p].cnt0[i-1];
		a[p].cnt1[i]+=a[p].cnt1[i-1];
		a[p].pre[i]+=a[p].pre[i-1];
	}
	a[p].tag=0;
}
void init() {
	for(int i=1;i<=n;i++) {
		if(i%Bsz==1) a[++tot].l=i;
		if(i%Bsz==0) a[tot].r=i;
	}
	if(a[tot].r==0) a[tot].r=n;
	for(int i=1;i<=tot;i++) {
		a[i].cnt0=TMPS[i][0]+Bsz+2;
		a[i].cnt1=TMPS[i][1]+Bsz+2;
		a[i].pre=TMPS[i][2]+Bsz+2;
	}
	for(int i=1;i<=tot;i++) updateAll(i);
}
void update(int l,int r) {
	for(int i=1;i<=tot;i++) {
		if(a[i].l<l&&l<=a[i].r) {
			for(int j=l;j<=min(r,a[i].r);j++) v[j]=-v[j];
			updateAll(i);
		} else if(l<=a[i].l&&a[i].r<=r) {
			a[i].tag^=1;
		} else if(r>=a[i].l&&r<a[i].r) {
			for(int j=max(l,a[i].l);j<=r;j++) v[j]=-v[j];
			updateAll(i);
		}
	}
}
int qrySum(int l,int r) {
	int sum=0;
	for(int i=1;i<=tot;i++) {
		if(a[i].l<l&&l<=a[i].r) {
			updateAll(i);
			for(int j=l;j<=min(r,a[i].r);j++) sum+=v[j];
		} else if(l<=a[i].l&&a[i].r<=r) {
			if(a[i].tag) sum-=a[i].sum;
			else sum+=a[i].sum;
		} else if(r>=a[i].l&&r<a[i].r) {
			updateAll(i);
			for(int j=max(l,a[i].l);j<=r;j++) sum+=v[j];
		}
	}
	return sum;
}
ll qryAns(int l,int r) {
	int sum=qrySum(l,r);
	int pre=0;
	ll minus=0,odd=0;
	if(sum>0) {
		pre=-sum;
		minus=1ll*(1+sum)*sum/2;
		odd=(sum+1)/2;
	} else {
		minus=1ll*(-sum)*(-sum-1)/2;
		odd=(-sum)/2;
	}
	ll ans=abs(sum);
	for(int i=1;i<=tot;i++) {
		if(a[i].l<l&&l<=a[i].r) {
			for(int j=l;j<=min(r,a[i].r);j++) {
				pre+=v[j];
				if(pre<0) {
					minus+=-pre;
					if(pre%2) odd++;
				}
			}
		} else if(l<=a[i].l&&a[i].r<=r) {
			int ned=-pre;
			ned=min(ned,Bsz+1);
			ned=max(ned,-Bsz-1);
			if(a[i].tag==0) {
				int s=a[i].pre[ned];
				int cnts=a[i].cnt0[ned]+a[i].cnt1[ned];
				s+=1ll*pre*cnts;
				assert(s<=0);
				if(pre%2) odd+=a[i].cnt0[ned];
				else odd+=a[i].cnt1[ned];
				minus-=s;

				pre+=a[i].sum;
			} else {
				int s=-(a[i].pre[Bsz]-a[i].pre[-ned]);
				int cnts=(a[i].r-a[i].l+1)-a[i].cnt0[-ned]-a[i].cnt1[-ned];
				s+=1ll*pre*cnts;
				assert(s<=0);
				if(pre%2) odd+=a[i].cnt0[Bsz]-a[i].cnt0[-ned];
				else odd+=a[i].cnt1[Bsz]-a[i].cnt1[-ned];
				minus-=s;

				pre-=a[i].sum;
			}
		} else if(r>=a[i].l&&r<a[i].r) {
			for(int j=max(l,a[i].l);j<=r;j++) {
				pre+=v[j];
				if(pre<0) {
					minus+=-pre;
					if(pre%2) odd++;
				}
			}
		}
	}
	assert((minus+odd)%2==0);
	return ans+(minus+odd)/2;
}
int main() {
	int Q;
	scanf("%d%d",&n,&Q);
	scanf("%s",s+1);
	for(int i=1;i<=n;i++) v[i]=s[i]=='('?1:-1;
	init();
	for(int cas=1;cas<=Q;cas++) {
		int op,l,r;
		scanf("%d%d%d",&op,&l,&r);
		if(op==1) {
			update(l,r);
		} else {
			ll ans=qryAns(l,r);
			printf("%lld\n",ans);
		}
	}
	return 0;
}