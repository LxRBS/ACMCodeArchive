/*
    A到达集合点的时间为[t1,t2]等概率
    B到达集合点的时间为[s1,s2]等概率
    任何人到达后w时间后离开
    问碰面的概率

    碰面的概率是x=t1,x=t2,y=s1,y=s2和|x-y|<=w围成的面积
    除以矩形的面积
*/

#include <stdio.h>
#include <algorithm>
using namespace std;

double const EPS = 1E-9;
inline bool is0(double x){return -EPS<=x&&x<=EPS;}

struct point_t{
    int x,y;
    point_t(int xx=0,int yy=0):x(xx),y(yy){}
};

struct point64f_t{
    double x,y;
    point64f_t(double xx=0.0,double yy=0.0):x(xx),y(yy){}
};

struct hp_t{
    double a,b,c;//ax+by+c>=0,法向量始终是(a,b)
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
	hp.a = (double)( l.y - r.y );
	hp.b = (double)( r.x - l.x );
	hp.c = (double)( l.x * r.y - l.y * r.x );
}

//半平面相交求交点，保证有且只有一个交点
inline void inter(hp_t const&l,hp_t const&r,point64f_t&p){
	double xishu = l.a * r.b - r.a * l.b;
	p.x = ( l.b * r.c - r.b * l.c ) / xishu;
	p.y = ( l.c * r.a - l.a * r.c ) / xishu;
}

//判断点是否在半平面内
inline bool isIn(point64f_t const&p,hp_t const&hp){
	double v = hp.a * p.x + hp.b * p.y + hp.c;
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

double cross(point64f_t const&O,point64f_t const&A,point64f_t const&B){
    double xoa = A.x - O.x;
    double yoa = A.y - O.y;
    double xob = B.x - O.x;
    double yob = B.y - O.y;
    return xoa * yob - xob * yoa;
}

hp_t Hp[10];
point64f_t P64[10];
int main(){
    int nofkase;
    scanf("%d",&nofkase);

    int t1,t2,s1,s2,w,n,bot,top,k;
    for(int kase=1;kase<=nofkase;++kase){
        scanf("%d%d%d%d%d",&t1,&t2,&s1,&s2,&w);

        //生成半平面
        genHP(point_t(t1,s1),point_t(t2,s1),Hp[0]);
        genHP(point_t(t2,s1),point_t(t2,s2),Hp[1]);
        genHP(point_t(t2,s2),point_t(t1,s2),Hp[2]);
        genHP(point_t(t1,s2),point_t(t1,s1),Hp[3]);

        Hp[4].a = -1, Hp[4].b = 1, Hp[4].c = w;
        Hp[5].a = 1, Hp[5].b = -1, Hp[5].c = w;

        n = sandi(Hp,6,bot,top);

        printf("Case #%d: ",kase);

        if ( n <= 2 ){
            printf("0\n");
            continue;
        }

        k = 0;
        Hp[top+1] = Hp[bot];
        for(int i=bot;i<=top;++i) inter(Hp[i],Hp[i+1],P64[k++]);

        double area = 0.0;
        for(int i=0;i<k-1;++i) area += cross(P64[0],P64[i],P64[i+1]);
        printf("%.9f\n",area*0.5/((t2-t1)*(s2-s1)));
    }
    return 0;
}
