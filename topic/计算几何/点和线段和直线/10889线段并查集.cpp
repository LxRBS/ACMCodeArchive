#include <iostream>
#include <map>
#include <string>
using namespace std;

#define SIZE 503

#define MAX(a,b) ( (a) > (b) ? (a) : (b) )
#define MIN(a,b) ( (a) < (b) ? (a) : (b) )

struct road_t{
	double x0,y0;
	double x1,y1;
	road_t(double a=0.,double b=0.,double c=0.,double d=0.):
	x0(a),y0(b),x1(c),y1(d){}
}Road[SIZE];

//叉积
double cross(double x0,double y0,double x1,double y1,double x2,double y2){
    double x01 = x1 - x0;
	double y01 = y1 - y0;
	double x02 = x2 - x0;
	double y02 = y2 - y0;
	return x01 * y02 - x02 * y01;
}

//线段相交
bool isInter(int i,int j){
	return MAX(Road[i].x0,Road[i].x1) >= MIN(Road[j].x0,Road[j].x1)
		&& MAX(Road[i].y0,Road[i].y1) >= MIN(Road[j].y0,Road[j].y1)
		&& MAX(Road[j].x0,Road[j].x1) >= MIN(Road[i].x0,Road[i].x1)
		&& MAX(Road[j].y0,Road[j].y1) >= MIN(Road[i].y0,Road[i].y1)
		&& cross(Road[i].x0,Road[i].y0,Road[j].x0,Road[j].y0,Road[i].x1,Road[i].y1)
		 * cross(Road[i].x0,Road[i].y0,Road[i].x1,Road[i].y1,Road[j].x1,Road[j].y1) >= 0
	    && cross(Road[j].x0,Road[j].y0,Road[i].x0,Road[i].y0,Road[j].x1,Road[j].y1)
		 * cross(Road[j].x0,Road[j].y0,Road[j].x1,Road[j].y1,Road[i].x1,Road[i].y1) >= 0;
}

int Father[SIZE];

map<string,int> Map;

void init(int n){
	for(int i=0;i<n;++i)
		Father[i] = i;
}

int find(int n){
	int k = Father[n];
	return ( n == k ) ? n : ( Father[n] = find(k) );
}

void unite(int x,int y){
    x = find(x);
	y = find(y);
	Father[y] = x;
	return;
}

char Input[20];

int main(){
	int n;
	scanf("%d",&n);

	init(n);

	for(int i=0;i<n;++i){
		scanf("%lf%lf%lf%lf%s",&Road[i].x0,&Road[i].y0,&Road[i].x1,&Road[i].y1,Input);
		Map[string(Input)] = i;
		for(int j=i-1;j>=0;--j){
			if ( isInter(i,j) ){
				unite(i,j);
//				break;
			}
		}
	}

	int m;
	scanf("%d%*c",&m);

	char ask0[20],ask1[20];
	for(int i=0;i<m;++i){
        scanf("%s%s",ask0,ask1);
		map<string,int>::iterator it = Map.find(string(ask0));
		if ( Map.end() == it ){
            printf("N\n");
			continue;
		}
		int x = it->second;

        it = Map.find(string(ask1));
		if ( Map.end() == it ){
			printf("N\n");
			continue;
		}
		int y = it->second;

		if ( find(x) == find(y) )
			printf("Y\n");
		else
			printf("N\n");
	}

	return 0;
}