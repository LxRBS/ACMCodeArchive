/**
   一个凸多边形，用半径为r的圆覆盖，每个单位要B元，
   直接覆盖每个单位要A元
   问最少要多少钱可以覆盖整个图形
   如果B>=A，直接计算多边形面积乘以A即可
   如果B<A，则计算出边角的面积，分别相乘相加即可
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long int llt;
typedef double ldb;

ldb const PI = acos(-1.0);
ldb const EPS = 1E-9;
inline bool is0(ldb x){return -EPS<=x&&x<=EPS;}
inline llt ABS(llt n){return n>=0?n:-n;}
struct point_t{
    llt x,y;
    point_t(llt xx=0,llt yy=0):x(xx),y(yy){}
};

llt cross(point_t const&O,point_t const&A,point_t const&B){
    llt xoa = A.x - O.x;
    llt yoa = A.y - O.y;
    llt xob = B.x - O.x;
    llt yob = B.y - O.y;
    return xoa * yob - xob * yoa;
}

struct point64f_t{
    ldb x,y;
    point64f_t(ldb xx=0.0,ldb yy=0.0):x(xx),y(yy){}
};

struct hp_t{
    ldb a,b,c;//ax+by+c>=0,法向量始终是(a,b)
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
    double chaji = l.a * r.b - l.b * r.a;
    if ( !is0(chaji) ) return chaji > 0;

    //能到此处说明法向量平行

    //当a大于0时
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

//从l到r，保证是逆时针方向，a、b是唯一确定的
inline void genHP(point_t const&l,point_t const&r,hp_t&hp){
	hp.a = (ldb)( l.y - r.y );
	hp.b = (ldb)( r.x - l.x );
	hp.c = (ldb)( l.x * r.y - l.y * r.x );
}

//半平面相交求交点，保证有且只有一个交点
inline void inter(hp_t const&l,hp_t const&r,point64f_t&p){
	ldb xishu = l.a * r.b - r.a * l.b;
	p.x = ( l.b * r.c - r.b * l.c ) / xishu;
	p.y = ( l.c * r.a - l.a * r.c ) / xishu;
}

//判断点是否在半平面内
inline bool isIn(point64f_t const&p,hp_t const&hp){
	ldb v = hp.a * p.x + hp.b * p.y + hp.c;
	return v >= - EPS;
}

//排序增量法，
//输入的半平面至少为3个，因为会加包围盒
//会改变hp里面的内容,hp最后保存剩下的半平面
int sandi(hp_t hp[],int n,int&bot,int&top){
    //排序
    sort(hp,hp+n);

    //完全平行的半平面只取一个
    n = unique(hp,hp+n,isPara) - hp;

    bot = 0, top = 1;

    point64f_t p;
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
//将多边形往内移动radius距离
void moveHP(hp_t hp[],int n,double radius){
	for(int i=0;i<n;++i)
		hp[i].c -= radius * sqrt(hp[i].a*hp[i].a+hp[i].b*hp[i].b);
	//半平面向法向移动，只改变c的值
}

ldb dist(const point64f_t&A,const point64f_t&B){
    ldb x = A.x - B.x;
    ldb y = A.y - B.y;
    return sqrt(x*x+y*y);
}

ldb cross(point64f_t const&O,point64f_t const&A,point64f_t const&B){
    ldb xoa = A.x - O.x;
    ldb yoa = A.y - O.y;
    ldb xob = B.x - O.x;
    ldb yob = B.y - O.y;
    return xoa * yob - xob * yoa;
}

point_t P[210];
hp_t Hp[210];
point64f_t P64[210];

int main(){
    //freopen("1.txt","r",stdin);
    //freopen("2.txt","w",stdout);
    int nofkase;
    scanf("%d",&nofkase);
    for(int kase=1;kase<=nofkase;++kase){
        int n,r,a,b;
        scanf("%d%d%d%d",&n,&r,&a,&b);
        for(int i=0;i<n;++i)scanf("%lld%lld",&P[i].x,&P[i].y);

        //先算一下多边形的面积
        llt area = 0;
        for(int i=1;i<=n-2;++i){
            area += cross(P[0],P[i],P[i+1]);
        }

        //如果b>=a
        if(b>=a){
            printf("%.12f\n",(ldb)ABS(area)*0.5*a);
            continue;
        }

        //将点集改成逆时针
        if (area<0){
            for(int i=0;i<n/2;++i)swap(P[i],P[n-i-1]);
            area = -area;
        }


        //生成半平面
        P[n] = P[0];
        for(int i=0;i<n;++i){
            genHP(P[i],P[i+1],Hp[i]);
            //printf("%d: %d %d %d %d\n",i,P[i].x,P[i].y,P[i+1].x,P[i+1].y);
            //printf("%f %f %f\n",Hp[i].a,Hp[i].b,Hp[i].c);
        }

        //往里面移动r
        moveHP(Hp,n,r);

        //求一个半平面相交
        int bot,top;
        int ret = sandi(Hp,n,bot,top);
        if(ret<=2){//半平面相交为空集
            printf("%.12f\n",(ldb)area*0.5*a);
            continue;
        }

        //首先计算半平面的交点
        Hp[top+1] = Hp[bot];
        int k = 0;
        for(int i=bot;i<=top;++i) inter(Hp[i],Hp[i+1],P64[k++]);

        //计算周长和面积
        ldb zhouchang = 0;
        ldb mianji = 0;
        for(int i=1;i<=k-2;++i) mianji += cross(P64[0],P64[i],P64[i+1]);
        P64[k] = P64[0];
        for(int i=0;i<k;++i) zhouchang += dist(P64[i],P64[i+1]);
        mianji *= 0.5;

        //结果
        ldb bmianji = mianji + zhouchang * r + PI * r * r;
        ldb aminaji = (ldb)area * 0.5 - bmianji;
        printf("%.12f\n",bmianji*b+aminaji*a);
    }
    return 0;
}
