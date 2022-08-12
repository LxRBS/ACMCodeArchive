/*
    给定一系列的点，保证有原点、其余点分布在三个象限、所有点形成一个凸多边形，
    输入是不排序的，而要求从原点开始逆时针输出     
*/
#include <iostream>
#include <cmath>
#include <algorithm>
#include <fstream>
using namespace std;

double const INF = 1E6;
double const PI = acos(-1.);

bool quardrant[5] ;
struct point_t{
	int x;
	int y;
};

//返回幅角0-2PI
double angle1(int x,int y){
    if ( x == 0 && y > 0 ) return PI / 2.;
	if ( x == 0 && y < 0 ) return PI + PI / 2.;
	if ( x > 0 && y >= 0 ) return atan( (double) y / x );
	if ( x > 0 && y <= 0 ) return atan( (double) y / x ) + 2. * PI;
	if ( x < 0 && y >= 0 ) return atan( (double) y / x ) + PI;
	if ( x < 0 && y <= 0 ) return atan( (double) y / x ) + PI;
	return INF;
}
//返回幅角-PI到PI
double angle2(int x,int y){
	if ( x == 0 && y > 0 ) return PI / 2.;
	if ( x == 0 && y < 0 ) return -PI / 2.;
	if ( x > 0 && y >= 0 ) return atan( (double) y / x );
	if ( x > 0 && y <= 0 ) return atan( (double) y / x );
	if ( x < 0 && y >= 0 ) return atan( (double) y / x ) + PI;
	if ( x < 0 && y <= 0 ) return atan( (double) y / x ) - PI;
	return INF;
}
typedef double (*func_t)(int,int);
func_t func[5] = { NULL, &angle1, &angle2, &angle2, &angle1 };
func_t f ;

bool comp(const point_t &a,const point_t &b){
    return f(a.x,a.y) < f(b.x,b.y);
}


//返回坐标位于第几象限：0 1 2 3 4
//0代表在坐标轴上
int quard(int x,int y){
    if ( x > 0 && y > 0 ) return 1;
    if ( x > 0 && y < 0 ) return 4;
	if ( x < 0 && y > 0 ) return 2;
	if ( x < 0 && y < 0 ) return 3;
	return 0;
}

point_t point[55];

int main(){
//    ifstream cin("1.txt");
	memset(quardrant,0,sizeof(quardrant));
	int i = 0;
	int x,y;
	while( cin>>x>>y ){
		quardrant[quard(x,y)] = true;
		point[i].x = x;
		point[i].y = y;
		i++;
	}
    int n;
    for ( n=1;n<=4;n++ ) if ( !quardrant[n] ) break; //检查缺了第几象限的点
	f = func[n];  //使用相应的返回幅角的函数
    sort(point+1,point+i,comp); //按幅角升序排序
	for (int j=0;j<i;j++)      //搞定、输出
		printf("(%d,%d)\n",point[j].x,point[j].y);
//	getchar();getchar();getchar();
	return 1;
}
