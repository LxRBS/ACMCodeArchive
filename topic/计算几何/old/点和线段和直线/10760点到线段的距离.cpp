#include <cstdio>
#include <cmath>
#define SIZE 101

struct point_t{
	int x;
	int y;
}In[SIZE],Out[SIZE];

int cross(point_t const&o,point_t const&a,point_t const&b){
	int xoa = a.x - o.x;
	int xob = b.x - o.x;
	int yoa = a.y - o.y;
	int yob = b.y - o.y;
	return xoa * yob - xob * yoa;
}
int dot(point_t const&o,point_t const&a,point_t const&b){
	int xoa = a.x - o.x;
	int xob = b.x - o.x;
	int yoa = a.y - o.y;
	int yob = b.y - o.y;
	return xoa * xob + yob * yoa;
}
//计算点A到点B的距离的平方
int dist2(point_t const&A,point_t const&B){
	int x = A.x - B.x;
	int y = A.y - B.y;
	return x * x + y * y;
}
//计算点P到线段AB的距离的平方
double dist2(point_t const&P,point_t const&A,point_t const&B){
    if ( dot(A,P,B) <= 0 ) return (double)dist2(P,A);
	if ( dot(B,P,A) <= 0 ) return (double)dist2(P,B);

	double s = (double)cross(A,P,B);
	s *= s;
	return s / (double)dist2(A,B);
}

int main(){
	int nofkase;
	scanf("%d",&nofkase);
	while(nofkase--){
		int ni;
		scanf("%d",&ni);
		for(int i=0;i<ni;++i)scanf("%d%d",&In[i].x,&In[i].y);

		int no;
		scanf("%d",&no);
		for(int i=0;i<no;++i)scanf("%d%d",&Out[i].x,&Out[i].y);
		Out[no] = Out[0];
 
        //对每个ni的点去找到no线段的最近距离
		double ans = 1E12;
		for(int i=0;i<ni;++i)for(int j=0;j<no;++j){
			double t = dist2(In[i],Out[j],Out[j+1]);
			if ( ans > t ) ans = t;
		}
		printf("%lf\n",sqrt(ans)/2.0);
	}
}