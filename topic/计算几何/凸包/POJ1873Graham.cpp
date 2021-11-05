/*
    n个树，砍掉其中一些，用来做篱笆
    把剩下的树围起来
    求砍掉哪些可以达到目标并且费用最小
*/

#include <stdio.h>
#include <math.h>
#include <algorithm>
using namespace std;

//点的数据结构
struct point_t{
	int x,y;
	point_t(int a=0,int b=0):x(a),y(b){}
};

//叉积OA×OB
int cross(point_t const&O,point_t const&A,point_t const&B){
	int xoa = A.x - O.x;
	int yoa = A.y - O.y;
	int xob = B.x - O.x;
	int yob = B.y - O.y;
	return xoa * yob - xob * yoa;
}

inline double dist(point_t const&lhs,point_t const&rhs){
    double x = lhs.x - rhs.x;
    double y = lhs.y - rhs.y;
    return sqrt(x*x+y*y);
}

//判断点l是否比点r更下更左
bool isBottomLeft(point_t const&l,point_t const&r){
	if ( l.y != r.y ) return l.y < r.y;
	return l.x < r.x;
}

//为Graham排序做准备
point_t* pOrigin;
bool is4Graham(point_t const&l,point_t const&r){
	int t = cross(*pOrigin,l,r);
	if ( t ) return t > 0;
	return (l.x-pOrigin->x)*(l.x-pOrigin->x)<(r.x-pOrigin->x)*(r.x-pOrigin->x);
}

//Graham求严格凸包
int Graham(point_t p[],int n){
	if ( 1 == n ) return 1;

	//求最下最左点
	point_t* t = min_element(p,p+n,isBottomLeft);

	//与0点交换位置
	point_t ptmp(*t);
	*t = p[0];
	p[0] = ptmp;

	//相对于0点排序
	pOrigin = p;
	sort(p+1,p+n,is4Graham);

	//建栈循环
	int top = 2;
	for(int i=2;i<n;++i){
		while( top>1 && cross(p[top-2],p[top-1],p[i])<=0 )
			--top;
		p[top++] = p[i];
	}

	if( top>=3 && 0==cross(p[0],p[top-1],p[top-2]) )
		--top;

	return top;
}

int N;
point_t P[20];
int V[20],L[20];
bool read(){
    scanf("%d",&N);
    if ( 0 == N ) return false;
    for(int i=0;i<N;++i)scanf("%d%d%d%d",&P[i].x,&P[i].y,V+i,L+i);
    return true;
}

point_t Q[20];
int main(){
    //freopen("1.txt","r",stdin);

    for(int kase=1;read();++kase){
        int ansValue = 10000000;
        int ansCnt = 20;
        int ansStatus;
        double ansLen;

        int ii,n,value,len,cnt;
        for(int i=1;i<(1<<N);++i){

            for(value=len=n=ii=0;ii<N;++ii){
                if(i&(1<<ii)) value += V[ii], len += L[ii];//砍树
                else Q[n++] = P[ii];//留下的树
            }

            cnt = N - n;
            if ( n ) n = Graham(Q,n);
            Q[n] = Q[0];

            //求周长
            double cir = 0;
            if ( n >= 2 ) for(ii=0;ii<n;++ii)cir += dist(Q[ii],Q[ii+1]);

            //判断
            if ( cir < len ){
                if ( value < ansValue || (value == ansValue && cnt < ansCnt) ){
                    ansValue = value;
                    ansCnt = cnt;
                    ansLen = len - cir;
                    ansStatus = i;
                }
            }
        }

        if (kase!=1) printf("\n");
        printf("Forest %d\nCut these trees:",kase);
        for(int i=0;i<N;++i)if(ansStatus&(1<<i))printf(" %d",i+1);
        printf("\nExtra wood: %.2f\n",ansLen);
    }
    return 0;
}