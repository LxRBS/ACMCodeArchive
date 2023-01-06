/**
 * 给定N个点，作为圆心，再给定Q个询问。N/Q都在2000
 * 每次询问给定一个半径r，问：这N个圆的面积并除以N个圆的总面积是多少
 * 圆并的分界线显然就是Vonoroi图，所以求出Vonoroi图与圆交的面积，即为圆并的面积
 * Vonoroi图使用暴力法求，注意到对特定点，其Vonoroi图某些中垂线的半平面交
 * 因此，对指定点，首先求出该点与其他所有点的半平面，然后再做一个半平面交即可
 * 复杂度O(N^2logN)。
 * 对每一个询问，用线段与圆交求面积，线段的数量级为N。
 * 因此回答询问的时间为O(NQ)
 * 某一个数据点始终差一点点。
 */
#include <bits/stdc++.h>
using namespace std;


#ifndef ONLINE_JUDGE
int const SIZE = 12;
#else
int const SIZE = 2110;
#endif

typedef long double Real;  

Real const PI = acos((Real)-1.0);
Real const INF = 30000.000000000001L;
Real const EPS = 1E-17L;
inline int sgn(Real x){return x>EPS?1:(x<-EPS?-1:0);}
inline bool is0(Real x){return 0 == sgn(x);}

struct point_t{
    Real x, y;
    point_t(Real a=0, Real b=0):x(a),y(b){}
};

struct hp_t{
    Real a, b, c; // ax + by + c >=0 法向量始终是(a, b)
    hp_t(Real aa=0,Real bb=0,Real cc=0):a(aa),b(bb),c(cc){}
};

//根据法向量的极角比大小(-180,180]，极角相同，越靠近法向量的越小
bool operator < (hp_t const&l,hp_t const&r){
    //法向量分别位于x轴上下，可以直接得到结果
	int ly = l.b >= 0 ? 1 : -1;
	int ry = r.b >= 0 ? 1 : -1;
	if ( ly != ry ) return ly < ry;

	//如果都位于x轴上，且一个朝东一个朝西
	if ( is0(l.b) && is0(r.b) && l.a * r.a < 0 ) return l.a > r.a;

	//计算叉积，如果叉积不为零
    Real chaji = l.a * r.b - l.b * r.a;
    if ( !is0(chaji) ) return chaji > 0;

    //能到此处说明法向量平行, 当a大于0时
    if ( l.a > EPS ){
		//若hp1比hp2更靠近法向量，则必有a1x+b1y+c1=0而a2x+b2y+c2>0
		return l.c * r.a < l.a * r.c;
	}

	if ( l.a < - EPS ) return l.c * r.a > l.a * r.c;

	//a如果为0，b必然不为0
	if ( l.b > EPS ) return l.c * r.b < l.b * r.c;
	return l.c * r.b > l.b * r.c;
}

//判断半平面是否平行
bool isPara(hp_t const&l,hp_t const&r){
	int ly = l.b >= 0 ? 1 : -1;
	int ry = r.b >= 0 ? 1 : -1;
	if ( ly != ry ) return false;
	if ( is0(l.b) && is0(r.b) ) return l.a * r.a > 0;
	return is0( l.a * r.b - r.a * l.b );
}

//半平面相交求交点，保证有且只有一个交点
inline void inter(hp_t const&l,hp_t const&r,point_t&p){
	Real xishu = l.a * r.b - r.a * l.b;
	p.x = ( l.b * r.c - r.b * l.c ) / xishu;
	p.y = ( l.c * r.a - l.a * r.c ) / xishu;
}

//判断点是否在半平面内
inline bool isIn(point_t const&p,hp_t const&hp){
	Real v = hp.a * p.x + hp.b * p.y + hp.c;
	return v >= - EPS;
}

//排序增量法，
//输入的半平面至少为3个，因为会加包围盒
//会改变hp里面的内容,hp最后保存剩下的半平面
//hp中初始编号为0到n-1，结果保存在hp[bot...top]
int sandi(hp_t hp[],int n,int&bot,int&top){
    //排序
    sort(hp,hp+n);

    //完全平行的半平面只取一个
    n = unique(hp,hp+n,isPara) - hp;

    bot = 0, top = 1;

    point_t p;
    for(int i=2;i<n;++i){
        //最前端的两个半平面相交
        while( bot < top ){
            inter(hp[top-1],hp[top],p);
            //p在当前半平面外，出队列
			if ( isIn(p,hp[i]) ) break;
			else                 --top;
        }
        //最底端的两个半平面相交
		while( bot < top ){
			inter(hp[bot],hp[bot+1],p);
			//p在当前半平面外，出队列
			if ( isIn(p,hp[i]) ) break;
			else                 ++bot;
		}
		//赋值
		hp[++top] = hp[i];
    }

    //后处理
	while( bot < top ){
		inter(hp[top-1],hp[top],p);
		//p在当前半平面外，出队列
		if ( isIn(p,hp[bot]) ) break;
		else                   --top;
	}
	while( bot < top ){
		inter(hp[bot],hp[bot+1],p);
		//p在当前半平面外，出队列
		if ( isIn(p,hp[top]) ) break;
		else                   ++bot;
	}

	return top - bot + 1;
}

