/**
 * ��͹�������С͹����Σ��ڶ���εı��ϵȸ���ѡ��һ����õ��Դ������С�����
 * ���������ȵ������Ƕ���
 * E = SIGMA{Pi * ��������}
 * ���ǵ�һ���߱��������϶��������������ģ����
 * E = SIGMA{�߳� * �߱������ĸ���}
 * ÿ���߱������ĸ��� = �ܹ������ߵĳ��� / �����ε��ܳ�
 * ���ֻ�����С�����ÿ��������ֱ�߽������ε���೤�ȼ���
 * ÿ�����ڴ����������������㣬���һ�Խ�����ҪO(N)
 * �Ժ��ÿ���ߵĽ����Ȼ�������仯�ģ����Ҳֻ��ҪO(N)
 * ���ȿ������󽻵������һ������ 
*/
#include <bits/stdc++.h>
using namespace std;

char *__abc147, *__xyz258, __ma369[100000];
#define __hv007() ((__abc147==__xyz258) && (__xyz258=(__abc147=__ma369)+fread(__ma369,1,100000-1,stdin),__abc147==__xyz258) ? EOF : *__abc147++)

int getInt(){
	int sgn = 1;
	char ch = __hv007();
	while( ch != '-' && ( ch < '0' || ch > '9' ) ) ch = __hv007();
	if ( '-' == ch ) {sgn = 0;ch=__hv007();}

	int ret = (int)(ch-'0');
	while( '0' <= (ch=__hv007()) && ch <= '9' ) ret = ret * 10 + (int)(ch-'0');
	return sgn ? ret : -ret;
}

#ifndef ONLINE_JUDGE
int const SIZE = 55;
#else
int const SIZE = 2E5+5;
#endif

typedef long double Real;
typedef tuple<Real, Real, Real> Line;

Real const INF = 1E9 + 1E8;
Real const EPS = 1E-12;
inline int sgn(Real x){return x>=EPS?1:(x<=-EPS?-1:0);}
inline bool is0(Real x){return 0 == sgn(x);}

struct Point{
    Real x, y;
	Point(Real a=0, Real b=0):x(a),y(b){}
};

const Point O(0, 0);

struct LineSeg{
	Point s, e;
	LineSeg(const Point&a, const Point&b):s(a),e(b){}
};

inline Real cross(const Point&O, const Point&A, const Point&B){
	Real xoa = A.x - O.x;
	Real yoa = A.y - O.y;
	Real xob = B.x - O.x;
	Real yob = B.y - O.y;
	return xoa * yob - xob * yoa;
}

inline Real dot(const Point&O, const Point&A, const Point&B){
	Real xoa = A.x - O.x;
	Real yoa = A.y - O.y;
	Real xob = B.x - O.x;
	Real yob = B.y - O.y;	
	return xoa * yoa + xob * yob;
}

inline Real dist(const Point&A, const Point&B){
	Real x = A.x - B.x, y = A.y - B.y;
	return sqrt(x*x+y*y);
}

/// �����ε����ģ���֤p[0] == p[n]
Point gravity(const Point p[], int n){
    vector<Point> vec;
	vec.reserve(n);
	Real a = 0;
	Point ans;
	for(int i=1;i<n-1;++i){
		Real tx = (p[0].x + p[i].x + p[i+1].x) / 3.0;
		Real ty = (p[0].y + p[i].y + p[i+1].y) / 3.0;
		Real w = cross(p[0], p[i], p[i+1]);
		a += w;
        ans.x += tx * w;
		ans.y += ty * w;
	}
	ans.x /= a; ans.y /= a;
	return ans;
}

/// �߶�AB���߶�CD�Ƿ��ཻ
inline bool isInter(const Point&A, const Point&B, const Point&C, const Point&D){
    if(min(A.x, B.x) > max(C.x, D.x)) return false;
	if(min(A.y, B.y) > max(C.y, D.y)) return false;
	if(min(C.x, D.x) > max(A.x, B.x)) return false;
	if(min(C.y, D.y) > max(A.y, B.y)) return false;
	if(sgn(cross(C, B, D) * cross(C, D, A)) < 0) return false;
	if(sgn(cross(A, C, B) * cross(A, B, D)) < 0) return false;
	return true;
}

/// ʵ���Ͼ�����ֱ��AB
inline Line cross(const Point&A, const Point&B){
    Real a = A.y - B.y;
	Real b = B.x - A.x;
	Real c = A.x * B.y - B.x * A.y;
	return {a, b, c};
}

inline Real eval(const Point&p, const Line&line){
	return p.x * get<0>(line) + p.y * get<1>(line) + get<2>(line);
}

/// p�Ƿ���ֱ��line��
inline bool isIn(const Point &p, const Line&line){
    Real t = eval(p, line);
	if(is0(t)) return true;
	return false;
}

