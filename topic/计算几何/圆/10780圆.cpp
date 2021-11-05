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

//a��b��֤��0��2PI
bool check(double a,double b){
	list<node_t>::iterator it;

	//����Ѱ�ҵ�a������Ѵ�������Σ���itָ��
	for(it=List.begin();it!=List.end();it++){
        if ( isLT(a,it->start) ) break;
	}   

	//a�п�������it֮ǰ���Ǹ����䣬��fit��ʾ
	//ע�⣬list�ĵ�����û�����ؼӼ�����ֻ��ʹ�üӼӡ���������
	list<node_t>::iterator fit = it;
	fit--;

	//keepit����ָʾ�����λ�ã������Ҫ����Ļ�
	list<node_t>::iterator keepit;
	
	double a_k;

	//һ��Ҫ��EPS���й�ϵ�жϣ�����ֱ��ʹ��<=֮��
	if ( isLT(a,fit->end) || isEqual(a,fit->end) ){
		//ab��������������
		if ( isLT(b,fit->end) || isEqual(b,fit->end) )
            return false;

		//���a����fit�ڣ������λ�û���fit֮ǰ
		keepit = fit;
		keepit--;
		a_k = fit->start;
	}else{
		//���aû������fit�ڣ������λ�þ���fit
		keepit = fit;
		a_k = a;
		fit = it;
	}

	//ȷ��b����ʲôλ��
	while( isGT(b,it->start) || isEqual(b,it->start) ) it++;
	it--;

	double b_k;
	if ( isGT(b,it->end) ) b_k = b;
	else               b_k = it->end;

	it++;

	//ȷ�����µ������[a_k,b_k]֮�󣬽��йص������ȫ��ɾ��
	//�������Ҫɾ��Ҳû�й�ϵ��fit��it֮��Ĺ�ϵ��Ȼ�ͻ�ʹ��eraseʧȥ����
    List.erase(fit,it);

	//ע�ⲻ����keepit���룬��������֮�����
	//��Ϊlist��ɾ����ʹ�ú�����������ʧЧ�����������Ҫά�����һ��û�б仯�ĵ������������keepit��Ȼ�����������в������
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

	//a/b���ӽǷ�Χ��a��b֮��һ����PI����
	double a = theta - beta;
	double b = theta + beta;

	//aС��0��������μ���
	if ( isLT(a,0.0) ){
		flag = check(0.0,b);
		flag = check(a+2.0*PI,2.0*PI) || flag;
		return flag ;
	}

	//b����2PI��Ҳ�����μ���
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

		//�������Բ���룬��������Բ�ľ���
		//���Բһ���ǿ��Կ�����
		proc1st(Cir[0]);
		ans = sqrt((double)(Cir->x*Cir->x+Cir->y*Cir->y))-(double)Cir->radius;
		
		//List����ͷβ�����ڣ����������ɾ��
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