#include <cstdio>
#include <algorithm>

#define SIZE 10000

struct point_t{
	int x;
	int y;
};

//叉积，OA×OB
int cross(point_t const& O,point_t const& A,point_t const& B){
    int xoa = A.x - O.x;
	int yoa = A.y - O.y;
	int xob = B.x - O.x;
	int yob = B.y - O.y;
	return xoa * yob - yoa * xob;
}

point_t Point[SIZE];

//以Point[0]为基点，比较left与right的极角，left < right返回真
bool cmp(point_t const& left,point_t const& right){
    int xl = left.x - Point->x;
	int yl = left.y - Point->y;
	int xr = right.x - Point->x;
	int yr = right.y - Point->y;
    
	int xmul = xl * yr - yl * xr;

	//说明A到B为顺时针，则B的极角肯定小于A，注意基点Point[0]是最下最左点
	if ( xmul < 0 ) return false;

	if ( xmul > 0 ) return true;

	//如果A、B在同一直线，则距离近的更小
	if ( xl * xl + yl * yl < xr * xr + yr * yr ) return true;

	return false;
}

int main(){
    int n;
	scanf("%d",&n);

	//输入的同时求最下最左点
	int bottomleft = SIZE + 1;
	int bottom = 1001;
	int left = 1001;

	for(int i=0;i<n;i++){
        scanf("%d%d",&(Point+i)->x,&(Point+i)->y);
		if ( (Point+i)->y < bottom || ( (Point+i)->y == bottom && (Point+i)->x < left ) ){
			bottom = (Point+i)->y;
			left = (Point+i)->x;
			bottomleft = i;
		}
	}

	if ( 1 == n || 2 == n ){
		printf("0\n");
		return 0;
	}

	if ( 3 == n ){
		int ans = cross(*Point,*(Point+1),*(Point+2)) / 100;
		if ( ans < 0 ) ans = -ans;
		printf("%d\n",ans);
		return 0;
	}

	//交换
	point_t tmp(*Point);
	*Point = *( Point + bottomleft );
	*(Point+bottomleft) = tmp;

	//以基点按极角排序
	std::sort(Point+1,Point+n,cmp);

	int top = 3;

	for(int i=3;i<n;i++){
        while( cross(*(Point+top-2),*(Point+top-1),*(Point+i)) <= 0 )
			top--;
		*(Point+top++) = *(Point+i);
	}

	//求面积
	int ans = 0;
	for(int i=1;i<top-1;i++){
        ans += cross(*Point,*(Point+i),*(Point+i+1));
	}

	printf("%d\n",ans/100);

	return 0;
}