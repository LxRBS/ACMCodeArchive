/*
    �����κ˵����
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
    double a,b,c;//ax+by+c>=0,������ʼ����(a,b)
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

int cross(point_t const&O,point_t const&A,point_t const&B){
    int xoa = A.x - O.x;
    int yoa = A.y - O.y;
    int xob = B.x - O.x;
    int yob = B.y - O.y;
    return xoa * yob - xob * yoa;
}

double cross(point64f_t const&O,point64f_t const&A,point64f_t const&B){
    double xoa = A.x - O.x;
    double yoa = A.y - O.y;
    double xob = B.x - O.x;
    double yob = B.y - O.y;
    return xoa * yob - xob * yoa;
}

hp_t Hp[2110];
point_t P[2110];
point64f_t P64[2110];
int N;
int main(){
    //freopen("1.txt","r",stdin);
    int nofkase;
    scanf("%d",&nofkase);

    int bot,top;
    while(nofkase--){
        scanf("%d",&N);
        for(int i=0;i<N;++i)scanf("%d%d",&P[i].x,&P[i].y);

        //�ж�����
        int area = 0;
        for(int i=1;i<N-1;++i) area += cross(P[0],P[i],P[i+1]);

        //���ɰ�ƽ��
        P[N] = P[0];
        if(area>0)for(int i=0;i<N;++i) genHP(P[i],P[i+1],Hp[i]);
        else for(int i=0;i<N;++i) genHP(P[i+1],P[i],Hp[i]);

        if ( sandi(Hp,N,bot,top) <= 2 ){
            printf("0.00\n");
            continue;
        }

        //�󽻵�
        int k = 0;
        Hp[top+1] = Hp[bot];
        for(int i=bot;i<=top;++i) inter(Hp[i],Hp[i+1],P64[k++]);

        //�����
        double ans = 0.0;
        for(int i=0;i<k-1;++i) ans += cross(P64[0],P64[i],P64[i+1]);
        printf("%.2f\n",ans*0.5);
    }
    return 0;
}
