#include <cstdio>
#include <cmath>
#include <climits>
#include <queue>
#include <algorithm>
using namespace std;

struct point_t{
	float x;
	float y;
	point_t(float a=0.f,float b=0.f):x(a),y(b){}
}P[80];

struct linesg_t{
    point_t s;
	point_t e;
}Ls[80];

float const EPS = 1E-6f;
#define is0(x) ( -EPS < (x) && (x) < EPS )
#define MIN(x,y) ( (x) < (y) ? (x) : (y) )
#define MAX(x,y) ( (x) > (y) ? (x) : (y) )

inline float dist(point_t const& A,point_t const& B){
	float x = A.x - B.x;
	float y = A.y - B.y;
	return sqrt( x * x + y * y );
};

//叉积，OA×OB
float cross(point_t const& O,point_t const& A,point_t const& B){
	float xoa = A.x - O.x;
	float yoa = A.y - O.y;
	float xob = B.x - O.x;
	float yob = B.y - O.y;
	return xoa * yob - xob * yoa;
}

//判断线段AB是否相交线段CD,而且不交于端点
bool isInter(point_t const& A,point_t const& B,point_t const& C,point_t const& D){
    return MIN(A.x,B.x) < MAX(C.x,D.x)
		&& MIN(C.x,D.x) < MAX(A.x,B.x)
		&& MIN(A.y,B.y) < MAX(C.y,D.y)
		&& MIN(C.y,D.y) < MAX(A.y,B.y)
		&& cross(A,C,B) * cross(A,B,D) > 0
		&& cross(C,B,D) * cross(C,D,A) > 0;
}

//0表示起点，1表示终点
float Graph[80][80];
//n表示墙的数量
void build(int n){
	//点的数量
	int pn = ( n << 2 ) + 2;
	//线段的数量
	int ln = n * 3;

    //计算每个点的距离
	for(int i=0;i<pn;++i)for(int j=i+1;j<pn;++j){
		//判断线段ij是否与其他线段相交
		bool flag = true;
		for(int k=0;k<ln;++k){
			if ( isInter(P[i],P[j],Ls[k].s,Ls[k].e) ){
				Graph[i][j] = Graph[j][i] = 1E9f;
				flag = false;
				break;
			}
		}
		if ( flag ) Graph[i][j] = Graph[j][i] = dist(P[i],P[j]);
	}
	return;
}

float Dist[80];
bool Flag[80];
//spfa算法，源始终为P[0]，n为墙的数量
void spfa(int n){
	int pn = ( n << 2 ) + 2;

    fill(Dist,Dist+80,1E8f);
    Dist[0] = 0.f;
	fill(Flag,Flag+80,false);
	Flag[0] = true;

	queue<int> q;
	q.push(0);

	while( !q.empty() ){
        int u = q.front();
		q.pop();
		Flag[u] = false;

		for(int i=0;i<pn;++i){
			if ( i == u ) continue;

			float tmp = Dist[u] + Graph[u][i];
			if ( tmp < Dist[i] ){
				Dist[i] = tmp;
				if ( !Flag[i] ) q.push(i),Flag[i] = true;
			}
		}
	}
	return;
}

int main(){
	P->x = 0.f;P->y = 5.f;
	P[1].x = 10.f;P[1].y = 5.f;

	int n;
	while( scanf("%d",&n) ){
		if ( -1 == n ) return 0;

		//输入
		for(int i=0;i<n;++i){
		    float x,y[4];
			scanf("%f%f%f%f%f",&x,y,y+1,y+2,y+3);

			//每堵墙4个点
            P[(i<<2)+2].x = P[(i<<2)+3].x
			          = P[(i<<2)+4].x
					  = P[(i<<2)+5].x
					  = x;
			P[(i<<2)+2].y = y[0];
            P[(i<<2)+3].y = y[1];
			P[(i<<2)+4].y = y[2];
			P[(i<<2)+5].y = y[3];

			//每堵墙3个线段
            Ls[i*3].s = point_t(x,0.f);
			Ls[i*3].e = P[(i<<2)+2];
			Ls[i*3+1].s = P[(i<<2)+3];
			Ls[i*3+1].e = P[(i<<2)+4];
			Ls[i*3+2].s = P[(i<<2)+5];
			Ls[i*3+2].e = point_t(x,10.f);
		}

		//建图
		build(n);

		//SPFA
		spfa(n);

		printf("%.2f\n",Dist[1]);
	}
	return 0;
}