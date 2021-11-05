#include <iostream>
#include <algorithm>
using namespace std;

typedef long long int ll_t;

struct point_t{
	ll_t x;
	ll_t y;
	ll_t t;
	point_t(ll_t a=0,ll_t b=0):x(a),y(b),t(1LL){}
};

struct hp_t{
	ll_t a;
	ll_t b;
	ll_t c;//ax+by+c>=0��������ʼ����(a,b)
};
inline int area(ll_t x,ll_t y){
	if ( y >= 0 ) return x > 0 ? 0 : 1;
	return x <= 0 ? 2 : 3;
}
//���ݷ������ļ�������0~360��������ͬ��Խ������������ԽС
bool operator < (hp_t const&l,hp_t const&r){
	//������
	int al = area(l.a,l.b);
	int ar = area(r.a,r.b);
	if ( al != ar ) return al < ar;

	//����
	ll_t chaji = l.a * r.b - l.b * r.a;
	if ( chaji ) return chaji > 0;

	//��������������
	//��������ȫƽ�У���aΪ��ʱ
	if ( l.a > 0 ){
		//��hp1��hp2�������������������a1x+b1y+c1=0��a2x+b2y+c2>0
		return l.c * r.a < l.a * r.c;
	}

	if ( l.a < 0 )return l.c * r.a > l.a * r.c;

	//a���Ϊ0��b��Ȼ��Ϊ0
	if ( l.b > 0 ) return l.c * r.b < l.b * r.c;
	return l.c * r.b > l.b * r.c;
}
//�жϰ�ƽ���Ƿ�ƽ��
bool isPara(hp_t const&left,hp_t const&right){
	return area(left.a,left.b) == area(right.a,right.b)
		&& left.a * right.b == right.a * left.b;
}
ll_t gcd(ll_t a,ll_t b){
	if ( 0 == a ) return b;
	if ( 0 == b ) return a;
	if ( a < 0 ) a = -a;
	if ( b < 0 ) b = -b;

	ll_t r;
	while( a % b ){
		r = a % b;
		a = b;
		b = r;
	}
	return b;
}
//��l��r����֤����ʱ�뷽��a��b��Ψһȷ����
inline void genHP(point_t const&l,point_t const&r,hp_t&hp){
    hp.a = l.y - r.y;
	hp.b = r.x - l.x;
    hp.c = l.x * r.y - l.y * r.x;

// 	int g = gcd(hp.a,hp.b);
// 	g = gcd(g,hp.c);
// 
// 	hp.a /= g;
// 	hp.b /= g;
// 	hp.c /= g;
}
//��ƽ���ཻ�󽻵㣬��֤����ֻ��һ������
inline void inter(hp_t const&l,hp_t const&r,point_t&p){
	p.x = l.b * r.c - r.b * l.c;
	p.y = r.a * l.c - l.a * r.c;
	p.t = l.a * r.b - r.a * l.b;
}
//�жϵ��Ƿ��ڰ�ƽ����
inline bool isIn(point_t const&p,hp_t const&hp){
	ll_t r = p.x * hp.a + p.y * hp.b + p.t * hp.c;
	return p.t > 0 ? r >= 0 : r <= 0;
}
//��������������ı�hp���������
bool sandi(hp_t hp[],int n){
    int bot = 0;
	int top = 1;
	for(int i=2;i<n;++i){
		//��ǰ�˵�������ƽ���ཻ
		while( bot < top ){
			point_t p;
			inter(hp[top-1],hp[top],p);
			//p�ڵ�ǰ��ƽ���⣬������
			if ( isIn(p,hp[i]) ) break;
			else                 --top;
		}
		//��׶˵�������ƽ���ཻ
		while( bot < top ){
			point_t p;
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
		point_t p;
		inter(hp[top-1],hp[top],p);
		//p�ڵ�ǰ��ƽ���⣬������
		if ( isIn(p,hp[bot]) ) break;
		else                   --top;
	}
	while( bot < top ){
		point_t p;
		inter(hp[bot],hp[bot+1],p);
		//p�ڵ�ǰ��ƽ���⣬������
		if ( isIn(p,hp[top]) ) break;
		else                   ++bot;
	}
	return top - bot > 1;
}

point_t P[55];
hp_t Hp[55];
int main(){
	int n;
	while( scanf("%d",&n) && n ){
		for(int i=0;i<n;++i)scanf("%lld%lld",&P[i].x,&P[i].y);
		P[n] = P[0];
		//���ɰ�ƽ��
        for(int i=0;i<n;++i) genHP(P[i],P[i+1],Hp[i]);
		//����
        sort(Hp,Hp+n);
		//��ȫƽ�еİ�ƽ��ֻȡһ��
		hp_t* p = unique(Hp,Hp+n,isPara);
		//������İ�ƽ����� 
		n = p - Hp;
		//S&I
		printf(sandi(Hp,n)?"1\n":"0\n");
	}
	return 0;
}
