#include <iostream>
#include <string>
#include <queue>
#include <map>
#include <fstream>
using namespace std;

typedef long long int llt;

//换算关系如果只使用int会超范围
struct _t{
	llt a;
	llt b;
};

llt gcd(llt a,llt b){
	llt r = a % b;
	while(r){
		a = b;
		b = r;
		r = a % b;
	}
	return b;
}

_t A[8][8];//货币的换算关系
map<string,int> Map;//货币到整数的映射
string Name[8];//货币的名字
bool Flag[8][8];

//根据t1,t2汇率计算t3
void fun(_t const&t1,_t const&t2,_t&t3){
	llt g = gcd(t1.b,t2.a);
    t3.a = t2.a / g * t1.a;
	t3.b = t1.b / g * t2.b;

	g = gcd(t3.a,t3.b);
	t3.a /= g;
	t3.b /= g;
}

//建立目标所有的换算关系
void bfs(int x,int size){
    queue<int> q;
	for(int i=0;i<size;++i)if(Flag[x][i]) q.push(i);

	while( !q.empty() ){
		int t = q.front();
		q.pop();

		for(int i=0;i<size;++i){
			if ( !Flag[t][i] || Flag[x][i] || x == i ) continue;
            fun(A[x][t],A[t][i],A[x][i]);
			Flag[x][i] = true;
			q.push(i);
		}
	}
	return;
}

int main(){
	int n,kase=0;
	while( cin>>n && n ){
		memset(Flag,0,sizeof(Flag));
		Map.clear();

		for(int i=0;i<n;++i){
			_t t;
			char ch;
			string sa,sb;
			cin>>t.a>>sa>>ch>>t.b>>sb;

			int ia,ib;
			map<string,int>::iterator it;
			
			it = Map.find(sa);
            if ( Map.end() == it ) Map.insert(it,make_pair(sa,ia=Map.size()));
			else ia = Map[sa];
			
			it = Map.find(sb);
			if ( Map.end() == it ) Map.insert(it,make_pair(sb,ib=Map.size()));
			else ib = Map[sb];
			
			Name[ia] = sa;
			Name[ib] = sb;

			A[ia][ib].a = A[ib][ia].b = t.a;
			A[ia][ib].b = A[ib][ia].a = t.b;
			Flag[ia][ib] = Flag[ib][ia] = true;
		}

		int quest;string s;
		cin>>quest>>s;

        bfs(Map[s],Map.size());

        int qi = Map[s];
		int account = 100000000;
		int idx;
		double eps = 1E20;
		for(unsigned i=0;i<Map.size();++i){
			if ( !Flag[qi][i] || qi == i ) continue;

			llt tt = A[qi][i].b * quest;
			llt x = tt / A[qi][i].a;
           
			if ( x > 100000 ) continue;

			if ( 0 == tt % A[qi][i].a ){
                if ( eps > 0.0 || x < account ) 
                    account = x, idx = i, eps = 0.0;
				continue;
			}

			//不整除则计算余额
			++x;
			if ( x > 100000 ) continue;

			double dt = (double)(A[qi][i].a * x - A[qi][i].b * quest);
			dt /= (double)A[qi][i].b;

			if ( eps > dt ) eps = dt, idx = i, account = x;
		}

		++kase;
		cout<<"Case "<<kase<<": "<<account<<' '<<Name[idx]<<endl;
	}
	return 0;
}