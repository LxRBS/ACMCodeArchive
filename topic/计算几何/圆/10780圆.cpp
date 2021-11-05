#include <cstdio>
#include <algorithm>
#include <list>

#include <cmath>

using namespace std;

double const PI = acos(-1.0);
double const EPS = 1E-9;

#define SIZE 1000

#define isZero(x) ( (x) < EPS && (x) > -EPS )
#define isEqual(a,b) isZero((a)-(b))
#define isLT(a,b)  ( (a) < (b) - EPS )
#define isGT(a,b)  ( (a) > (b) + EPS )

struct node_t{
	double start;
	double end;
	node_t(double s=0.0,double e=0.0){start=s;end=e;}
};

struct circle_t{
	int x;
	int y;
	int radius;
}Cir[SIZE];

bool cmpdist(circle_t const& left,circle_t const& right){
	return left.x * left.x + left.y * left.y - left.radius * left.radius
		< right.x * right.x + right.y * right.y - right.radius * right.radius;
}

list<node_t> List;

void proc1st(circle_t const& cir){
	double theta;
	
	if ( 0 == cir.x ){
		if ( cir.y > 0 ) theta = PI / 2.0;
		else         theta = 3.0 * PI / 2.0;
	}else{
		theta = atan((double)cir.y/(double)cir.x);
		if ( cir.x < 0 )
			theta += PI; 
	}

	if ( theta < 0 ) theta += 2.0 * PI;

	double beta = asin((double)cir.radius/sqrt((double)(cir.x*cir.x+cir.y*cir.y)));

	double a = theta - beta;
	double b = theta + beta;

	if ( isLT(a,0.0) ){
		List.push_back(node_t(0.0,b));
		List.push_back(node_t(a+2.0*PI,2.0*PI));
		return;
	}

	if ( isGT(b,2.0*PI) ){
		List.push_back(node_t(0.0,b-2.0*PI));
		List.push_back(node_t(a,2.0*PI));
		return;
	}

    List.push_back(node_t(a,b));
	return;
}

//a、b保证在0到2PI
bool check(double a,double b){
	list<node_t>::iterator it;

	//首先寻找到a后面的已存在区间段，用it指向
	for(it=List.begin();it!=List.end();it++){
        if ( isLT(a,it->start) ) break;
	}   

	//a有可能落在it之前的那个区间，用fit表示
	//注意，list的迭代器没有重载加减法，只能使用加加、减减操作
	list<node_t>::iterator fit = it;
	fit--;

	//keepit用来指示插入的位置，如果需要插入的话
	list<node_t>::iterator keepit;
	
	double a_k;

	//一定要用EPS进行关系判断，不能直接使用<=之类
	if ( isLT(a,fit->end) || isEqual(a,fit->end) ){
		//ab区间是已有区间
		if ( isLT(b,fit->end) || isEqual(b,fit->end) )
            return false;

		//如果a落在fit内，则插入位置还在fit之前
		keepit = fit;
		keepit--;
		a_k = fit->start;
	}else{
		//如果a没有落在fit内，则插入位置就在fit
		keepit = fit;
		a_k = a;
		fit = it;
	}

	//确定b落在什么位置
	while( isGT(b,it->start) || isEqual(b,it->start) ) it++;
	it--;

	double b_k;
	if ( isGT(b,it->end) ) b_k = b;
	else               b_k = it->end;

	it++;

	//确定好新的区间段[a_k,b_k]之后，将有关的区间段全部删除
	//如果不需要删除也没有关系，fit和it之间的关系自然就会使得erase失去作用
    List.erase(fit,it);

	//注意不是在keepit插入，而是在其之后插入
	//因为list的删除会使得后续迭代器均失效，因此我们需要维持最后一个没有变化的迭代器，这就是keepit，然后再在其后进行插入操作
	keepit++;

	List.insert(keepit,node_t(a_k,b_k));

	return true;
}

bool procNext(circle_t const* cir){
	double theta;
	bool flag;

	if ( 0 == cir->x ){
		if ( cir->y > 0 ) theta = PI / 2.0;
		else         theta = 3.0 * PI / 2.0;
	}else{
		theta = atan((double)cir->y/(double)cir->x);
		if ( cir->x < 0 )
			theta += PI; 
	}

	if ( theta < 0 ) theta += 2.0 * PI;

	double beta = asin((double)cir->radius/sqrt((double)(cir->x*cir->x+cir->y*cir->y)));

	//a/b是视角范围，a、b之差一定在PI以内
	double a = theta - beta;
	double b = theta + beta;

	//a小于0，则分两段加入
	if ( isLT(a,0.0) ){
		flag = check(0.0,b);
		flag = check(a+2.0*PI,2.0*PI) || flag;
		return flag ;
	}

	//b大于2PI，也分两段加入
	if ( isGT(b,2.0*PI) ){
		flag = check(0.0,b-2.0*PI);
		flag = check(a,2.0*PI) || flag;
		return flag;
	}

	return check(a,b);
}
int main(){
	int n;
	double ans;

	while( scanf("%d",&n) && n ){
        for(int i=0;i<n;i++)
			scanf("%d%d%d",&(Cir+i)->x,&(Cir+i)->y,&(Cir+i)->radius);

		sort(Cir,Cir+n,cmpdist);

        List.clear();
        List.push_front(node_t(-3.0,-2.0));

		//将最近的圆加入，并求出最近圆的距离
		//最近圆一定是可以看见的
		proc1st(Cir[0]);
		ans = sqrt((double)(Cir->x*Cir->x+Cir->y*Cir->y))-(double)Cir->radius;
		
		//List加入头尾监视哨，方便插入与删除
		List.push_back(node_t(100.0,101.0));
		

        double dist;
		for(int i=1;i<n;i++){
			if ( procNext(Cir+i) ){
				dist = sqrt((double)((Cir+i)->x*(Cir+i)->x+(Cir+i)->y*(Cir+i)->y))-(double)(Cir+i)->radius;
				if ( ans < dist ) 
					ans = dist;
			}
		}

		printf("%.3lf\n",ans);
		
	}

	return 0;
}