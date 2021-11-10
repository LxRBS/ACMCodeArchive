#include <bits/stdc++.h>
#include "testlib.h"
using namespace std;

typedef long long ll;
const int MAXN=200005;

struct Point2D
{
    ll x,y;
    Point2D() {}
    Point2D(ll _x,ll _y):x(_x),y(_y) {}
    Point2D operator - (const Point2D &t)const
    {
        return Point2D(x-t.x,y-t.y);
    }
    ll operator * (const Point2D &t)const
    {
        return x*t.y-y*t.x;
    }
} p[MAXN];

namespace Geometry
{
int n,m;
Point2D c[MAXN];
inline bool cmp(const Point2D &a,const Point2D &b)
{
    return a.x==b.x?a.y<b.y:a.x<b.x;
}
inline ll cross(const Point2D &a,const Point2D &b)
{
    return 1LL*a.x*b.y-1LL*a.y*b.x;
}
int convexhull(Point2D *p,int n,Point2D *q)
{
    int i,k,m;
    for(i=m=0; i<n; q[m++]=p[i++])while(m>1&&cross(q[m-1]-q[m-2],p[i]-q[m-2])<=0)m--;
    k=m;
    for(i=n-2; i>=0; q[m++]=p[i--])while(m>k&&cross(q[m-1]-q[m-2],p[i]-q[m-2])<=0)m--;
    return --m;
}
inline int askl(int l,int r,const Point2D &p)
{
    int t=l++,mid;
    while(l<=r)
    {
        mid=(l+r)>>1;
        if(cross(c[mid]-p,c[(mid-1+n)%n]-c[mid])<=0)l=(t=mid)+1;
        else r=mid-1;
    }
    return t;
}
inline int askr(int l,int r,const Point2D &p)
{
    int t=r--,mid;
    while(l<=r)
    {
        mid=(l+r)>>1;
        if(cross(c[mid]-p,c[(mid+1)%n]-c[mid])>=0)r=(t=mid)-1;
        else l=mid+1;
    }
    return t;
}
Point2D init(int ca, Point2D p[])
{
    sort(p,p+ca,cmp);
    n=convexhull(p,ca,c);
    Point2D o=c[0];
    for(int i=0; i<n; i++)
        c[i]=c[i]-o;
    c[n]=c[0];
    for(int i=(m=0); i<n; i++)
        if(c[i].x>=c[m].x)m=i;
    return o;
}
pair<int,int> get_tangent(const Point2D& p)
{
    int o=0;
    if(p.x>0)
    {
        int l=1,r=n-1,mid;
        while(l<=r)if(cross(c[mid=(l+r)>>1],p)>=0)l=(o=mid)+1;
            else r=mid-1;
    }
    else if(p.y>0)o=n-1;
    int l,r;
    if(p.x>0)l=askl(0,o,p),r=askr(o,n,p);
    else l=askl(m,n,p),r=askr(0,m,p);
    while(!cross(p-c[l],p-c[(l+1+n)%n]))l=(l+1+n)%n;
    while(!cross(p-c[r],p-c[(r-1+n)%n]))r=(r-1+n)%n;
    //ÏàÇÐ²»Ëã
    if(l==r)while(1);
    //if(l>r)r+=n;
    //printf("(%d,%d):",p.x,p.y);
    //for(int i=l;i<=r;i++)printf("(%d,%d) ",c[i%n].x,c[i%n].y);puts("");
    return make_pair(l%n,r%n);
}
}

pair<int,int> seg[MAXN];
int cover[MAXN],usd[MAXN];

bool no_sol(int n,int m)
{
    for(int i=0; i<n; i++)
        cover[i]=0;
    for(int i=0; i<m; i++)
    {
        cover[seg[i].first]++,cover[seg[i].second]--;
        if (seg[i].first>seg[i].second)cover[0]++;
    }
    for(int i=1; i<n; i++)
        cover[i]+=cover[i-1];
    for(int i=0; i<n; i++)
        if(!cover[i])return 1;
    return 0;
}

int check(int n,int m,InStream &res)
{
    int k=res.readInt(-1,m);
    if(no_sol(n,m))
    {
        if(k!=-1)res.quitf(_wa,"no solution but output yes.");
        return -1;
    }
    if(k==-1)res.quitf(_wa,"has solution but output no.");
    res.readEoln();
    for(int i=0; i<n; i++)
        cover[i]=0;
    for(int i=0; i<m; i++)
        usd[i]=0;
    for(int _=0; _<k; _++)
    {
        if(_)res.readSpace();
        int i=res.readInt(1,m)-1;
        if(usd[i])res.quitf(_wa,"the illuminant with index %d has been selected before.",i+1);
        usd[i]=1;
        cover[seg[i].first]++,cover[seg[i].second]--;
        if (seg[i].first>seg[i].second)cover[0]++;
    }
    for(int i=1; i<n; i++)
        cover[i]+=cover[i-1];
    for(int i=0; i<n; i++)
        if(!cover[i])res.quitf(_wa,"the chosen illuminants cannot light up all exterior boundaries of the polygon.");
    return k;
}

int main(int argc,char* argv[])
{
    setName("check whether the given scheme feasible");
    registerTestlibCmd(argc,argv);

    int n=inf.readInt();
    int m=inf.readInt();
    for(int i=0; i<n; i++)
    {
        p[i].x=inf.readInt();
        p[i].y=inf.readInt();
    }
    Point2D o=Geometry::init(n, p);
    for(int i=0; i<m; i++)
    {
        int x=inf.readInt();
        int y=inf.readInt();
        seg[i]=Geometry::get_tangent(Point2D(x,y)-o);
    }
    int j=check(n,m,ans);
    int p=check(n,m,ouf);
    if(j<p)quitf(_wa,"the participant's output %d is larger than the jury's %d.",p,j);
    if(j>p)quitf(_fail,"the jury's output %d is larger than the participant's %d.",j,p);
    quitf(_ok, "ok, answer %d", j);
}
