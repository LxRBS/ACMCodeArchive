#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>
using namespace std;

double const EPS = 1E-9;

#define isZero(x)  ( -EPS < (x) && (x) < EPS )

struct point_t{
	int x;
	int y;
	point_t(int a=0,int b=0):x(a),y(b){}
}Point[101];

struct point64f_t{
	double x;
	double y;
};

bool operator == (point64f_t const&l,point64f_t const&r){
	return isZero(l.x-r.x) && isZero(l.y-r.y);
}

//半平面数据结构
struct hp_t{
	double a;
	double b;
	double c;    //直线ax+by+c
	double angle;//法向量极角，当ax+by+c>=0时，法向量恰好为(a,b)
	hp_t(double aa=0.0,double bb=0.0,double cc=0.0,double theta=0.0):
	a(aa),b(bb),c(cc),angle(theta){}
}Hp[105];

//返回向量所在的区域值，肯定不是0向量
inline int calcLoc(double x,double y){
	if ( isZero(x) ) return y > 0 ? 5 : 1; //5表示y正方向，1表示y负方向
	if ( isZero(y) ) return x > 0 ? 2 : 7; //2:x正方向；7:x负方向

	if ( x > 0 ) return y > 0 ? 4 : 2; //4：第一象限；2：第四象限
	return y > 0 ? 6 : 0;    //6:二象限; 0:第三象限
}
//根据半平面法向量的极角进行排序，实际上利用叉积排序
bool cmp(hp_t const&left,hp_t const&right){
    int leftloc = calcLoc(left.a,left.b);
	int rightloc = calcLoc(right.a,right.b);
	//如果法向量处在不同区域，可直接返回结果
	if ( leftloc != rightloc ) return leftloc < rightloc;

	//计算叉积
	double chaji = left.a * right.b - left.b * right.a;
	
	//保证比较的半平面不平行
	if ( !isZero(chaji) )	return chaji > 0;

	//叉积为0，说明半平面平行，越靠近法向量的越小
	if ( left.a > EPS ){
        //即a为正的情况下
	    //若hp1比hp2更靠近法向量，则必有a1x+b1y+c1=0而a2x+b2y+c2>0
		return left.c * right.a < left.a * right.c;
	}

    if ( left.a < -EPS ) return left.a * right.c < left.c * right.a;

	//剩下则为a取值为0的情况，此时考虑b即可
	if ( left.b > EPS ) return left.c * right.b < left.b * right.c;

	//若b为负，a、b不可能同时为0
	return left.b * right.c < left.c * right.b;
}

//由两点生成半平面，已知left到right为顺时针，第三个参数为输出参数
void genHP(point_t const&left,point_t const&right,hp_t&hp){
    hp.a = (double)(right.y - left.y);
	hp.b = (double)(left.x - right.x);
	hp.c = (double)(right.x * left.y - right.y * left.x);

	//顺时针方向，则方向边与法向量叉积为负，若为正的话将a、b、c异号
//	if ( hp.a * hp.b > 0 ) {
//        hp.a = -hp.a;
//		hp.b = -hp.b;
//		hp.c = -hp.c;
//	}
    //极角是用来排序的，但是考虑到误差，尽量使用叉积进行排序  
//	hp.angle = atan2(hp.b,hp.a);
}

//判断两半平面是否平行
inline bool isParallel(hp_t const&left,hp_t const&right){
	return calcLoc(left.a,left.b) == calcLoc(right.a,right.b) 
		&& isZero( left.a * right.b - left.b * right.a );
}

//半平面相交求交点，p是输出参数，保证半平面不平行
void inter(hp_t const&left,hp_t const&right,point64f_t&p){
    double xishu = left.a * right.b - right.a * left.b;
	p.x = ( left.b * right.c - right.b * left.c ) / xishu;
	p.y = ( left.c * right.a - left.a * right.c ) / xishu;
}

