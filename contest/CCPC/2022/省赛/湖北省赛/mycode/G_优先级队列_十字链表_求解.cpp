/**
 * 给定一堵墙，每一格的高度为hi，用1乘2的砖头在原有基础上继续砌墙
 * 可以横着放，也可以竖着放，问：将所有格弄成一样高度，这个一样的高度最小是多少
 * 如果无法实现，则输出-1。
 * 首先判解的存在性，如果是1 2 1 2或者1 2 3 4这种高度肯定不行
 * 但是2 1 1 2或者9 6 2 9是可以的。
 * 所以关键在于相邻格的奇偶性，如果奇偶性相同，这两格可以一起砌，相当于不会再影响其他格，所以将之删除
 * 于是有了新的相邻格，再进行判断
 * 如果有三个连续格奇偶性均相同，则将前二格结合删除即可，实际上不影响结论
 * 所以反复判断，如果能够通过这种方式将格子删光或者删到只剩一格，就是有解。
 * 再考虑求解，将所有格子塞入优先级队列，
 * 每一次取出最低点，如果它和邻居一样高，则他们以后就可以一起砌，于是将这二者从队列中删除并且记录当前高度
 * 如果它比邻居矮，如果相差是偶数，显然要用砖砌到一样高，并且此时可以将二者删除并记录当前高度
 * 如果相差是奇数，显然要砌到邻居加一，并且将这一格重新塞回队列
 * 可以想象，如此操作不会改变最终答案。但是如果墙高度相差过大，会T，例如
 * 2 1 999999999 1000000000
 * 因为入队次数与差值有关。可以事先将所有高度补到距离最高有一定余量的位置
 * 经测余量为500可ac
 * 还有一种方案是每次对最低点去检查他的邻居，然后向邻居补齐，不知道是否能够保证答案正确
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

char getChar(){
	char ch = __hv007();
	while(!isalpha(ch)) ch = __hv007();
	return ch;
}

#ifndef ONLINE_JUDGE
int const SIZE = 110;
#else
int const SIZE = 2E5+10;
#endif

using llt = long long;
using pii = pair<int, llt>;

int N;
pii A[SIZE];
int Left[SIZE], Right[SIZE];
bool Flag[SIZE] = {false};


llt proc(){
	if(1 == N) return A[1].second;

	for(int i=1;i<=N;++i) Left[i] = i - 1, Right[i] = i + 1;
	Right[N] = 0;
	int head = 1;
	
	using coor = pair<int, int>;
	queue<coor> q;

	for(int i=2;i<=N;){
		if(0 == (A[i-1].second - A[i].second) % 2){
			q.push({i-1, i}); 
			Flag[i-1] = Flag[i] = true;
			i += 2;			
		}else{
			++i;
		}
	}
    
	if(q.empty()) return -1;

	int cnt = N;
	while(1){
        int sz = q.size();
		while(sz--){
			int u = q.front().first, v = q.front().second;
			q.pop();
			cnt -= 2;

			/// uv可以成对删掉，并且Left[u]和Right[v]变为邻居
			Right[Left[u]] = Right[v];
			Left[Right[v]] = Left[u];
			if(u == head) head = Right[v];
			if(Left[u] && Right[v] && !Flag[Left[u]] && !Flag[Right[v]] && 0 == (A[Left[u]].second - A[Right[v]].second) % 2){
                q.push({Left[u], Right[v]});
				Flag[Left[u]] = Flag[Right[v]] = true;
			}			
			// 这一步其实可以不必要
			Left[u] = Left[v] = Right[u] = Right[v] = 0; 
		}

		if(q.empty()){
			if(cnt > 1) return -1;
            goto L;
		}
	}
L:  ;;
	/// 以上判了解的存在性，以下求解
	/// 首先将高度都补到一个接近的位置，但显然不能补到只差1所以要留有一定的余量
	/// 本题现有数据留200还会wa，500能够ac
	llt mm = 0;
	llt yuliang = 500;
	for(int i=1;i<=N;++i) mm = max(mm, A[i].second);
	for(int i=1;i<=N;++i){
		llt cha = mm - A[i].second;
		if(cha & 1) A[i].second = max(A[i].second, mm - 1 - yuliang);
		else A[i].second = max(A[i].second, mm - yuliang);
	}

	for(int i=1;i<=N;++i) Left[i] = i - 1, Right[i] = i + 1;
	Right[N] = 0;

    /// 优先级队列，把A扔进去
	using f_t = function<bool(const pii&a, const pii&b)>;
    priority_queue<pii, vector<pii>, f_t> pq(A+1, A+N+1, [](const pii&a, const pii&b){
        if(a.second != b.second) return a.second > b.second;
		return a.first > b.first;
	});

    llt ans = 0;
	while(!pq.empty()){
		auto h = pq.top(); pq.pop();
		ans = h.second;

		if(pq.empty()) break;
	
	    auto b = pq.top();
		llt cha = b.second - h.second;
		if(Right[h.first] == b.first && 0 == cha % 2){
			pq.pop();
			ans = b.second;
			Right[Left[h.first]] = Right[b.first];
            Left[Right[b.first]] = Left[h.first];			
			continue;
		}

        llt tmp = 1234567891234LL;
		if(Left[h.first]) tmp = min(tmp, A[Left[h.first]].second);
		if(Right[h.first]) tmp = min(tmp, A[Right[h.first]].second);
		if(0 == (tmp - h.second) % 2) h.second = tmp;
		else h.second = tmp + 1;
		A[h.first].second = h.second;
		pq.push(h);
	}

	return ans;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    N = getInt();
	for(int i=1;i<=N;++i) A[A[i].first=i].second = getInt();
    cout << proc() << endl;
    return 0;
}