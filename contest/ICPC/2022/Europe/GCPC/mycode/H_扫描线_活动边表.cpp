/**
 * 给了一个简单多边形（有可能是凹的），多边形的边一定是横平竖直的
 * 给定多边形内壁上的某一个点，从该点出发向多边形内射出一条光线，射出方向一定是正负45度之一
 * 光线依次在多边形内壁反射M次，求这M次的反射点坐标
 * 保证反射点坐标一定是整数，保证光线不会射到多边形的端点上
 * N和M在5E5，因此需要NlogN算法
 * 注意到多边形的特殊性，如果将多边形旋转45度，则光线变为了横平竖直，
 * 可以使用扫描线活动边表算法预处理出所有可能的点对，然后直接读取数据即可
 * 两个方向均需要扫描，以Y方向为例
 * 首先预处理每一条边，对每条边记录{ymin, ymax, ymin时的x, delta}
 * Y_XX[ymin]记录了所有ymin相同的边，称作预处理边表
 * 然后再将所有Y_XX[ymin]按x排序，x相同则按delta排序
 * 活动边表记作aet，初始为最小的y的边表，for y : y的最小值到最大值
 *    对每一个y更新aet
 *    对每一个到达了ymax的边，将其从边表删除
 *    如果当前y存在预处理边表，则将预处理边表合并进aet
 *    由于预处理边表和aet始终有序，因此合并操作是线性的
 *    根据当前aet记录点对
 * 由于使用了stl进行删除操作，因此不需要使用链表，直接使用vector则可
 * 使用链表实现删除操作可能会更快
 * 扫描完以后就记录了所有可能的点对，从起点开始依次读取数据即可
 */
#include <bits/stdc++.h>
using namespace std;

char *__abc147, *__xyz258, __ma369[100000];
#define __hv007() ((__abc147==__xyz258) && (__xyz258=(__abc147=__ma369)+fread(__ma369,1,100000,stdin),__abc147==__xyz258) ? EOF : *__abc147++)

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
int const SIZE = 14;
#else
int const SIZE = 2E5+12;
#endif



using llt = int;
using pii = pair<llt, llt>;
using vpii = vector<pii>;
using si = set<int>;
using mmsi = map<int, map<int, si>>;

struct edge_t{
    pii mm; // 扫描线坐标的最小值和最大值
    llt another; // 另外一个坐标，这个值会随着扫描线坐标的变化而变化 
	llt delta; // 变化率，本题必然是正负一之一
};

using ve = vector<edge_t>;
// using le = list<edge_t>;
using le = ve;

llt const INF = 2000000000;
int N, M;
vpii Origin;
vpii After;

map<llt, ve> YLine, XLine;
pii XMM, YMM;

mmsi X_YY, Y_XX;

/// 本题不可能存在水平边，只计算低点
void init(const pii & a, const pii & b){
	llt xmin = min(a.first, b.first);
	llt ymin = min(a.second, b.second);
	llt xmax = max(a.first, b.first);
	llt ymax = max(a.second, b.second);

	XMM.first = min(XMM.first, xmin);
	XMM.second = max(XMM.second, xmax);

	YMM.first = min(YMM.first, ymin);
	YMM.second = max(YMM.second, ymax);

    llt k = (b.second - a.second) / (b.first - a.first);
    YLine[ymin].push_back({{ymin, ymax}, ymin==a.second?a.first:b.first, k});
    XLine[xmin].push_back({{xmin, xmax}, xmin==a.first?a.second:b.second, k});
}

void init(){
	YMM = XMM = {INF, -INF};
	XLine.clear(); YLine.clear();
	for(int i=0;i<N;++i){
		init(After[i], After[(i+1)%N]);
	}
	for(auto & p : XLine){
        sort(p.second.begin(), p.second.end(), [](const edge_t & a, const edge_t & b){
			if(a.another != b.another) return a.another < b.another;
			return a.delta < b.delta;
		});
	}
	for(auto & p : YLine){
        sort(p.second.begin(), p.second.end(), [](const edge_t & a, const edge_t & b){
			if(a.another != b.another) return a.another < b.another;
			return a.delta < b.delta;
		});
	}
}

