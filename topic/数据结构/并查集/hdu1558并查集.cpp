#include <cstdio>
#include <algorithm>
using namespace std;

#define SIZE 1002

int Father[SIZE],Deg[SIZE];//合并度数前一定要检查
void init(int n){for(int i=1;i<=n;Deg[i]=1,Father[i]=i++);}
int find(int x){return x==Father[x]?x:Father[x]=find(Father[x]);}
void unite(int x,int y){x=find(x),y=find(y),Father[y]=x,x!=y?Deg[x]+=Deg[y]:0;}

#define EPS 1E-6
#define is0(x) ( -EPS < (x) && (x) < EPS )

struct point64_t{
	double x,y;
};

double cross(point64_t const&O,point64_t const&A,point64_t const&B){
	double xoa = A.x - O.x;
	double yoa = A.y - O.y;
	double xob = B.x - O.x;
	double yob = B.y - O.y;
	return xoa * yob - xob * yoa;
}

struct seg_t{
	point64_t s,e;
}Seg[SIZE];

bool isOn(seg_t const&a,seg_t const&b){
	return min(a.s.x,a.e.x) <= max(b.s.x,b.e.x)
		&& min(b.s.x,b.e.x) <= max(a.s.x,a.e.x)
		&& min(a.s.y,a.e.y) <= max(b.s.y,b.e.y)
		&& min(b.s.y,b.e.y) <= max(a.s.y,a.e.y)
		&& cross(b.s,a.e,b.e) * cross(b.s,b.e,a.s) >= 0.0
		&& cross(a.e,b.s,a.s) * cross(a.e,a.s,b.e) >= 0.0;
}

int main(){
	int nofkase;
	scanf("%d",&nofkase);
	while(nofkase--){
		int n;
		scanf("%d",&n);
		init(n);
		int k = 0;
		for(int i=0;i<n;++i){
            char cmd;
			scanf("%*c%c",&cmd);
			if ( 'P' == cmd ){
				++k;
				scanf("%lf%lf%lf%lf",&Seg[k].s.x,&Seg[k].s.y,&Seg[k].e.x,&Seg[k].e.y);
				//判断第k条线段与前面的线段是否相交
				for(int j=1;j<k;++j){
					if ( isOn(Seg[j],Seg[k]) )
					    unite(j,k);
				}
			}else{
				int kk;
				scanf("%d",&kk);
				printf("%d\n",Deg[find(kk)]);
			}
		}
		if ( nofkase > 0 ) printf("\n");
	}
	return 0;
}