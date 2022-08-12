/*
    这道题目提交POJ通过，提交HUNNU出错
 后将EPS从1E-6改为1E-9通过
    自己做过一组测试数据，其中有两个点
 的极角非常接近，在1E-6以下，所以两次
 求凸包的结果不稳定，改为1E-9以后，凸包
 结果稳定，最大三角形面积也随之稳定。
*/
#include <cmath>
#include <algorithm>
#include <iostream>
using namespace std;

struct point_t{
	int x;
	int y;
};

int cross(point_t const& O,point_t const& A,point_t const& B){
	int xoa = A.x - O.x;
	int yoa = A.y - O.y;
	int xob = B.x - O.x;
	int yob = B.y - O.y;
	return xoa * yob - yoa * xob;
}

point_t P[50000];

//为graham中排序写的比较函数
bool cmp(point_t const& left,point_t const& right){
    int xl = left.x - P->x;
	int yl = left.y - P->y;
	int xr = right.x - P->x;
	int yr = right.y - P->y;

	int xmul = xl * yr - yl * xr;

	//若A到B为顺时针，则B的极角肯定小于A，注意基点P[0]是最下最左点
	if ( xmul < 0 ) return false;

	if ( xmul > 0 ) return true;

	//如果A、B在同一直线，则距离近的更小
	if ( xl * xl + yl * yl < xr * xr + yr * yr )
		return true;

	return false;
}

//返回凸包的点数
int graham(int n){
	int blk = 0;
	//找最下最左点
	for(int i=1;i<n;i++){
        if ( (P+i)->y < (P+blk)->y || ( (P+i)->y==(P+blk)->y && (P+i)->x<(P+blk)->x ) )
			blk = i;
	}
	//交换
	point_t t(*P);
	*P = *(P+blk);
	*(P+blk) = t;

	std::sort(P+1,P+n,cmp);

	int top = 3;

	for(int i=3;i<n;i++){
		//严格凸包，凸包后没有共线的三点
		while( cross(*(P+top-2),*(P+top-1),*(P+i)) <= 0 )
			top--;
		*(P+top++) = *(P+i);
	}

	return top;
}

int main(){
	int i,j,k,n;
	while( EOF != scanf("%d",&n) ){
        for(i=0;i<n;i++)scanf("%d%d",&(P+i)->x,&(P+i)->y);
		
		if ( 1 == n || 2 == n ){
			printf("0.00\n");
			continue;
		}

		if ( 3 == n ){
			int ans = cross(*P,*(P+1),*(P+2));
			if ( ans < 0 ) ans = -ans;
				if ( ans % 2 ) printf("%d.50\n",ans/2);
		else           printf("%d.00\n",ans/2);
			continue;
		}

        n = graham(n);


		//上述步骤求凸包，结果就在p数组里面
		int edge;//用于记录某条边所能形成的最大三角形
		int tmp;
		int ans = 0;
		for(i=0;i<n-2;i++){
            j = i + 1;
			k = j + 1;
L1:
			edge = 0;
			while( k < n ){
				tmp = cross(P[i],P[j],P[k]);
				if ( tmp < 0 ) tmp = -tmp;
				if ( edge > tmp ) break;
				edge = tmp;
				k++;
			}
			if ( ans < edge ) ans = edge;
			//此时ijk三角形是以ij为边的最大三角形
			//更新答案，如果k已到达终点，不必再循环j
			//接下来循环j、k
			k--;
			j++;
			if ( j == n - 1 ) continue;
			goto L1;			
		}
			if ( ans % 2 ) printf("%d.50\n",ans/2);
		else           printf("%d.00\n",ans/2);
	}
	return 0;
}