void disp(){
	printf("xrange = {%d, %d}, yrange = {%d, %d}\n", XMM.first, XMM.second, YMM.first, YMM.second);
	printf("Y scan line: \n");
	for(const auto & p : YLine){
        printf("y = %d: \n", p.first);
		for(const auto & e : p.second){
			printf(" {{%d, %d}, %d, %d}", e.mm.first, e.mm.second, e.another, e.delta);
		}
		printf("\n");
	}
	printf("X scan line: \n");
	for(const auto & p : XLine){
        printf("x = %d:\n", p.first);
		for(const auto & e : p.second){
			printf(" {{%d, %d}, %d, %d}", e.mm.first, e.mm.second, e.another, e.delta);
		}
		printf("\n");
	}
}

void dispRecord(){
	printf("X_YY\n");
	for(const auto & p : X_YY){
		printf("x = %d:", p.first);
		for(const auto & pp : p.second){
			// assert(pp.second.size() == 1);
			for(int i : pp.second) printf(" (%d, %d)", pp.first, i);
		}
		printf("\n");
	}
	printf("Y_XX\n");
	for(const auto & p : Y_XX){
		printf("y = %d:", p.first);
		for(const auto & pp : p.second){
			// assert(pp.second.size() == 1);
			for(int i : pp.second) printf(" (%d, %d)", pp.first, i);
		}
		printf("\n");
	}
}

/// m记录了边表，range表示扫描线范围，ans记录答案
void proc(const map<llt, ve> & m, const pii & range, mmsi & ans){
    /// 准备活动边表，第一个活动边表与最小的边表一致
	auto it = m.begin();
	le aet(it->second.begin(), it->second.end());
	auto anchor = it->first;
	assert(anchor == range.first);

	while(1){
        ++it;
		auto cur_taget = it != m.end() ? it->first : range.second;
        /// 从anchor到cur_taget
		do{
			/// 变化边表
			++anchor;
			for(auto & e : aet){
				e.another += e.delta;
			} 
			/// 删除边表
			aet.erase(remove_if(aet.begin(), aet.end(), [anchor](const edge_t & e){
                return e.mm.second == anchor;
			}), aet.end());

            /// 合并边表 
			if(anchor == cur_taget){
				const ve & vtmp = it != m.end() ? it->second : ve();
				le tmp;
                merge(aet.begin(), aet.end(), vtmp.begin(), vtmp.end(), back_inserter(tmp), [](const edge_t & a, const edge_t & b){
                    if(a.another != b.another) return a.another < b.another;
					return a.delta < b.delta;
				});
				aet.swap(tmp);
			}
            
            /// 记录答案
			assert(aet.size() % 2 == 0);
			for(auto i=aet.begin(),e=aet.end();i!=e;++i){
				llt x1 = i->another;
				++i;
				llt x2 = i->another;
				ans[anchor][x1].insert(x2);
				ans[anchor][x2].insert(x1);
			}
		}while(anchor <= cur_taget);

		if(it == m.end()) break;
	}
	return;
}

void proc(pii & p, int & k){
	// printf("(%d %d %d)\n", p.first, p.second, k);
    if(k == 0){ // shuzhi
        const auto & m = X_YY;
		auto anchor = p.first;
		auto another = p.second;
        auto it = m.find(anchor);
		assert(it != m.end());
        auto jt = it->second.find(another);
		assert(jt != it->second.end());
		assert(jt->second.size() == 1);
		auto last = *jt->second.begin();
		p.second = last;
		k ^= 1;
		return;
	}

	const auto & m = Y_XX;
	auto anchor = p.second;
	auto another = p.first;
	auto it = m.find(anchor);
	assert(it != m.end());
	auto jt = it->second.find(another);
	assert(jt != it->second.end());
	assert(jt->second.size() == 1);
	auto last = *jt->second.begin();
	p.first = last;
	k ^= 1;
	return;	
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    Origin.assign(N = getInt(), {0, 0});
    M = getInt();
	for(auto & p : Origin) p.first = getInt(), p.second = getInt();
    After.reserve(N);
	for(const auto & p : Origin) After.emplace_back(p.first - p.second, p.first + p.second);

    init();
	// for(auto & p : After){
	// 	printf("(%d, %d)", p.first, p.second);
	// }
	// printf("\n");
	// disp();
   
	proc(YLine, YMM, Y_XX);
	proc(XLine, XMM, X_YY);
	// dispRecord();

    pii cur;
	cur.first = getInt(); 
	cur.second = getInt();
	pii zhen = {cur.first - cur.second, cur.first + cur.second};
	int k = 0; // 初始方向向上
	vpii ans;
	for(int i=1;i<=M;++i){
        proc(zhen, k);
		ans.push_back(zhen);
	}

	for(auto & p : ans){
		printf("%d %d\n", (p.first + p.second) / 2, (p.second - p.first) / 2);
	}
    return 0;
}