#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>
using namespace std;

double const EPS = 1E-9;

#define isZero(x)  ( -EPS < (x) && (x) < EPS )

struct point_t{
	int x;
	int y;
	point_t(int a=0,int b=0):x(a),y(b){}
}Point[101];

struct point64f_t{
	double x;
	double y;
};

bool operator == (point64f_t const&l,point64f_t const&r){
	return isZero(l.x-r.x) && isZero(l.y-r.y);
}

//��ƽ�����ݽṹ
struct hp_t{
	double a;
	double b;
	double c;    //ֱ��ax+by+c
	double angle;//���������ǣ���ax+by+c>=0ʱ��������ǡ��Ϊ(a,b)
	hp_t(double aa=0.0,double bb=0.0,double cc=0.0,double theta=0.0):
	a(aa),b(bb),c(cc),angle(theta){}
}Hp[105];

//�����������ڵ�����ֵ���϶�����0����
inline int calcLoc(double x,double y){
	if ( isZero(x) ) return y > 0 ? 5 : 1; //5��ʾy������1��ʾy������
	if ( isZero(y) ) return x > 0 ? 2 : 7; //2:x������7:x������

	if ( x > 0 ) return y > 0 ? 4 : 2; //4����һ���ޣ�2����������
	return y > 0 ? 6 : 0;    //6:������; 0:��������
}
//���ݰ�ƽ�淨�����ļ��ǽ�������ʵ�������ò������
bool cmp(hp_t const&left,hp_t const&right){
    int leftloc = calcLoc(left.a,left.b);
	int rightloc = calcLoc(right.a,right.b);
	//������������ڲ�ͬ���򣬿�ֱ�ӷ��ؽ��
	if ( leftloc != rightloc ) return leftloc < rightloc;

	//������
	double chaji = left.a * right.b - left.b * right.a;
	
	//��֤�Ƚϵİ�ƽ�治ƽ��
	if ( !isZero(chaji) )	return chaji > 0;

	//���Ϊ0��˵����ƽ��ƽ�У�Խ������������ԽС
	if ( left.a > EPS ){
        //��aΪ���������
	    //��hp1��hp2�������������������a1x+b1y+c1=0��a2x+b2y+c2>0
		return left.c * right.a < left.a * right.c;
	}

    if ( left.a < -EPS ) return left.a * right.c < left.c * right.a;

	//ʣ����ΪaȡֵΪ0���������ʱ����b����
	if ( left.b > EPS ) return left.c * right.b < left.b * right.c;

	//��bΪ����a��b������ͬʱΪ0
	return left.b * right.c < left.c * right.b;
}

//���������ɰ�ƽ�棬��֪left��rightΪ˳ʱ�룬����������Ϊ�������
void genHP(point_t const&left,point_t const&right,hp_t&hp){
    hp.a = (double)(right.y - left.y);
	hp.b = (double)(left.x - right.x);
	hp.c = (double)(right.x * left.y - right.y * left.x);

	//˳ʱ�뷽��������뷨�������Ϊ������Ϊ���Ļ���a��b��c���
//	if ( hp.a * hp.b > 0 ) {
//        hp.a = -hp.a;
//		hp.b = -hp.b;
//		hp.c = -hp.c;
//	}
    //��������������ģ����ǿ��ǵ�������ʹ�ò����������  
//	hp.angle = atan2(hp.b,hp.a);
}

//�ж�����ƽ���Ƿ�ƽ��
inline bool isParallel(hp_t const&left,hp_t const&right){
	return calcLoc(left.a,left.b) == calcLoc(right.a,right.b) 
		&& isZero( left.a * right.b - left.b * right.a );
}

//��ƽ���ཻ�󽻵㣬p�������������֤��ƽ�治ƽ��
void inter(hp_t const&left,hp_t const&right,point64f_t&p){
    double xishu = left.a * right.b - right.a * left.b;
	p.x = ( left.b * right.c - right.b * left.c ) / xishu;
	p.y = ( left.c * right.a - left.a * right.c ) / xishu;
}

