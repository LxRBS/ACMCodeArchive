#include <cstdio>
#include <set>
#include <cmath>
#include <utility>

double const INF = 1E170;
double const EPS = 1E-9;

struct node_t{
	double start;
	double end;
	node_t(double x=0.,double y=0.){start=x;end=y;}
};

//�Ƚ���ߵ�����С
bool operator < (node_t const& left,node_t const& right){
    return left.start < right.start 
		|| ( left.start == right.start && left.end < right.end );
}

int main(){
	int n;
	int bx,by;
	int cx,cy,r;
	double k1,k2;

	node_t node;
	std::set<node_t> Set;
	typedef std::set<node_t>::iterator set_it_t;
	std::pair<set_it_t,bool> Pair;


	//һԪ���η���ϵ��
	double a,b,c;
	double delta;

    while(1){
		scanf("%d",&n);
	
		if ( 0 == n ) return 0;

		scanf("%d%d",&bx,&by);

		//���ú�����
		Set.clear();
        Set.insert(node_t(-INF,-INF + EPS));
		Set.insert(node_t(INF,INF + EPS));

		for(int i=0;i<n;i++){
			scanf("%d%d%d",&cx,&cy,&r);
            
			a = ( cx - bx ) * ( cx - bx ) - r * r;
			b = 2 * ( cx - bx ) * ( by - cy );
			c = ( by - cy ) * ( by - cy ) - r * r;

			delta = sqrt( b * b - 4 * a * c );

			//�ⷽ��������б��
			if ( 0 != a ){
                k1 = ( delta - b ) / ( 2.0 * a );
				k2 = - ( delta + b ) / ( 2.0 * a );
                node.start = bx - by / k1;
				node.end = bx - by / k2;
			}else{
				//��ĳ������б��Ϊ�����ʱ
                k1 = - c / b;
				node.start = bx - by / k1;
				node.end = bx;
			}

			//ȷ��startС��end
			if ( node.start > node.end ){
				double t = node.start;
				node.start = node.end;
				node.end = t;
			}
			
            Pair = Set.insert(node);
			
			if ( !Pair.second ) continue;
			
			//ȷ��ǰ������
			set_it_t it = Pair.first;
			it--;
			set_it_t fit = it;
            it = Pair.first;

			//��������ص�
			//����Ҫдѭ��������ֻ�ж�1��
//			if ( it->start <= fit->end ){
// 				if ( it->end > fit->end )
// 			        fit->end = it->end;
// 				Set.erase(it);
// 				it = fit;
//			}
			bool flag = false;
			while ( it->start <= fit->end ){
				flag = true;
				if ( it->end > fit->end )
					fit->end = it->end;
				Set.erase(it);
				it = fit;
				it++;
			}
			
			//ȡ��ߵĵ�����
			set_it_t bit;
			if ( flag ) {
				it = fit;
                bit = it;
				bit++;
			}else{
				bit = it;
				bit++;
			}
			

			//�����ұ��ص� 
			while ( it->end >= bit->start ){
				if ( it->end < bit->end )
				    it->end = bit->end;
				Set.erase(bit);
				bit = it;
				bit++;
			}
		}

		set_it_t it = Set.begin();
		set_it_t itend = Set.end();
		itend--;
		for(it++;it!=itend;it++){
			printf("%.2lf %.2lf\n",it->start,it->end);
		}

		printf("\n");
	}
}
