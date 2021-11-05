//�������κ;��ν��������ʹ�ð�ƽ���ཻ����
#include <cstdio>
#include <algorithm>
using namespace std;

double const EPS = 1E-8;

inline bool is0(double x){return -EPS < x && x < EPS;}

struct point_t{
	int x;
	int y;
	point_t(int a=0,int b=0):x(a),y(b){}
};
int cross(point_t const&O,point_t const&A,point_t const&B){
    int xoa = A.x - O.x;
    int yoa = A.y - O.y;
    int xob = B.x - O.x;
    int yob = B.y - O.y;
    return xoa * yob - xob * yoa;
}
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

//��������������ı�hp���������
int sandi(hp_t hp[],int n,point64f_t ans[]){
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

    if ( top - bot < 2 ) return 0;

    int k = 0;
    for(int i=bot;i<top;++i) inter(hp[i],hp[i+1],ans[k++]);
    inter(hp[top],hp[bot],ans[k++]);
    return k;
}

hp_t Hp[12];
int main(){
    //freopen("1.txt","r",stdin);
    point_t a,b,c;
    point_t r,s,t,u;
    point64f_t ans[100];
    while( EOF != scanf("%d%d%d%d%d%d%d%d",&a.x,&a.y,&c.x,&b.y,&r.x,&r.y,&t.x,&t.y) ){
        b.x = a.x;c.y = a.y;
        s.x = r.x;s.y = t.y;
        u.x = t.x;u.y = r.y;

        //triangle
        if ( cross(a,b,c) > 0 ){
            genHP(b,a,Hp[0]);
            genHP(c,b,Hp[1]);
            genHP(a,c,Hp[2]);
        }else{
            genHP(a,b,Hp[0]);
            genHP(b,c,Hp[1]);
            genHP(c,a,Hp[2]);
        }

        //rectangle
        genHP(r,s,Hp[3]);
        genHP(s,t,Hp[4]);
        genHP(t,u,Hp[5]);
        genHP(u,r,Hp[6]);

        //boundary
        Hp[7].a = 1.0, Hp[7].b = Hp[7].c = 0.0;
        Hp[8].a = 0.0, Hp[8].b = -1.0, Hp[8].c = 10000.0;
        Hp[9].a = -1.0, Hp[9].b = 0.0, Hp[9].c = 10000.0;
        Hp[10].a = Hp[10].c = 0.0, Hp[10].b = 1.0;

        sort(Hp,Hp+11);
        hp_t*p = unique(Hp,Hp+11,isPara);

        int n = p - Hp;
        n = sandi(Hp,n,ans);

        if ( n < 3 ){
            printf("0.00000000\n");
            continue;
        }

        double r = 0.0;
        for(int i=1;i<n-1;++i){
            r += cross(ans[0],ans[i],ans[i+1]);
        }
        printf("%.8f\n",r/2.0);
    }
}
