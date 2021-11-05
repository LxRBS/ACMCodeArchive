#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

double const EPS = 1E-17;
double const INF = 1E100;

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
double cross(point64f_t const&O,point64f_t const&A,point64f_t const&B){
	double xoa = A.x - O.x;
	double yoa = A.y - O.y;
	double xob = B.x - O.x;
	double yob = B.y - O.y;
	return xoa * yob - xob * yoa;
}
//��㶨��˳��
bool operator < (point64f_t const&l,point64f_t const&r){
	return l.x < r.x || ( isEq(l.x,r.x) && l.y < r.y );
}
bool operator == (point64f_t const&l,point64f_t const&r){
	return isEq(l.x,r.x) && isEq(l.y,r.y);
}
//�������ȷ���������ļ�������
point64f_t Origin;
bool cmp(point64f_t const&l,point64f_t const&r){
	double xl = l.x - Origin.x;
	double yl = l.y - Origin.y;
	double xr = r.x - Origin.x;
	double yr = r.y - Origin.y;
	double chaji = xl * yr - yl * xr;
	return chaji > 0 || ( isZero(chaji) && l.x * l.x + l.y * l.y < r.x * r.x + r.y * r.y );
}
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
//��l��r����֤����ʱ�뷽��a��b��Ψһȷ����
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
	//����ʣ����3����ƽ�棬˵��>=0�϶��н⣬������Ҫ��>0�Ľ�
	//�󽻵�
    vector<point64f_t> v(top-bot+1);
	inter(hp[top],hp[bot],v[top-bot]);
	for(int i=bot;i<top;++i) 
		inter(hp[i],hp[i+1],v[i-bot]);
	
	//�޳��ظ��ĵ�
	sort(v.begin(),v.end());
	vector<point64f_t>::iterator it = unique(v.begin(),v.end());
    v.erase(it,v.end());
	
	if ( v.size() <= 2 ) return false;
	//��Ҫ��ʣ�µĵ㲻�ܹ��ߣ������µĴ����ƺ��鷳�˵�
	int k = 0;
	for(unsigned int i=1;i<v.size();++i){
		if ( v[i].y < v[k].y || ( isEq(v[i].y,v[k].y) && v[i].x < v[k].x ) )
			k = i;
	}
    Origin = v[k];
	v[k] = v[0];
	v[0] = Origin;
	sort(v.begin()+1,v.end(),cmp);
       //�����
	double area=0.0;
	for(unsigned int i=1;i<v.size()-1;++i) 
		area += cross(v[0],v[i],v[i+1]);
	if ( isZero(area) ) return false;
	return true;
}

point_t P[55];
hp_t Hp[105];
int V[105],U[105],W[105];

int main(){
	int n;
	while( EOF != scanf("%d",&n) ){
		for(int i=0;i<n;++i)scanf("%d%d%d",V+i,U+i,W+i);
		//��ÿһ�������߹���һ���ƽ��������
		for(int kase=0;kase<n;++kase){
			bool flag = false;
			int k = 0;
			for(int i=0;i<n;++i){
				if ( i == kase ){
					k = 1;
					continue;
				}
				if ( V[i] >= V[kase] && U[i] >= U[kase] && W[i] >= W[kase] ){
				    flag = true;
					break;
				}
                Hp[i-k].a = (double)(V[kase]-V[i])/(double)V[i]/(double)V[kase];
				Hp[i-k].b = (double)(U[kase]-U[i])/(double)U[i]/(double)U[kase];
				Hp[i-k].c = (double)(W[kase]-W[i])/(double)W[i]/(double)W[kase];
			}

			if ( flag ){
				printf("No\n");
				continue;
			}

			int nn = n - 1;
			//��һ����Χ��
			Hp[nn].a = 0.0;
			Hp[nn].b = -1.0;
			Hp[nn].c = INF;
			++nn;
			Hp[nn].a = 0.0;
			Hp[nn].b = 1.0;
			Hp[nn].c = 0.0;
			++nn;
			Hp[nn].a = 1.0;
			Hp[nn].b = 0.0;
			Hp[nn].c = 0.0;
			++nn;
			Hp[nn].a = - 1.0;
			Hp[nn].b = 0.0;
			Hp[nn].c = INF;
			++nn;

			//����
			sort(Hp,Hp+nn);

			//��ȫƽ�еİ�ƽ��ֻȡһ��
			hp_t* p = unique(Hp,Hp+nn,isPara);

			//������İ�ƽ����� 
			nn = p - Hp;

			//S&I
			printf(sandi(Hp,nn)?"Yes\n":"No\n");
		}
	}
	return 0;
}
