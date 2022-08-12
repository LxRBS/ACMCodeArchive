#include <iostream>
#include <algorithm>
#include <deque>
using namespace std;

long double const EPS = 1E-8;

#define isZero(x) ( - EPS < (x) && (x) < EPS )

inline long double cross(double a1,double b1,double a2,double b2){
	return a1 * b2 - a2 * b1;
}

struct point64f_t{
	long double x;
	long double y;
	point64f_t(long double a=0.0,long double b=0.0):x(a),y(b){}
	bool operator == (point64f_t const&r){
		return isZero(x-r.x) && isZero(y-r.y);
	}
};

long double cross(point64f_t const&O,point64f_t const&A,point64f_t const&B){
	long double xoa = A.x - O.x;
	long double yoa = A.y - O.y;
	long double xob = B.x - O.x;
	long double yob = B.y - O.y;
	return xoa * yob - xob * yoa;
}

struct hp_t{
	long double a,b,c; //ax+by+c>0������������(a, b)
	hp_t(long double aa=0.0,long double bb=0.0,long double cc=0.0):
	a(aa),b(bb),c(cc){}
}Hp[20000+4+3];

//a/bΪ��������������ͬʱΪ0�����Ǵ�0~360
inline int calLoc(long double a,long double b){
	if ( isZero(a) ) return b > 0 ? 2 : 6;
	if ( isZero(b) ) return a > 0 ? 0 : 4;
	if ( a > 0 ) return b > 0 ? 1 : 7;
	return b > 0 ? 3 : 5;
}

// ��ƽ��ȴ�С�����÷������ļ���
bool operator < (hp_t const&l,hp_t const&r){
    int locl = calLoc(l.a,l.b);
	int locr = calLoc(r.a,r.b);
	if ( locl != locr ) return locl < locr;

	long double chaji = cross(l.a,l.b,r.a,r.b);
    if ( !isZero(chaji) ) return chaji > 0;

	//�������0����ƽ��ƽ�С�Խ���������������ԽС
	if ( l.a > EPS ){
		//��aΪ���������
		//��hp1��hp2�������������������a1x+b1y+c1=0��a2x+b2y+c2>0
		return l.c * r.a < l.a * r.c;
	}

	if ( l.a < -EPS ) return l.a * r.c < l.c * r.a;

	//ʣ����ΪaȡֵΪ0���������ʱ����b����
	if ( l.b > EPS ) return l.c * r.b < l.b * r.c;

	//��bΪ����a��b������ͬʱΪ0
	return l.b * r.c < l.c * r.b;
}
//�жϵ��Ƿ���hp��
inline bool isIn(point64f_t const&p,hp_t const&hp){
	double v = hp.a * p.x + hp.b * p.y + hp.c;
	return isZero(v) || v > 0;
}
//�ж�l��r�Ƿ�ƽ�У����������Ƿ���һ��
inline bool isParallel(hp_t const&l,hp_t const&r){
	return calLoc(l.a,l.b) == calLoc(r.a,r.b) 
		&& isZero( l.a * r.b - l.b * r.a );
}
//��ƽ���ཻ��ֱ�ߵĽ��㣬��֤l��r�н���
inline void inter(hp_t const&l,hp_t const&r,point64f_t&p){
	double xishu = l.a * r.b - r.a * l.b;
	p.x = ( l.b * r.c - r.b * l.c ) / xishu;
	p.y = ( l.c * r.a - l.a * r.c ) / xishu;
}

//����������
void sandi(hp_t hp[],int n,deque<point64f_t>&ans){
	//Ԥ������ƽ�еİ�ƽ��ֻ������С��Ҳ���������������
	Hp[n] = Hp[0];//���㴦����һ�������һ�����Բ���ƽ��
	int k = 0;
	for(int i=1;i<n;){
		while( isParallel(Hp[k],Hp[i]) ) ++i;
		if ( i == n ) break;
		Hp[k+1] = Hp[i];
		k = k + 1;
		++i;
	}
	//n��Ԥ�����Ժ�İ�ƽ�����
	n = k + 1;

	int bot = 0, top = 1;
	for(int i=2;i<n;++i){
		//��ǰ��������ƽ���ཻ
		while( bot < top ){
			point64f_t p;
			inter(hp[top-1],hp[top],p);
			//�ڰ�ƽ���ڣ������
			if ( isIn(p,hp[i]) ){
				break;

			//�ڰ�ƽ���⣬������
			}else{
				--top;
			}
		}

		//����������ƽ���ཻ
		while( bot < top ){
			point64f_t p;
			inter(hp[bot],hp[bot+1],p);

			if ( isIn(p,hp[i]) ){
				break;
			}else{
				++bot;
			}
		}

	    //��ֵ
        hp[++top] = hp[i];
	}

	//������İ�ƽ�����������϶����ԣ�������˰�Χ���Ժ�һ����Χ��һ����յ�����
	if ( top - bot <= 1 ){
		ans.clear();
		return;
	}

	//����
	while( bot < top ){
		point64f_t p;
		inter(hp[top-1],hp[top],p);
		
		//�����˵İ�ƽ���⣬�������
		if ( isIn(p,Hp[bot]) ){
			break;
		}else{
			--top;
		}
	}
	while( bot < top ){
		point64f_t p;
		inter(hp[bot],hp[bot+1],p);
		
		if ( isIn(p,Hp[top]) ){
			break;
		}else{
			++bot;
		}
	}

	if ( top - bot <= 1 ){
		ans.clear();
		return;
	}

	//ʣ��İ�ƽ���󽻵�
	hp[top+1] = hp[bot];
	ans.clear();
	for(int i=bot;i<=top;++i){
		point64f_t p;
		inter(hp[i],hp[i+1],p);
		ans.push_back(p);
	}

	//ȥ���غϵĵ㣬�˴�����Ҫ����ΪֻҪ��һ����Ϳ�����������
	deque<point64f_t>::iterator it;
	it = unique(ans.begin(),ans.end());
	ans.erase(it,ans.end());
	return;
}

int main(){
	int n;
	scanf("%d",&n);
	for(int i=0;i<n;++i){
		long double x1,y1,x2,y2;
		scanf("%Lf%Lf%Lf%Lf",&x1,&y1,&x2,&y2);
		Hp[i].a = y1 - y2;
		Hp[i].b = x2 - x1;
		Hp[i].c = x1 * y2 - x2 * y1;
	}
	//դ��
	Hp[n].a = 1.0;Hp[n].b = 0.0;Hp[n].c = 0.0;
	Hp[++n].a = 0.0;Hp[n].b = 1.0;Hp[n].c = 0.0;
	Hp[++n].a = -1.0;Hp[n].b = 0.0;Hp[n].c = 10000.0;
	Hp[++n].a = 0.0;Hp[n].b = -1.0;Hp[n].c = 10000.0;

	n = n + 1;

    //����
	sort(Hp,Hp+n);

	deque<point64f_t> ans;
	sandi(Hp,n,ans);

	//��͹����ε����
	if ( ans.size() <= 2 ){
		printf("0.0\n");
		return 0;
	}

	long double area = 0.0;
	for(unsigned int i=1;i<ans.size()-1;++i){
        area += cross(ans[0],ans[i],ans[i+1]);
	}
	if ( area < 0 ) area = -area;

	printf("%.1Lf\n",area/2.0);
	return 0;
}
