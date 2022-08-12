#include <cstdio>
#include <algorithm>
#include <cmath>


struct node_t{
	double start;
	double end;
};

//比较左边的起点大小
bool operator < (node_t const& left,node_t const& right){
    return left.start < right.start 
		|| ( left.start == right.start && left.end < right.end );
}

//qsort比较函数
// int cmp(void const* a,void const* b){
//     node_t* left = (node_t*)a;
// 	node_t* right = (node_t*)b;
// 
// 	if( left->start < right->start 
// 		|| ( left->start == right->start && left->end < right->end ) )
// 		return -1;
// 	return 1;
// }

int main(){
	int n;
	int bx,by;
	int cx,cy,r;
	double k1,k2;

	node_t node[500];

	//一元二次方程系数
	double a,b,c;
	double delta;

    while(1){
		scanf("%d",&n);
	
		if ( 0 == n ) return 0;

		scanf("%d%d",&bx,&by);

		memset(node,0,sizeof(node));

		for(int i=0;i<n;i++){
			scanf("%d%d%d",&cx,&cy,&r);
            
			a = ( cx - bx ) * ( cx - bx ) - r * r;
			b = 2 * ( cx - bx ) * ( by - cy );
			c = ( by - cy ) * ( by - cy ) - r * r;

			delta = sqrt( b * b - 4 * a * c );

			//解方程求切线斜率
			if ( 0 != a ){
                k1 = ( delta - b ) / ( 2.0 * a );
				k2 = - ( delta + b ) / ( 2.0 * a );
                (node+i)->start = bx - by / k1;
				(node+i)->end = bx - by / k2;
			}else{
				//当某个切线斜率为无穷大时
                k1 = - c / b;
				(node+i)->start = bx - by / k1;
				(node+i)->end = bx;
			}

			//确保start小于end
			if ( (node+i)->start > (node+i)->end ){
				double t = (node+i)->start;
				(node+i)->start = (node+i)->end;
				(node+i)->end = t;
			}
      
		}

		std::sort(node,node+n);
//		std::qsort(node,n,sizeof(node[0]),cmp);
	
		double start = node->start;
		double end = node->end;

		for(int i=1;i<n;i++){
			if ( (node+i)->start > end ){
				printf("%.2lf %.2lf\n",start,end);
				start = (node+i)->start;
				end = (node+i)->end;
			}else{
		        if ( (node+i)->end > end )
					end = (node+i)->end;
			}
		}

		printf("%.2lf %.2lf\n\n",start,end);
	}
}