//判断点是否在半平面上
inline bool isIn(point64f_t const&p,hp_t const&hp){
	double v = hp.a * p.x + hp.b * p.y + hp.c;
	return isZero(v) || v > 0;
}

int main(){
	int n;
	int kase = 0;
	while( scanf("%d",&n) && n ){
		//输入点集，已知为逆时针
        for(int i=0;i<n;++i)scanf("%d%d",&Point[i].x,&Point[i].y);

        //根据点集生成半平面
        Point[n] = Point[0];
		for(int i=0;i<n;++i) 
			genHP(Point[i],Point[i+1],Hp[i]);
		
		//生成最大取值范围的半平面确保将定义域包围，此处不需要
// 		genHP(point_t(INT_MIN,INT_MIN),point_t(INT_MAX,INT_MIN),Hp[n]);
// 		genHP(point_t(INT_MAX,INT_MIN),point_t(INT_MAX,INT_MAX),Hp[n+1]);
// 		genHP(point_t(INT_MAX,INT_MAX),point_t(INT_MIN,INT_MAX),Hp[n+2]);
// 		genHP(point_t(INT_MIN,INT_MAX),point_t(INT_MIN,INT_MIN),Hp[n+3]);

		//排序
		sort(Hp,Hp+n,cmp);

		//极角相同的半平面，只保留一个，此处保留更靠近法向量方向的，也就是保留最小的
		Hp[n] = Hp[0];//此题中，第一个与最后一个绝对不会平行，这样省去了检查i越界的问题
		int k = 0;
		for(int i=1;i<n;){
            while( isParallel(Hp[k],Hp[i]) ) ++i;
			if ( i == n ) break;
			Hp[k+1] = Hp[i];
			k = k + 1;
			++i;
		}
		
		//k是参与后续处理的半平面个数
		k = k + 1;

		//执行循环
		int bot = 0;
		int top = 1;
		for(int i=2;i<k;++i){
			//最前端两个半平面相交
			while( bot < top ){
				//求交点
				point64f_t p;
				inter(Hp[top-1],Hp[top],p);
				//在半平面外，出队列
                if ( !isIn(p,Hp[i]) ) --top;
				else                  break;
			}
			//最后段两个半平面相交
			while( bot < top ){
				point64f_t p;
				inter(Hp[bot],Hp[bot+1],p);
				if ( isIn(p,Hp[i]) ) break;
				else                 ++bot;
			}
			//赋值
			Hp[++top] = Hp[i];
		}

		//如果最后只留下2个甚至更少的半平面，肯定不对
		if ( top - bot <= 1 ){
			++kase;
			printf("Floor #%d\n",kase);
            printf("Surveillance is impossible.\n");
			printf("\n");
			continue;
		}

		//最前端两个半平面相交
		while( bot < top ){
			//求交点
			point64f_t p;
			inter(Hp[top-1],Hp[top],p);
			//在最后端的半平面外，则出队列
			if ( !isIn(p,Hp[bot]) ) --top;
			else                    break;
		}	
        //最后端两个半平面相交
		while( bot < top ){
			point64f_t p;
			inter(Hp[bot],Hp[bot+1],p);
			if ( isIn(p,Hp[top]) ) break;
			else                   ++bot;
		}

		//剩余的半平面求交点
        vector<point64f_t> vec;
		Hp[top+1] = Hp[bot];
		for(int i=bot;i<=top;++i){
			point64f_t p;
			inter(Hp[i],Hp[i+1],p);
			vec.push_back(p);
		}

        //去除重合的点，此处不需要，因为只要有一个点就可以满足题意
//		vector<point64f_t>::iterator it;
//		it = unique(vec.begin(),vec.end());

        //输出
		++kase;
		printf("Floor #%d\n",kase);
		if ( vec.empty() ) printf("Surveillance is impossible.\n");
		else               printf("Surveillance is possible.\n");
        printf("\n");
	}
	return 0;
}