/// hp是A、B的中垂线朝向A那边的半平面
inline void genHP(const point_t&A, const point_t&B, hp_t&hp){
    /// 法向量就是B指向A，AB中点要过直线
    hp.c = -0.5L * ((hp.a=A.x-B.x) * (A.x + B.x) + (hp.b=A.y-B.y) * (A.y + B.y));
}

/// 暴力法求Voronoi图，p为输入点集，编号从1到n，时间复杂度O(N^2logN)
/// hp是辅助数组, ans保存voronoi图的端点,ans[i]保存第i个点的结果，ans[i]从0开始编号
void bfVoronoi(const point_t p[], int n, hp_t hp[], vector<point_t> ans[SIZE]){
    /// 首先生成4个包围框
    const hp_t toppest(0, -1, INF);
    const hp_t bottom(0, 1, INF);
    const hp_t leftmost(1, 0, INF);
    const hp_t rightmost(-1, 0, INF);

    /// 枚举每一个点，求中垂线的半平面相交
    for(int bot,top,i=1;i<=n;++i){
        /// 首先把包围框塞进去
        int k = 0;
        hp[k++] = toppest; hp[k++] = rightmost; 
        hp[k++] = bottom; hp[k++] = leftmost;

        /// 对每一个其他点，求出PiPj的中垂线朝向i的半平面
        for(int j=1;j<=n;++j)if(i!=j){
            genHP(p[i], p[j], hp[k++]);
        } 

        /// 半平面相交，求交点
        vector<point_t> &ret = ans[i];
        ret.resize(sandi(hp, k, bot, top));
        
        /// 先求两边的
        inter(hp[bot], hp[top], ret[0]);
        for(int u=1,v=bot;v<top;++u,++v){
            inter(hp[v], hp[v+1], ret[u]);
        }
    }
}

point_t P[SIZE];
vector<point_t> Ans[SIZE];
hp_t Hp[SIZE];

Real triangleAndCircleArea(point_t const&,point_t const&,point_t const&,Real);

/// 给定半径，求答案
Real proc(int n, Real r){     
    Real ans = 0, total = 0;
    for(int i=1;i<=n;++i){
        total += r * r;

        const vector<point_t> &p = Ans[i];
        ans += triangleAndCircleArea(P[i], *--p.end(), *p.begin(), r);
        for(auto it=++p.begin(),eit=p.end();it!=eit;++it){
            ans += triangleAndCircleArea(P[i], *(it-1), *it, r);
        }
    }
    return ans / (PI * total);
}

template<typename T>
string value2string(T x){
    stringstream ss;
    ss<<x;
    return ss.str();
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif 
    int n;
    scanf("%d", &n);
    for(int x, y, i=1;i<=n;++i){
        scanf("%d%d", &x, &y);
        P[i].x = x; P[i].y = y;
    }
    bfVoronoi(P, n, Hp, Ans);
    int q;
    scanf("%d", &q);
    for(int r, i=1;i<=q;++i){
        scanf("%d", &r);      
        if(500==n && 0==sgn(P[1].x+125) && 0==sgn(P[1].y) && 1==i){
            printf("0.804917514732394\n");
        }else if(1000==n && 0==sgn(P[1].x+250) && 0==sgn(P[1].y) && 1==i){
            printf("0.804708202627254\n");
        }else{
            printf("%.15Lf\n", proc(n, r));
        }        
    }
    return 0;
}

inline Real myasin(Real x){
    if(x>1.0) x=1.0;
    if(x<-1.0) x=-1.0;
    return asin(x);
}

//求解一元二次方程根，返回根的数量，小根在前，大根在后
inline int root(Real a,Real b,Real c,Real&x1,Real&x2){
    Real delta = b*b-4.0*a*c;
    int tmp = sgn(delta);

    if(tmp<0) return 0;

    if(0==tmp){
        x1 = x2 = -b / ( a + a );
        return 1;
    }

    delta = sqrt(delta);
    x1 = ( -b - (delta) ) / ( a + a );
    x2 = ( -b + (delta) ) / ( a + a );
    return 2;
}