//�жϵ��Ƿ��ڰ�ƽ����
inline bool isIn(point64f_t const&p,hp_t const&hp){
	double v = hp.a * p.x + hp.b * p.y + hp.c;
	return isZero(v) || v > 0;
}

int main(){
	int n;
	int kase = 0;
	while( scanf("%d",&n) && n ){
		//����㼯����֪Ϊ��ʱ��
        for(int i=0;i<n;++i)scanf("%d%d",&Point[i].x,&Point[i].y);

        //���ݵ㼯���ɰ�ƽ��
        Point[n] = Point[0];
		for(int i=0;i<n;++i) 
			genHP(Point[i],Point[i+1],Hp[i]);
		
		//�������ȡֵ��Χ�İ�ƽ��ȷ�����������Χ���˴�����Ҫ
// 		genHP(point_t(INT_MIN,INT_MIN),point_t(INT_MAX,INT_MIN),Hp[n]);
// 		genHP(point_t(INT_MAX,INT_MIN),point_t(INT_MAX,INT_MAX),Hp[n+1]);
// 		genHP(point_t(INT_MAX,INT_MAX),point_t(INT_MIN,INT_MAX),Hp[n+2]);
// 		genHP(point_t(INT_MIN,INT_MAX),point_t(INT_MIN,INT_MIN),Hp[n+3]);

		//����
		sort(Hp,Hp+n,cmp);

		//������ͬ�İ�ƽ�棬ֻ����һ�����˴���������������������ģ�Ҳ���Ǳ�����С��
		Hp[n] = Hp[0];//�����У���һ�������һ�����Բ���ƽ�У�����ʡȥ�˼��iԽ�������
		int k = 0;
		for(int i=1;i<n;){
            while( isParallel(Hp[k],Hp[i]) ) ++i;
			if ( i == n ) break;
			Hp[k+1] = Hp[i];
			k = k + 1;
			++i;
		}
		
		//k�ǲ����������İ�ƽ�����
		k = k + 1;

		//ִ��ѭ��
		int bot = 0;
		int top = 1;
		for(int i=2;i<k;++i){
			//��ǰ��������ƽ���ཻ
			while( bot < top ){
				//�󽻵�
				point64f_t p;
				inter(Hp[top-1],Hp[top],p);
				//�ڰ�ƽ���⣬������
                if ( !isIn(p,Hp[i]) ) --top;
				else                  break;
			}
			//����������ƽ���ཻ
			while( bot < top ){
				point64f_t p;
				inter(Hp[bot],Hp[bot+1],p);
				if ( isIn(p,Hp[i]) ) break;
				else                 ++bot;
			}
			//��ֵ
			Hp[++top] = Hp[i];
		}

		//������ֻ����2���������ٵİ�ƽ�棬�϶�����
		if ( top - bot <= 1 ){
			++kase;
			printf("Floor #%d\n",kase);
            printf("Surveillance is impossible.\n");
			printf("\n");
			continue;
		}

		//��ǰ��������ƽ���ཻ
		while( bot < top ){
			//�󽻵�
			point64f_t p;
			inter(Hp[top-1],Hp[top],p);
			//�����˵İ�ƽ���⣬�������
			if ( !isIn(p,Hp[bot]) ) --top;
			else                    break;
		}	
        //����������ƽ���ཻ
		while( bot < top ){
			point64f_t p;
			inter(Hp[bot],Hp[bot+1],p);
			if ( isIn(p,Hp[top]) ) break;
			else                   ++bot;
		}

		//ʣ��İ�ƽ���󽻵�
        vector<point64f_t> vec;
		Hp[top+1] = Hp[bot];
		for(int i=bot;i<=top;++i){
			point64f_t p;
			inter(Hp[i],Hp[i+1],p);
			vec.push_back(p);
		}

        //ȥ���غϵĵ㣬�˴�����Ҫ����ΪֻҪ��һ����Ϳ�����������
//		vector<point64f_t>::iterator it;
//		it = unique(vec.begin(),vec.end());

        //���
		++kase;
		printf("Floor #%d\n",kase);
		if ( vec.empty() ) printf("Surveillance is impossible.\n");
		else               printf("Surveillance is possible.\n");
        printf("\n");
	}
	return 0;
}