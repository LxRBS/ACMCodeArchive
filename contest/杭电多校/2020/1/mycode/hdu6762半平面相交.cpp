/**
   һ��͹����Σ��ð뾶Ϊr��Բ���ǣ�ÿ����λҪBԪ��
   ֱ�Ӹ���ÿ����λҪAԪ
   ������Ҫ����Ǯ���Ը�������ͼ��
   ���B>=A��ֱ�Ӽ��������������A����
   ���B<A���������߽ǵ�������ֱ������Ӽ���
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
    ldb a,b,c;//ax+by+c>=0,������ʼ����(a,b)
};

//���ݷ������ļ��Ǳȴ�С(-180,180]��������ͬ��Խ������������ԽС
bool operator < (hp_t const&l,hp_t const&r){
    //�������ֱ�λ��x�����£�����ֱ�ӵõ����
	int ly = l.b >= 0 ? 1 : -1;
	int ry = r.b >= 0 ? 1 : -1;
	if ( ly != ry ) return ly < ry;

	//�����λ��x���ϣ���һ������һ������
	if ( is0(l.b) && is0(r.b) && l.a * r.a < 0 ) return l.a > r.a;

	//����������������Ϊ��
    double chaji = l.a * r.b - l.b * r.a;
    if ( !is0(chaji) ) return chaji > 0;

    //�ܵ��˴�˵��������ƽ��

    //��a����0ʱ
    if ( l.a > EPS ){
		//��hp1��hp2�������������������a1x+b1y+c1=0��a2x+b2y+c2>0
		return l.c * r.a < l.a * r.c;
	}

	if ( l.a < - EPS ) return l.c * r.a > l.a * r.c;

	//a���Ϊ0��b��Ȼ��Ϊ0
	if ( l.b > EPS ) return l.c * r.b < l.b * r.c;
	return l.c * r.b > l.b * r.c;
}

//�жϰ�ƽ���Ƿ�ƽ��
bool isPara(hp_t const&l,hp_t const&r){
	int ly = l.b >= 0 ? 1 : -1;
	int ry = r.b >= 0 ? 1 : -1;
	if ( ly != ry ) return false;
	if ( is0(l.b) && is0(r.b) ) return l.a * r.a > 0;
	return is0( l.a * r.b - r.a * l.b );
}

//��l��r����֤����ʱ�뷽��a��b��Ψһȷ����
inline void genHP(point_t const&l,point_t const&r,hp_t&hp){
	hp.a = (ldb)( l.y - r.y );
	hp.b = (ldb)( r.x - l.x );
	hp.c = (ldb)( l.x * r.y - l.y * r.x );
}

//��ƽ���ཻ�󽻵㣬��֤����ֻ��һ������
inline void inter(hp_t const&l,hp_t const&r,point64f_t&p){
	ldb xishu = l.a * r.b - r.a * l.b;
	p.x = ( l.b * r.c - r.b * l.c ) / xishu;
	p.y = ( l.c * r.a - l.a * r.c ) / xishu;
}

//�жϵ��Ƿ��ڰ�ƽ����
inline bool isIn(point64f_t const&p,hp_t const&hp){
	ldb v = hp.a * p.x + hp.b * p.y + hp.c;
	return v >= - EPS;
}

//������������
//����İ�ƽ������Ϊ3������Ϊ��Ӱ�Χ��
//��ı�hp���������,hp��󱣴�ʣ�µİ�ƽ��
int sandi(hp_t hp[],int n,int&bot,int&top){
    //����
    sort(hp,hp+n);

    //��ȫƽ�еİ�ƽ��ֻȡһ��
    n = unique(hp,hp+n,isPara) - hp;

    bot = 0, top = 1;

    point64f_t p;
    for(int i=2;i<n;++i){
        //��ǰ�˵�������ƽ���ཻ
        while( bot < top ){
            inter(hp[top-1],hp[top],p);
            //p�ڵ�ǰ��ƽ���⣬������
			if ( isIn(p,hp[i]) ) break;
			else                 --top;
        }
        //��׶˵�������ƽ���ཻ
		while( bot < top ){
			inter(hp[bot],hp[bot+1],p);
			//p�ڵ�ǰ��ƽ���⣬������
			if ( isIn(p,hp[i]) ) break;
			else                 ++bot;
		}
		//��ֵ
		hp[++top] = hp[i];
    }

    //����
	while( bot < top ){
		inter(hp[top-1],hp[top],p);
		//p�ڵ�ǰ��ƽ���⣬������
		if ( isIn(p,hp[bot]) ) break;
		else                   --top;
	}
	while( bot < top ){
		inter(hp[bot],hp[bot+1],p);
		//p�ڵ�ǰ��ƽ���⣬������
		if ( isIn(p,hp[top]) ) break;
		else                   ++bot;
	}

	return top - bot + 1;
}
//������������ƶ�radius����
void moveHP(hp_t hp[],int n,double radius){
	for(int i=0;i<n;++i)
		hp[i].c -= radius * sqrt(hp[i].a*hp[i].a+hp[i].b*hp[i].b);
	//��ƽ�������ƶ���ֻ�ı�c��ֵ
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

        //����һ�¶���ε����
        llt area = 0;
        for(int i=1;i<=n-2;++i){
            area += cross(P[0],P[i],P[i+1]);
        }

        //���b>=a
        if(b>=a){
            printf("%.12f\n",(ldb)ABS(area)*0.5*a);
            continue;
        }

        //���㼯�ĳ���ʱ��
        if (area<0){
            for(int i=0;i<n/2;++i)swap(P[i],P[n-i-1]);
            area = -area;
        }


        //���ɰ�ƽ��
        P[n] = P[0];
        for(int i=0;i<n;++i){
            genHP(P[i],P[i+1],Hp[i]);
            //printf("%d: %d %d %d %d\n",i,P[i].x,P[i].y,P[i+1].x,P[i+1].y);
            //printf("%f %f %f\n",Hp[i].a,Hp[i].b,Hp[i].c);
        }

        //�������ƶ�r
        moveHP(Hp,n,r);

        //��һ����ƽ���ཻ
        int bot,top;
        int ret = sandi(Hp,n,bot,top);
        if(ret<=2){//��ƽ���ཻΪ�ռ�
            printf("%.12f\n",(ldb)area*0.5*a);
            continue;
        }

        //���ȼ����ƽ��Ľ���
        Hp[top+1] = Hp[bot];
        int k = 0;
        for(int i=bot;i<=top;++i) inter(Hp[i],Hp[i+1],P64[k++]);

        //�����ܳ������
        ldb zhouchang = 0;
        ldb mianji = 0;
        for(int i=1;i<=k-2;++i) mianji += cross(P64[0],P64[i],P64[i+1]);
        P64[k] = P64[0];
        for(int i=0;i<k;++i) zhouchang += dist(P64[i],P64[i+1]);
        mianji *= 0.5;

        //���
        ldb bmianji = mianji + zhouchang * r + PI * r * r;
        ldb aminaji = (ldb)area * 0.5 - bmianji;
        printf("%.12f\n",bmianji*b+aminaji*a);
    }
    return 0;
}