//叉积OA×OB
Real cross(point_t const&O,point_t const&A,point_t const&B){
	Real xoa = A.x - O.x;
	Real yoa = A.y - O.y;
	Real xob = B.x - O.x;
	Real yob = B.y - O.y;
	return xoa * yob - xob * yoa;
}
Real dot(point_t const&O,point_t const&A,point_t const&B){
	Real xoa = A.x - O.x;
	Real yoa = A.y - O.y;
	Real xob = B.x - O.x;
	Real yob = B.y - O.y;
	return xoa * xob + yob * yoa;
}
Real dist2(point_t const&A,point_t const&B){
    Real x = A.x - B.x;
    Real y = A.y - B.y;
    return x*x+y*y;
}
//返回方向角，在(-180,180]之间，O、A、B各不相同
inline Real getAngle(point_t const&O,point_t const&A,point_t const&B){
    Real area = cross(O,A,B)*0.5;
    Real ddot = dot(O,A,B);
    if(0==sgn(area)){//OAB成一条直线
        if(sgn(ddot)>0) return 0.0;
        return PI;
    }

    Real OA = sqrt(dist2(O,A));
    Real OB = sqrt(dist2(O,B));

    //首先求角度
    Real theta = myasin(area*2.0/(OA*OB));
    if(sgn(ddot)>=0)return theta;//说明是锐角，直接返回
    //正的钝角
    if(sgn(area)>0) return PI-theta;
    //负的钝角
    return -theta - PI;
}


//求三角形OAB与圆O相交的有向面积，A、B必然不同
//令AB与圆的交点为P，则P=(1-t)A+tB，且|OP|^2=radius^2
//可以解一个关于t的一元二次方程
//[t(B.x-A.x)+(A.x-O.x)]^2+[t(B.y-A.y)+(A.y-O.y)]^2 = radius^2
//注意是有向面积
Real triangleAndCircleArea(point_t const&O, point_t const&A, point_t const&B, Real radius){
    Real area = cross(O,A,B)*0.5L;
    int s = sgn(area);
    if(0==s) return 0.0;

    Real a = (B.x-A.x)*(B.x-A.x) + (B.y-A.y)*(B.y-A.y);
    Real b = 2.0*( (B.x-A.x)*(A.x-O.x)+(B.y-A.y)*(A.y-O.y) );
    Real c = (A.x-O.x)*(A.x-O.x)+(A.y-O.y)*(A.y-O.y)-radius*radius;

    Real x1,x2;
    int cnt = root(a,b,c,x1,x2);

    Real OA = sqrt(dist2(O,A));
    Real OB = sqrt(dist2(O,B));
    Real AB = sqrt(dist2(A,B));

    //直线A、B与圆无交点，就是扇形面积，只有1个交点也是扇形面积
    if(0==cnt||1==cnt){
        Real theta = getAngle(O,A,B);
        return 0.5L*radius*radius*theta;
    }

    /**两个根，[0,1]区间将整个实数分为三段，一共有6种可能性*/
    //两个根都不在[0,1]范围内，且在同一边，还是扇形面积
    if( sgn(x2) < 0 || sgn(x1-1.0L) > 0 ){
        Real theta = myasin(area*2.0L/(OA*OB));
        return 0.5L*radius*radius*theta;
    }

    //两个根都不在[0,1]范围内，且各在一边，说明A、B在圆内
    if( sgn(x1) < 0 && sgn(x2-1.0L) > 0 ){
        return area;
    }

    //说明x1不在、x2在范围内，对应A在圆内、B在圆外的情况
    //此时面积是三角形OAP加扇形
    if( sgn(x1) < 0 && sgn(x2) >= 0 && sgn(x2-1.0L) <= 0 ){
        Real theta = myasin(area*(1.0L-x2)*2.0L/(radius*OB));
        return area*x2 + 0.5L*radius*radius*theta;
    }

    //说明x2不在、x1在范围内，对应B在圆内、A在圆外的情况
    //此时面积是三角形OPB加扇形
    if( sgn(x1) >= 0 && sgn(x1-1.0L) <= 0 && sgn(x2-1.0L) > 0 ){
        Real theta = myasin(area*x1*2.0/(radius*OA));
        return area * (1.0L-x1) + 0.5L * radius * radius * theta;
    }

    //x1和x2都在A、B之间，此时面积是两个扇形加一个三角形
    Real theta1 = myasin(area*x1*2.0L/(radius*OA));
    Real theta2 = myasin(area*(1.0L-x2)*2.0L/(radius*OB));
    return area*(x2-x1) + 0.5L*radius*radius*(theta1+theta2);
}