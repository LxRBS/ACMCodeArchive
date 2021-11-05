#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;

double const EPS = 1E-11;
double const INF = 1E9;

#define is0(x) ( - EPS <= (x) && (x) <= EPS )
#define isEq(x,y) is0( (x) - (y) )

struct point_t{
	int x;
	int y;
}P[203];

struct point64f_t{
	double x;
	double y;
};

struct hp_t{
	double a;
	double b;
	double c;//ax+by+c>=0,(a,b)��������
}Hp[210];

//���ݷ������ļ�������(0~360)��������ͬ��Խ������������ԽС
bool operator < (hp_t const&l,hp_t const&r){
	//�������ֱ�λ��x�����£�����ֱ�ӵõ����
	int ly = l.b >= 0 ? 1 : -1;
	int ry = r.b >= 0 ? 1 : -1;
	if ( ly != ry ) return ly > ry;
	//�����λ��x����
	if ( is0(l.b) && is0(r.b) && l.a * r.a < 0 )
		return l.a > r.a;

	double chaji = l.a * r.b - l.b * r.a;

	if ( !is0(chaji) ) return chaji > 0;

	//��������ȫƽ�У���aΪ��ʱ
	if ( l.a > EPS ){
		//��hp1��hp2�������������������a1x+b1y+c1=0��a2x+b2y+c2>0
		return l.c * r.a < l.a * r.c;
	}

	if ( l.a < - EPS )return l.c * r.a > l.a * r.c;

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

//��l��r����֤����ʱ�뷽��
inline void genHP(point_t const&l,point_t const&r,hp_t&hp){
    hp.a = (double)( l.y - r.y );
	hp.b = (double)( r.x - l.x );
	hp.c = (double)( l.x * r.y - l.y * r.x );
}

//��ƽ���ཻ�󽻵㣬��֤����ֻ��һ������
inline void inter(hp_t const&l,hp_t const&r,point64f_t&p){
	double xishu = l.a * r.b - r.a * l.b;
	p.x = ( l.b * r.c - r.b * l.c ) / xishu;
	p.y = ( l.c * r.a - l.a * r.c ) / xishu;
}

//�жϵ��Ƿ��ڰ�ƽ����
inline bool isIn(point64f_t const&p,hp_t const&hp){
	double v = hp.a * p.x + hp.b * p.y + hp.c;
	return v >= - EPS;
}

//��������������ı�hp���������
bool sandi(hp_t hp[],int n){
	int bot = 0;
	int top = 1;
	for(int i=2;i<n;++i){
		//��ǰ�˵�������ƽ���ཻ
		while( bot < top ){
			point64f_t p;
			inter(hp[top-1],hp[top],p);
			//p�ڵ�ǰ��ƽ���⣬������
			if ( isIn(p,hp[i]) ) break;
			else                 --top;
		}
		//��׶˵�������ƽ���ཻ
		while( bot < top ){
			point64f_t p;
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
		point64f_t p;
		inter(hp[top-1],hp[top],p);
		//p�ڵ�ǰ��ƽ���⣬������
		if ( isIn(p,hp[bot]) ) break;
		else                   --top;
	}
	while( bot < top ){
		point64f_t p;
		inter(hp[bot],hp[bot+1],p);
		//p�ڵ�ǰ��ƽ���⣬������
		if ( isIn(p,hp[top]) ) break;
		else                   ++bot;
	}
	//ʣ��3�������İ�ƽ����н���
	return top - bot > 1;
}
//������������ƶ�radius����
void moveHP(hp_t hp[],int n,double radius){
	for(int i=0;i<n;++i)
		hp[i].c -= radius * sqrt(hp[i].a*hp[i].a+hp[i].b*hp[i].b);
	//��ƽ�������ƶ���ֻ�ı�c��ֵ
}
int main(){
	int n;
	while( scanf("%d",&n) && n ){
		int xmin = INT_MAX, xmax = INT_MIN;
		for(int i=0;i<n;++i){
			scanf("%d%d",&P[i].x,&P[i].y);
			if ( P[i].x < xmin ) xmin = P[i].x;
			if ( P[i].x > xmax ) xmax = P[i].x;
		}
		P[n] = P[0];
		//���ɰ�ƽ��
		for(int i=0;i<n;++i)genHP(P[i],P[i+1],Hp[i]);
		//���ұն��ַ�
		double left = 0.00001;                        //���ܵ���Сֵ
		double right = (double)( xmax - xmin ) / 2.0; //���ܵ����ֵ
		double mid;
		hp_t hp[210];
		do{			
			copy(Hp,Hp+n,hp);
			//������������ƶ�mid����
            mid = ( left + right ) / 2;
			moveHP(hp,n,mid);
			int nn = n;
			//����
			sort(hp,hp+nn);
			//��ȫƽ�еİ�ƽ��ֻȡһ��
			hp_t* p = unique(hp,hp+nn,isPara);
			nn = p - hp;
			if ( sandi(hp,nn) ) left = mid; //+ 0.000001;//����ط��Ӽ�1E-5ʼ�չ����ˣ��ĳ�1E-6��OK��
			else                right = mid; // - 0.000001;//��ȫ���Բ���...
		}while( left + 0.000001 <= right + EPS );
		printf("%lf\n",right);
	}
	return 0;
}
