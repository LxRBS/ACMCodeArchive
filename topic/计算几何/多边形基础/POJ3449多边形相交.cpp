//多边形相交
#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;

#define MIN(x,y) ( (x) < (y) ? (x) : (y) )
#define MAX(x,y) ( (x) > (y) ? (x) : (y) )

double const EPS = 1E-6;
#define is0(x) ( -EPS < (x) && (x) < EPS )
#define isEq(x,y) is0( (x) - (y) )

//点的数据结构
struct point_t{
	double x,y;
	point_t(double a=0.0,double b=0.0):x(a),y(b){}
};

//线段的数据结构
struct lineseg_t{
	point_t s,e;
	lineseg_t(point_t const&a=point_t(),point_t const&b=point_t()):s(a),e(b){}
};

//多边形的数据结构
struct poly_t{
	point_t* vertex;
	int num;
	poly_t(point_t* p=0,int n=0):vertex(p),num(n){}
};

//叉积OA×OB
double cross(point_t const&O,point_t const&A,point_t const&B){
	double xoa = A.x - O.x;
	double yoa = A.y - O.y;
	double xob = B.x - O.x;
	double yob = B.y - O.y;
	return xoa * yob - xob * yoa;
}

//判断线段a和b是否相交
bool isInter(lineseg_t const&a,lineseg_t const&b){
	return MIN(a.s.x,a.e.x) <= MAX(b.s.x,b.e.x)
		&& MIN(b.s.x,b.e.x) <= MAX(a.s.x,a.e.x)
		&& MIN(a.s.y,a.e.y) <= MAX(b.s.y,b.e.y)
		&& MIN(b.s.y,b.e.y) <= MAX(a.s.y,a.e.y)
		&& cross(a.s,b.s,a.e) * cross(a.s,a.e,b.e) >= 0
		&& cross(b.s,a.e,b.e) * cross(b.s,b.e,a.s) >= 0;
}

//判断多边形a和b是否相交，a、b均可退化
bool isInter(poly_t&a,poly_t&b){
	int& na = a.num;
	point_t* va = a.vertex;
	int& nb = b.num;
	point_t* vb = b.vertex;
	va[na] = va[0],vb[nb] = vb[0];

	//判断是否有边相交
	for(int i=0;i<na;++i)for(int j=0;j<nb;++j)
		if( isInter(lineseg_t(va[i],va[i+1]),lineseg_t(vb[j],vb[j+1])) )
			return true;

	return false;
}

void mkSquare(point_t const&A,point_t const&B,poly_t& poly){
    poly.num = 4;
    poly.vertex[0] = A;
	poly.vertex[2] = B;
	poly.vertex[1].x = (A.y-B.y+A.x+B.x)/2.0;
    poly.vertex[1].y = (B.x-A.x+A.y+B.y)/2.0;
	poly.vertex[3].x = A.x + B.x - poly.vertex[1].x;
	poly.vertex[3].y = A.y + B.y - poly.vertex[1].y;
	return;
}

void mkRect(point_t const&A,point_t const&B,point_t const&C,poly_t&poly){
    poly.num = 4;
	poly.vertex[0] = A;
	poly.vertex[1] = B;
	poly.vertex[2] = C;
	poly.vertex[3].x = A.x + C.x - B.x;
	poly.vertex[3].y = A.y + C.y - B.y;
	return;
}
char Input[10000];
point_t P[26][21];
poly_t Poly[26];

int widNum(int n){
	int ret = ( n >= 0 ? 0 : 1 );
	if ( n < 0 ) n = -n;
	if ( 10000 == n ) return ret + 5;
	if ( n >= 1000 ) return ret + 4;
	if ( n >= 100 ) return ret + 3;
	if ( n >= 10 ) return ret + 2;
	return ret + 1;
}

bool Flag[26] = {false};
void procString(){
    char s[20],ch;
	sscanf(Input,"%c%s",&ch,s);

	int sn = ch - 'A';
	Flag[sn] = true;

	if ( 's' == *s ){
        point_t A,B;
		sscanf(Input+9,"(%lf,%lf) (%lf,%lf)",&A.x,&A.y,&B.x,&B.y);
		mkSquare(A,B,Poly[sn]);
	}else if ( 'l' == *s ){
        sscanf(
			Input+7,"(%lf,%lf) (%lf,%lf)",
			&Poly[sn].vertex[0].x,
			&Poly[sn].vertex[0].y,
			&Poly[sn].vertex[1].x,
			&Poly[sn].vertex[1].y
		);
		Poly[sn].num = 2;
	}else if ( 't' == *s ){
		sscanf(
			Input+11,
			"(%lf,%lf) (%lf,%lf) (%lf,%lf)",
			&Poly[sn].vertex[0].x,
			&Poly[sn].vertex[0].y,
			&Poly[sn].vertex[1].x,
			&Poly[sn].vertex[1].y,
			&Poly[sn].vertex[2].x,
			&Poly[sn].vertex[2].y
		);
		Poly[sn].num = 3;
	}else if ( 'r' == *s ){
		point_t A,B,C;
		sscanf(Input+12,"(%lf,%lf) (%lf,%lf) (%lf,%lf)",&A.x,&A.y,&B.x,&B.y,&C.x,&C.y);
        mkRect(A,B,C,Poly[sn]);
	}else{
        int n;
		sscanf(Input+10,"%d",&n);
		int offset = 0;
		for(int i=0;i<n;++i){
			sscanf(
			    Input+12+(n>9)+offset,
				"(%lf,%lf)",
                &Poly[sn].vertex[i].x,
				&Poly[sn].vertex[i].y
			);
            offset += widNum(Poly[sn].vertex[i].x) + widNum(Poly[sn].vertex[i].y) + 4;
		}
		Poly[sn].num = n;
	}
}

void solve(){
	for(int i=0;i<26;++i){
		if ( !Flag[i] ) continue;
	
		int a[26];
		int cnt = 0;
		for(int j=0;j<26;++j){
			if ( !Flag[j] || i == j ) continue;

            if ( isInter(Poly[i],Poly[j]) )
				a[cnt++] = j;
		}
		
		if ( 0 == cnt ){
			printf("%c has no intersections\n",i+'A');
			continue;
		}

		if ( 1 == cnt ){
			printf("%c intersects with %c\n",i+'A',a[0]+'A');
			continue;
		}

		if ( 2 == cnt ){
			printf("%c intersects with %c and %c\n",i+'A',a[0]+'A',a[1]+'A');
			continue;
		}

		printf("%c intersects with",i+'A');
		for(int j=0;j<cnt-1;++j)
			printf(" %c,",a[j]+'A');
		printf(" and %c\n",a[cnt-1]+'A');
	}
}

int main(){
    for(int i=0;i<26;++i)Poly[i].vertex = P[i];

	bool first_flag = true;
	while( 1 ){
		gets(Input);

		if ( '.' == *Input ) return 0;

		if ( '-' == *Input ){
			if ( first_flag ) first_flag = false;
			else printf("\n");
			solve();
			fill(Flag,Flag+26,false);
			continue;
		}


		procString();		
	}
	return 0;
}