/// �жϵ�A��B�Ƿ���ֱ�ߵ�ͬ�࣬AB��֤����ֱ����
inline bool isTong(const Point &A, const Point&B, const Line&line){
    Real ta = eval(A, line);
	Real tb = eval(B, line);
	int sa = sgn(ta), sb = sgn(tb);
	// assert(sa && sb); // �ϸ�ͬ�࣬��Ϊ����ֱ���ϵ��Ѿ����޳��ˣ������϶�����д�ǶԵģ�ֻ��AC��
	return sa * sb > 0;
}

/// ֱ��u��v�Ľ��㣬ȷ���н���
inline Point inter(const Line&u, const Line&v){
	Real ua = get<0>(u), ub = get<1>(u), uc = get<2>(u);
	Real va = get<0>(v), vb = get<1>(v), vc = get<2>(v);
    Real x = ub * vc - vb * uc;
	Real y = va * uc - ua * vc;
	Real t = ua * vb - va * ub;
	if(is0(x) && is0(y) && is0(t)){
		throw runtime_error("XXXXX");
	}
	assert(!is0(t));
	return {x/t, y/t};
}

int N, M;

Point P[SIZE], Q[SIZE];
Point GQ;

/// ֱ��Q[idx]Q[idx+1]������P�ཻ�Ľ����Լ��������ڵıߵ����
/// ���践����<A, B, i, j>
/// ��A��(i,i+1)�ϵĵ㣬��i+1�������߶�Q(idx,idx+1)
/// B��(j, j+1)�ϵĵ㣬��j�������߶�Q(idx,idx+1)
tuple<Point, Point, int, int> inter(int idx){
    /// �Ƚ�Q[idx]Q[idx+1]���һ��ֱ��
	Line line = cross(Q[idx], Q[idx+1]);
	vector<int> vec;
    /// �ж϶���εĶ���P�Ƿ�ǡ����ֱ����
	for(int i=0;i<N;++i){
		if(isIn(P[i], line)){
            vec.push_back(i);
		}
	}

    tuple<Point, Point, int, int> ans = {Point(), Point(), -1, -1};
	if(2 == vec.size()){ // ˵���������㶼�ҵ���	    
        /// Pi��ֱ���ϣ���P[i+1]��P[i-1]˭�������߶�Q(idx,idx+1)
		int i = vec.front();
		if(isTong(GQ, P[i+1], line)){ // ˵��P[i+1]�������߶�
		    assert(!isTong(GQ, P[i?i-1:N-1], line)); // ��Ȼ����һ��
            get<0>(ans) = P[i];
			get<2>(ans) = i;
		}else if(isTong(GQ, P[i?i-1:N-1], line)){ // ˵��i-1������
            get<1>(ans) = P[i];
            get<3>(ans) = i?i-1:N-1;
		}else{
			throw runtime_error("line171");
		}

		int j = vec.back();
		if(isTong(GQ, P[j+1], line)){ // ˵��P[i+1]������
            assert(!isTong(GQ, P[j?j-1:N-1], line)); // ��Ȼ����һ��
			assert(-1 == get<2>(ans)); // ��һ���𰸱�Ȼ������һ�ߵ�
			get<0>(ans) = P[j];
			get<2>(ans) = j;
		}else if(isTong(GQ, P[j?j-1:N-1], line)){
			assert(-1 == get<3>(ans));
			get<1>(ans) = P[j];
			get<3>(ans) = j?j-1:N-1;
		}else{
			throw runtime_error("185");
		}
		return ans;
	}

	if(1 == vec.size()){
        /// Pi��ֱ���ϣ���P[i+1]��P[i-1]˭�������߶�Q(idx,idx+1)
		int i = vec.front();
		if(isTong(GQ, P[i+1], line)){ // ˵��P[i+1]�������߶�
		    assert(!isTong(GQ, P[i?i-1:N-1], line)); // ��Ȼ����һ��
            get<0>(ans) = P[i];
			get<2>(ans) = i;
		}else if(isTong(GQ, P[i?i-1:N-1], line)){ // ˵��i-1������
            get<1>(ans) = P[i];
            get<3>(ans) = i?i-1:N-1;
		}else{
			throw runtime_error("line171");
		}
		/// ��ʣ�µ�һ�����㼴�ɣ����ĳ���߷־�ֱ�ߵ����༴��
		for(int i=0;i<N;++i){
            if(i == vec.front() || i + 1 == vec.front()) continue;
			if(isTong(P[i], P[i+1], line)) continue;
			/// ˵��Pi��P[i+1]�־����࣬�����������棬���󽻵�
			Point jiaodian = inter(line, cross(P[i], P[i+1]));
			/// ����֤һ��
			if(isTong(GQ, P[i], line)){ // ˵��P[i+1]�ǿ��ü���һ��
			    assert(-1 == get<3>(ans));
                get<3>(ans) = i;
				get<1>(ans) = jiaodian;
			}else if(isTong(GQ, P[i+1], line)){ // ˵��Pi���ü�
                assert(-1 == get<2>(ans));
				get<2>(ans) = i;
				get<0>(ans) = jiaodian;
			}else{
				throw runtime_error("211");
			}
			break;
		}		
		return ans;
	}

	/// ������������ж�
	for(int i=0;i<N;++i){
		if(isTong(P[i], P[i+1], line)) continue;
		/// ����һ������
		Point jiaodian = inter(line, cross(P[i], P[i+1]));
        if(isTong(GQ, P[i+1], line)){
			assert(-1 == get<2>(ans));
            get<0>(ans) = jiaodian;
			get<2>(ans) = i;
		}else if(isTong(GQ, P[i], line)){
			assert(-1 == get<3>(ans));
			get<1>(ans) = jiaodian;
			get<3>(ans) = i;
		}else{
			throw runtime_error("232");
		}
		if(-1 != get<2>(ans) && -1 != get<3>(ans)) break;
	}

    return ans;
}

