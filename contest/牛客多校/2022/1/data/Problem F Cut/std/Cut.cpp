#include<bits/stdc++.h>
using namespace std;
#define LL long long
#define pa pair<int,int>
const int N=100010;
const int inf=1<<29;
LL read()
{
	LL x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9')x=x*10ll+ch-'0',ch=getchar();
	return x*f;
}
int n,q,lc[N*44],rc[N*44],tot=N*4+5,c[N*44];
struct T
{
	int v[2][2];
	void print()
	{
		printf("00: %d 01: %d 10: %d 11: %d\n",v[0][0],v[0][1],v[1][0],v[1][1]);
	}
}s[N*44];
T operator + (T a,T b)
{
	T c;
	c.v[0][0]=max({a.v[0][0]+b.v[1][0],a.v[0][1]+b.v[0][0],a.v[0][0],b.v[0][0]});
	c.v[0][1]=max({a.v[0][0]+b.v[1][1],a.v[0][1]+b.v[0][1],a.v[0][1],b.v[0][1]});
	c.v[1][0]=max({a.v[1][0]+b.v[1][0],a.v[1][1]+b.v[0][0],a.v[1][0],b.v[1][0]});
	c.v[1][1]=max({a.v[1][0]+b.v[1][1],a.v[1][1]+b.v[0][1],a.v[1][1],b.v[1][1]});
	return c;
}
T rev(T a)
{
	swap(a.v[0][1],a.v[1][0]);
	return a;
}
/**/
struct I
{
	int l,r,rt,o;
	I(int _l,int _r,int _rt,int _o)
	{
		l=_l,r=_r,rt=_rt,o=_o;
	}
};
bool operator < (I a,I b)
{
	return a.r<b.r;
}
set<I>S;
void modify(int x,int l,int r,int p,T v)
{
	if(l==r)
	{
		s[x]=v;
		return;
	}
	int mid=l+r>>1;
	if(p<=mid)modify(x<<1,l,mid,p,v);
	else modify(x<<1|1,mid+1,r,p,v);
	s[x]=s[x<<1]+s[x<<1|1];
}
T query(int x,int l,int r,int ql,int qr)
{
	if(ql>qr)return s[0];
	if(l==ql&&r==qr)return s[x];
	int mid=l+r>>1;
	if(qr<=mid)return query(x<<1,l,mid,ql,qr);
	if(ql>mid)return query(x<<1|1,mid+1,r,ql,qr);
	return query(x<<1,l,mid,ql,mid)+query(x<<1|1,mid+1,r,mid+1,qr);
}
/**/
vector<int>sta;
void up(int x)
{
	c[x]=c[lc[x]]+c[rc[x]];
	s[x]=s[lc[x]]+s[rc[x]];
}
void del(int x)
{
	c[x]=lc[x]=rc[x]=0;s[x]=s[0];
	sta.emplace_back(x);
}
int newnode()
{
	if(sta.empty())return ++tot;
	int x=sta.back();sta.pop_back();
	return x;
}
void insert(int&x,int l,int r,int p)
{
	if(!x)x=newnode();
	if(l==r)
	{
		c[x]=1;
		s[x]=s[0];
		s[x].v[p&1][p&1]=1;
		return;
	}
	int mid=l+r>>1;
	if(p<=mid)insert(lc[x],l,mid,p);
	else insert(rc[x],mid+1,r,p);
	up(x);
}
void merge(int&u1,int u2)
{
	if(!u1){u1=u2;return;}
	if(!u2)return;
	merge(lc[u1],lc[u2]);
	merge(rc[u1],rc[u2]);
	up(u1);
	del(u2);
}
void split(int&u1,int&u2,int k) 
{
	if(!u1||c[u1]==k)return;
	if(!k){u2=u1;u1=0;return;}
	u2=newnode();
	int v=c[lc[u1]];
	if(k>v)split(rc[u1],rc[u2],k-v);
	else swap(rc[u1],rc[u2]);
	if(k<v)split(lc[u1],lc[u2],k);
	up(u1),up(u2);
}
void Split(int&x,int&y,int&z,int rt,int a,int b)
{
	y=rt;split(y,z,a+b);
	x=y;split(x,y,a);
}
void Erase(I u)
{
	modify(1,1,n,u.l,s[0]);
	S.erase(u);
}
void Insert(I u)
{
	if(u.l>u.r)return;
	modify(1,1,n,u.l,(!u.o?s[u.rt]:rev(s[u.rt])));
	S.insert(u);
}
void print_set()
{
	for(auto i=S.begin();i!=S.end();i++)
	{
		I t=*i;
		printf("%d %d %d %d %d ",t.l,t.r,t.rt,t.o,c[t.rt]);
		s[t.rt].print();
	}
	puts("");
}
int main()
{
	s[0].v[0][0]=s[0].v[0][1]=s[0].v[1][0]=s[0].v[1][1]=-inf;
	n=read(),q=read();
	for(int i=1;i<=n;i++)
	{
		int rt=0,x=read();
		insert(rt,1,n,x);
		Insert(I(i,i,rt,0));
	}
//	return 0;
	while(q--)
	{
		int o=read(),l=read(),r=read();
		if(o!=3)
		{
			I t=*S.lower_bound(I(0,l,0,0));
			if(t.l<=l&&r<=t.r)
			{
				int x=0,y=0,z=0,a,b,c;
				a=l-t.l;
				c=t.r-r;
				b=t.r-t.l+1-a-c;
				if(t.o)swap(a,c);
				Split(x,y,z,t.rt,a,b);
				Erase(t);
				if(!t.o)
				{
					Insert(I(t.l,t.l+a-1,x,0));
					Insert(I(t.l+a,t.l+a+b-1,y,o-1));
					Insert(I(t.l+a+b,t.l+a+b+c-1,z,0));
				}
				else
				{
					Insert(I(t.l,t.l+c-1,z,1));
					Insert(I(t.l+c,t.l+c+b-1,y,o-1));
					Insert(I(t.l+c+b,t.l+c+b+a-1,x,1));
				}
				//print_set();
			}
			else
			{
				int rt=0;
				while(t.l<=r)
				{
					Erase(t);
//					printf("l %d r %d\n",t.l,t.r);
//					print_set();
					if(t.l<l)
					{
						int x=0,y=0;
						if(!t.o)y=t.rt,split(y,x,l-t.l);
						else x=t.rt,split(x,y,t.r-l+1);
						merge(rt,x);
						t.r=l-1;t.rt=y;
						Insert(t);
					}
					else if(t.r>r)
					{
						int x=0,y=0;
						if(!t.o)x=t.rt,split(x,y,r-t.l+1);
						else y=t.rt,split(y,x,t.r-r);
						merge(rt,x);
						t.l=r+1;t.rt=y;
						Insert(t);
					}
					else merge(rt,t.rt);
					auto it=S.lower_bound(I(0,l,0,0));
					if(it==S.end())break;
					t=*it;
//					printf("# l %d r %d\n",t.l,t.r);
				}
//				print_set();
//				printf("l = %d r = %d\n",l,r);
				Insert(I(l,r,rt,o-1));
//				print_set();
			}
		}
		else
		{
//			print_set();
			I t=*S.lower_bound(I(0,l,0,0));
			if(t.l<=l&&r<=t.r)
			{
				int x=0,y=0,z=0,A,B,C;
				A=l-t.l;
				C=t.r-r;
				B=t.r-t.l+1-A-C;
				if(t.o)swap(A,C);
				Split(x,y,z,t.rt,A,B);
				printf("%d\n",max({s[y].v[0][0],s[y].v[0][1],s[y].v[1][0],s[y].v[1][1]}));
				merge(y,z);
				merge(x,y);
				I nt=t;nt.rt=x;
				Erase(t);Insert(nt);
			}
			else
			{
				I L=t,R=*S.lower_bound(I(0,r,0,0));
				T ans=s[0];
				int x,y;
				
				Erase(L);
				x=y=0;
				if(!L.o)y=L.rt,split(y,x,l-L.l),ans=ans+s[x];
				else x=L.rt,split(x,y,L.r-l+1),ans=ans+rev(s[x]);
				L.rt=x;merge(L.rt,y);
				Insert(L);
//				ans.print();
 
				ans=ans+query(1,1,n,L.r+1,R.l-1);
//				ans.print();
				
				Erase(R);
				x=y=0;
				if(!R.o)x=R.rt,split(x,y,r-R.l+1),ans=ans+s[x];
				else y=R.rt,split(y,x,R.r-r),ans=ans+rev(s[x]);
				R.rt=x;merge(R.rt,y);
				Insert(R);
//				ans.print();
				
				printf("%d\n",max({ans.v[0][0],ans.v[0][1],ans.v[1][0],ans.v[1][1]}));
			}
		}
//		print_set();
	}
	return 0;
}
