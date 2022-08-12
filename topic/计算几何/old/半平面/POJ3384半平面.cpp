#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
using namespace std;

double const EPS = 1E-9;

#define isZero(x) ( - EPS <= (x) && (x) <= EPS )
#define isEq(x,y) isZero( (x) - (y) )

struct point_t{
	int x;
	int y;
	point_t(int a=0,int b=0):x(a),y(b){}
};
struct point64f_t{
	double x;
	double y;
	point64f_t(double a=0.0,double b=0.0):x(a),y(b){}
};
struct hp_t{
	double a;
	double b;
	double c;//ax+by+c>=0��������ʼ����(a,b)
};
//���ݷ������ļ�������(-180,180]��������ͬ��Խ������������ԽС
bool operator < (hp_t const&l,hp_t const&r){
	//�������ֱ�λ��x�����£�����ֱ�ӵõ����
	int ly = l.b >= 0 ? 1 : -1;
	int ry = r.b >= 0 ? 1 : -1;
	if ( ly != ry ) return ly < ry;
	//�����λ��x����
	if ( isZero(l.b) && isZero(r.b) && l.a * r.a < 0 )
		return l.a > r.a;

	double chaji = l.a * r.b - l.b * r.a;

	if ( !isZero(chaji) ) return chaji > 0;

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
	if ( isZero(l.b) && isZero(r.b) ) return l.a * r.a > 0;
	return isZero( l.a * r.b - r.a * l.b );
}
//��l��r����֤��˳ʱ�뷽��a��b��Ψһȷ����
inline void genHP(point_t const&l,point_t const&r,hp_t&hp){
	hp.a = - (double)( l.y - r.y );
	hp.b = - (double)( r.x - l.x );
	hp.c = - (double)( l.x * r.y - l.y * r.x );
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
//������뷽
inline double calDist2(point64f_t const&l,point64f_t const&r){
	double x = l.x - r.x;
	double y = l.y - r.y;
	return x * x + y * y;
}
//��������������ı�hp���������
bool sandi(hp_t hp[],int n,point64f_t ans[]){
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
	//���Ᵽ֤�н⣬�󽻵�
	vector<point64f_t> vp;
	hp[top+1] = hp[bot];
	for(int i=bot;i<=top;++i){
		point64f_t p;
		inter(hp[i],hp[i+1],p);
		vp.push_back(p);
	}
	//�󽻵��������Զ��2��
	double dst = 0.0;
	int k1 = 0,k2 = 0;
	for(unsigned int i=0;i<vp.size()-1;++i)for(unsigned int j=i+1;j<vp.size();++j){
		double dtmp = calDist2(vp[i],vp[j]);
		if ( dtmp > dst ) dst = dtmp, k1 = i, k2 = j;
	}
    ans[0] = vp[k1];
	ans[1] = vp[k2];
	return true;
}

//������������ƶ�radius����
void moveHP(hp_t hp[],int n,double radius){
	for(int i=0;i<n;++i)
		hp[i].c -= radius * sqrt(hp[i].a*hp[i].a+hp[i].b*hp[i].b);
	//��ƽ�������ƶ���ֻ�ı�c��ֵ
}

point_t P[105];
hp_t Hp[105];


int main(){
	int n,r;
	while( EOF != scanf("%d%d",&n,&r) ){
		for(int i=0;i<n;++i)scanf("%d%d",&P[i].x,&P[i].y);
		P[n] = P[0];
		//���ɰ�ƽ��
		for(int i=0;i<n;++i) genHP(P[i],P[i+1],Hp[i]);
		//����
		sort(Hp,Hp+n);
		//��ȫƽ�еİ�ƽ��ֻȡһ��
		hp_t* p = unique(Hp,Hp+n,isPara);
		//������İ�ƽ����� 
		n = p - Hp;
		moveHP(Hp,n,(double)r);
		//S&I
		point64f_t ansp[2];
		sandi(Hp,n,ansp);
		printf("%.4lf %.4lf %.4lf %.4lf\n",ansp->x,ansp->y,ansp[1].x,ansp[1].y);
	}
	return 0;
}
