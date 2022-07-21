/**
 * ����һ��ǽ��ÿһ��ĸ߶�Ϊhi����1��2��שͷ��ԭ�л����ϼ�����ǽ
 * ���Ժ��ŷţ�Ҳ�������ŷţ��ʣ������и�Ū��һ���߶ȣ����һ���ĸ߶���С�Ƕ���
 * ����޷�ʵ�֣������-1��
 * �����н�Ĵ����ԣ������1 2 1 2����1 2 3 4���ָ߶ȿ϶�����
 * ����2 1 1 2����9 6 2 9�ǿ��Եġ�
 * ���Թؼ��������ڸ����ż�ԣ������ż����ͬ�����������һ�������൱�ڲ�����Ӱ�����������Խ�֮ɾ��
 * ���������µ����ڸ��ٽ����ж�
 * �����������������ż�Ծ���ͬ����ǰ������ɾ�����ɣ�ʵ���ϲ�Ӱ�����
 * ���Է����жϣ�����ܹ�ͨ�����ַ�ʽ������ɾ�����ɾ��ֻʣһ�񣬾����н⡣
 * �ٿ�����⣬�����и����������ȼ����У�
 * ÿһ��ȡ����͵㣬��������ھ�һ���ߣ��������Ժ�Ϳ���һ���������ǽ�����ߴӶ�����ɾ�����Ҽ�¼��ǰ�߶�
 * ��������ھӰ�����������ż������ȻҪ��ש����һ���ߣ����Ҵ�ʱ���Խ�����ɾ������¼��ǰ�߶�
 * ����������������ȻҪ�����ھӼ�һ�����ҽ���һ���������ض���
 * ����������˲�������ı����մ𰸡��������ǽ�߶������󣬻�T������
 * 2 1 999999999 1000000000
 * ��Ϊ��Ӵ������ֵ�йء��������Ƚ����и߶Ȳ������������һ��������λ��
 * ��������Ϊ500��ac
 * ����һ�ַ�����ÿ�ζ���͵�ȥ��������ھӣ�Ȼ�����ھӲ��룬��֪���Ƿ��ܹ���֤����ȷ
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

			/// uv���Գɶ�ɾ��������Left[u]��Right[v]��Ϊ�ھ�
			Right[Left[u]] = Right[v];
			Left[Right[v]] = Left[u];
			if(u == head) head = Right[v];
			if(Left[u] && Right[v] && !Flag[Left[u]] && !Flag[Right[v]] && 0 == (A[Left[u]].second - A[Right[v]].second) % 2){
                q.push({Left[u], Right[v]});
				Flag[Left[u]] = Flag[Right[v]] = true;
			}			
			// ��һ����ʵ���Բ���Ҫ
			Left[u] = Left[v] = Right[u] = Right[v] = 0; 
		}

		if(q.empty()){
			if(cnt > 1) return -1;
            goto L;
		}
	}
L:  ;;
	/// �������˽�Ĵ����ԣ��������
	/// ���Ƚ��߶ȶ�����һ���ӽ���λ�ã�����Ȼ���ܲ���ֻ��1����Ҫ����һ��������
	/// ��������������200����wa��500�ܹ�ac
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

    /// ���ȼ����У���A�ӽ�ȥ
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