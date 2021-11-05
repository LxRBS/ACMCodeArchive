/*
    ����һϵ�еĵ㣬��֤��ԭ�㡢�����ֲ����������ޡ����е��γ�һ��͹����Σ�
    �����ǲ�����ģ���Ҫ���ԭ�㿪ʼ��ʱ�����     
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

//���ط���0-2PI
double angle1(int x,int y){
    if ( x == 0 && y > 0 ) return PI / 2.;
	if ( x == 0 && y < 0 ) return PI + PI / 2.;
	if ( x > 0 && y >= 0 ) return atan( (double) y / x );
	if ( x > 0 && y <= 0 ) return atan( (double) y / x ) + 2. * PI;
	if ( x < 0 && y >= 0 ) return atan( (double) y / x ) + PI;
	if ( x < 0 && y <= 0 ) return atan( (double) y / x ) + PI;
	return INF;
}
//���ط���-PI��PI
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


//��������λ�ڵڼ����ޣ�0 1 2 3 4
//0��������������
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
    for ( n=1;n<=4;n++ ) if ( !quardrant[n] ) break; //���ȱ�˵ڼ����޵ĵ�
	f = func[n];  //ʹ����Ӧ�ķ��ط��ǵĺ���
    sort(point+1,point+i,comp); //��������������
	for (int j=0;j<i;j++)      //�㶨�����
		printf("(%d,%d)\n",point[j].x,point[j].y);
//	getchar();getchar();getchar();
	return 1;
}