/// ����Q[idx]Q[idx+1]������P�Ľ��㣬
/// ��Q[idx-1]Q[idx]����һ���߼���e��abuv��e��P�Ľ��㣬�ֱ��ʾ
/// e��P[u,u+1]��a����P[u+1]������,e��P[v,v+1]��b����P[v]������
/// �����һ���ɼ������Ǵ�b��v+1��u��a
/// light����һ���ɼ����ֵĳ���
void inter(int idx, Point&a, Point &b, int&u, int&v, Real&light){
    /// ����ȷ����ǰ�ߵ�ֱ�߷���
	Line line = cross(Q[idx], Q[idx+1]);
	/// �ƽ�u��Pu���ü��ߣ�P[u+1]������
	int t = 0;
	/// ���Ƚ�ua�ľ����ȥ
	light -= dist(P[u], a);
	while(1){
		/// ���ȼ��P[u+1]�Ƿ�����ֱ����
		if(isIn(P[(u+1)%N], line)){ // ����u+1��u+2
		    light += dist(P[u], P[(u+1)%N]);
            u = (u + 1)%N; a = P[u];			
			break;
		}
		/// ���u,u+1�Ƿ���������
		if(!isTong(P[u], GQ, line) && isTong(P[(u+1)%N], GQ, line)){
            // u = u;
			a = inter(line, cross(P[u], P[(u+1)%N])); 
			light += dist(P[u], a);
			break;
		}
		light += dist(P[u], P[(u+1)%N]);
		u = (u+1) % N;		
		++t;
		if(t > N){
			throw runtime_error("269");
		}
	}
    light += dist(P[v], b);
	t = 0;
	while(1){ // �ƽ�v
        /// ���ȼ��v+1�Ƿ�����ֱ����
		if(isIn(P[(v+1)%N], line)){ // ����v��v+1
            // v = v;			
			b = P[(v+1)%N];
			light -= dist(P[v], b);
			break;
		}
		/// ���v/v+1
		if(isTong(P[v], GQ, line) && !isTong(P[(v+1)%N], GQ, line)){
			// v = v;
			b = inter(line, cross(P[v], P[(v+1)%N]));
			light -= dist(P[v], b);
			break;
		}
		light -= dist(P[v], P[(v+1)%N]);
		v = (v+1) % N;
		++t;
		if(t > N){
			throw runtime_error("290");
		}
	}
	return;
}

Real proc(){
	P[N] = P[0]; Q[M] = Q[0];
	GQ = gravity(Q, M);
    auto t4t = inter(0);
	Point a = get<0>(t4t), b = get<1>(t4t);
	int u = get<2>(t4t), v = get<3>(t4t);

	/// ����P���ܳ�
	Real total = 0;
    for(int i=0;i<N;++i){
		total += dist(P[i], P[i+1]);
	}

	/// b����v+1��u��a�ǿɼ����֣��󳤶�
	Real cur = dist(b, P[(v+1)%N]);
	for(int i=(v+1)%N;i!=u%N;(i+=1)%=N){
		cur += dist(P[i], P[(i+1)%N]);
	}
	cur += dist(P[u], a);
	
	Real ans = cur / total * dist(Q[0], Q[1]);
	for(int i=1;i<M;++i){		
		/// ������һ��t4t
		inter(i, a, b, u, v, cur);
		ans += cur / total * dist(Q[i], Q[i+1]);
	}
    return ans;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif        
    N = getInt(); M = getInt();
	for(int i=0;i<N;++i) P[i].x = getInt(), P[i].y = getInt();
	for(int i=0;i<M;++i) Q[i].x = getInt(), Q[i].y = getInt();
	cout<<fixed<<setprecision(12)<<proc()<<endl;
    return 0;
}
