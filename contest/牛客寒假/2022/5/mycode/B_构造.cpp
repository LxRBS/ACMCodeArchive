/**
 * 乒乓球满分为11分，但如过负者达到10分，则必须净胜2分才可。
 * 现在打了若干局，给定了双方的总得分
 * 要求还原每一局的比分。局数无限制，但要求每一局的必分合法
 * 如果无解输出NO，否则输出每一局的必分。
 * 发现分数比较大时(大于等于21)，a==b, a==b+1, a==b+2均是有解的
 * 于是将a比b多的部分都拆成11:0，这样只要处理a、b差小于10的情况
 * 再把a和b拆成相差1或者2的情况，例如假设a、b相差7，则拆成4部分
 * 变为：b1+2vsb1, b2+2vsb2, b3+2vsb3, b4+1vsb4
 * 然后每一部分都是有解的。
 * 最多拆成5个部分，每一部分都要大于等于21，因此就是100多。
 * 100以下用深搜即可。
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


typedef long long llt;
typedef pair<llt, llt> pll;
typedef vector<pll> vpll;

int const PRESIZE = 120;
vpll Pre[PRESIZE][PRESIZE];
int Flag[PRESIZE][PRESIZE];

bool dfs(int x, int y, vpll&ans){
	ans.clear();

	if(-1 != Flag[x][y]){
        ans.assign(Pre[x][y].begin(), Pre[x][y].end());
		return Flag[x][y];
	}

    bool ret = false;
	vpll &vec = Pre[x][y];
    if(x < y){
		ret = dfs(y, x, ans);
		vec.assign(ans.begin(), ans.end());
		for(auto &p: vec)swap(p.first, p.second);
		ans.assign(vec.begin(), vec.end());
	}else{		
		for(int i=0;i<=9&&i<=y;++i){
			vpll tmp;
			vec.push_back({11, i});
			bool b = dfs(x-11, y-i, tmp);
			if(b){
				ret = true;
				vec.insert(vec.end(), tmp.begin(), tmp.end());
				goto L;
			}
			vec.pop_back();
		}
		for(int i=10;i<=y;++i){
			if(x<i+2) break;
			vpll tmp;
			vec.push_back({i+2, i});
			bool b = dfs(x-i-2, y-i, tmp);
			if(b){
				ret = true;
				vec.insert(vec.end(), tmp.begin(), tmp.end());
				goto L;
			}
			vec.pop_back();			
		}
	}
L:
	assert(ret || (!ret && vec.empty()));
    return Flag[x][y] = (ret ? 1 : 0);
}

void init(){
	memset(Flag, -1, sizeof(Flag));
	for(int x=0;x<=10;++x)for(int y=0;y<=10;++y)Flag[x][y]=Flag[y][x]=0;
    Flag[0][0] = 1;
	for(int x=11;x<PRESIZE;++x)for(int y=0;y<=x;++y){
		vpll tmp;
		dfs(x, y, tmp);
	}   
	return;
}

bool check(llt x, llt y){
	if(x < y) swap(x, y);
    if(y >= 10) return x == y + 2;
	return 11 == x;
}
bool check(const vpll &ans, llt x, llt y){
	for(auto p: ans){
		if(!check(p.first, p.second)) return false;
		x -= p.first; y -= p.second;
	}
	return x == 0 && 0 == y;
}

bool proc0(llt n, vpll &ans){
	assert(n >= 21);
	ans.push_back({11, 9});
	ans.push_back({n-11, n-9});
	return true;
}

bool proc1(llt n, vpll &ans){
	assert(n>=21);
	ans.push_back({11, 8});
	ans.push_back({n-10, n-8});
	return true;
}

bool proc2(llt n, vpll &ans){
	assert(n >= 10);
	ans.push_back({n+2, n});
	return true;
}

bool proc(llt cha, llt x, llt y, vpll &ans){
	if(cha < 0){
		bool b = proc(-cha, y, x, ans);
		if(!b) return false;
		for(auto &p: ans) swap(p.first, p.second);
		return true;
	}

	assert(cha < 11);
	if(0 == cha) return proc0(y, ans);
	
	int t2 = cha / 2;
	int t1 = cha & 1;
    int tt = t2 + t1;
	llt yy = y / tt;
	llt lefty = y - yy * (tt - 1);
    vpll problem;
	if(t1){
		problem.push_back({lefty+1, lefty});
		for(int i=0;i<t2;++i)problem.push_back({yy+2, yy});
	}else{
		problem.push_back({lefty+2, lefty});
		for(int i=1;i<t2;++i)problem.push_back({yy+2, yy});
	}
#ifndef ONLINE_JUDGE
    llt a1 = 0, a2 = 0;
	for(auto p: problem) a1+=p.first, a2+=p.second;
	if(a1!=x || a2!=y){
		throw runtime_error("a1 a2: " + [=]()->string{
			stringstream ss;
			ss<<x<<" "<<y;
			return ss.str();
		}());		
	}
#endif
    for(auto p: problem){
		vpll tmp;
		if(p.first - p.second == 1){
            proc1(p.second, tmp);
			ans.insert(ans.end(), tmp.begin(), tmp.end());
		}else if(p.first - p.second == 2){
            proc2(p.second, tmp); 
			ans.insert(ans.end(), tmp.begin(), tmp.end());
		}else{
			throw runtime_error("XXX == 3");
		}
	}
	return true;
}

bool proc(llt x, llt y, vpll &ans){
	if(x < y){
		bool b = proc(y, x, ans);
		if(!b) return false;
		for(auto &p: ans) swap(p.first, p.second);
		return true;
	}

	if(x < PRESIZE){
		bool b = dfs(x, y, ans);
		if(!b) return false;
		return true;
	}
	if(y < PRESIZE){
		llt k = (x - PRESIZE) / 11;
		if((x-PRESIZE) % 11) ++k;
		llt tx = x - k * 11;
		if(tx < 0){
			throw runtime_error("tx should gt 0: " + [=]()->string{
				stringstream ss;
				ss<<x<<" "<<y;
				return ss.str();
			}());
		}
        bool b = proc(tx, y, ans);
		if(!b) return false;
		for(int i=0;i<k;++i) ans.push_back({11, 0});
		return true;
	}

	llt t = (x-y) / 11;
	llt tx = x - 11 * t;
	llt cha = tx - y;
	bool b = proc(cha, tx, y, ans);
	if(!b) return false;
	for(int i=0;i<t;++i) ans.push_back({11, 0});
#ifndef ONLINE_JUDGE
    if(!check(ans, x, y)){
        throw runtime_error("wrong: " + [=]()->string{
				stringstream ss;
				ss<<x<<" "<<y;
				return ss.str();
		}());
	}
#endif
	return true;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif    
    init();
#ifndef ONLINE_JUDGE
    // for(int i=0;i<PRESIZE;++i){
	// 	for(int j=0;j<=i;++j){
	// 		if(0==Flag[i][j]) cout<<i<<" "<<j<<endl;
	// 	}
	// }
#endif

    int nofkase = getInt();
    while(nofkase--){
        llt x = getInt();
        llt y = getInt();
        vpll ans;
		bool b = proc(x, y, ans);
		if(!b){
			printf("NO\n"); continue;
		}
		printf("YES\n%d\n", ans.size());
		for(auto p: ans)printf("%lld %lld\n", p.first, p.second);
    }
    return 0;
}