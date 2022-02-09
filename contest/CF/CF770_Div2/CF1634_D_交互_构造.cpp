/**
 * 交互式问题
 * 给定数组A，已知长度为N，但是Ai未知，只知道其中有且只有一个0，其余全是整数
 * 可以进行一种操作：? i j k，其中ijk互异
 * 返回max(Ai,Aj,Ak) - min(Ai,Aj,Ak)
 * 要求操作不超过2N-2次，最后输出i,j，满足Ai==0或者Aj==0
 * 考虑任意4个元素，进行4次操作：?abc, ?abd, ?acd, ?bcd
 * 假设a是最大值，b是最小值，则有前两次操作返回的值最大且相等
 * 返回来，如果知道哪两次操作返回最大值，就知道哪两个数是这4个数中的最大和最小。
 * 把这两个数留下来，以待下一轮。另外两个数直接扔掉
 * 因此每轮扔掉两个数，一共要扔掉N-2个数，因此总操作数量是2(N-2)
 * 再考虑N如果不是4的倍数，剩下的数也要4次操作，所以总数量不会超过2N-2
*/
#include <bits/stdc++.h>
using namespace std;

typedef long long llt;

#ifndef ONLINE_JUDGE
int const SIZE = 11;
#else
int const SIZE = 1000055;
#endif

int N;
vector<int> V[2];
typedef pair<int, int> pii;

pii proc(int a, int b, int c, int d){
	printf("? %d %d %d\n", a, b, c);
	fflush(stdout);
	int ans1;
	scanf("%d", &ans1);

	printf("? %d %d %d\n", a, b, d);
	fflush(stdout);
	int ans2;
	scanf("%d", &ans2);

	printf("? %d %d %d\n", a, c, d);
	fflush(stdout);
	int ans3;
	scanf("%d", &ans3);	

	printf("? %d %d %d\n", b, c, d);
	fflush(stdout);
	int ans4;
	scanf("%d", &ans4);

	const int r = max(max(ans1, ans2), max(ans3, ans4));

	if(r == ans1 && ans1 == ans2) return {a, b};
	if(r == ans1 && ans1 == ans3) return {a, c};
	if(r == ans1 && ans1 == ans4) return {b, c};
	if(r == ans2 && ans2 == ans3) return {a, d};
	if(r == ans2 && ans2 == ans4) return {b, d};
	assert(r == ans3 && ans3 == ans4);
	return {c, d};	 
}

bool proc(int idx){
	int oidx = idx ^ 1;

	const vector<int> & vec = V[idx];

	if(vec.size() == 3){
		throw runtime_error("XXX3");
	}

    if(vec.size() == 2){
		printf("! %d %d\n", vec[0], vec[1]);
		fflush(stdout);
		return true;
	}

	vector<int> & buick = V[oidx];
	buick.clear();

	if(vec.size() == 5){
		pii t1 = proc(vec[0], vec[1], vec[2], vec[3]);
		pii t2;
		if(vec[0]!=t1.first&&vec[0]!=t1.second){
			t2 = proc(vec[4], t1.first, t1.second, vec[0]);
		}else if(vec[1]!=t1.first&&vec[1]!=t1.second){
			t2 = proc(vec[4], t1.first, t1.second, vec[1]);
		}else if(vec[2]!=t1.first&&vec[2]!=t1.second){
            t2 = proc(vec[4], t1.first, t1.second, vec[2]);
		}else{
			throw runtime_error("YYY");
		}
		printf("! %d %d\n", t2.first, t2.second);
		fflush(stdout);
		return true;
	}

	int len = vec.size();
	int t = len / 4;
	int n = t * 4;

	for(int i=0;i<n;i+=4){
		pii tmp = proc(vec[i], vec[i+1], vec[i+2], vec[i+3]);
		buick.push_back(tmp.first);
		buick.push_back(tmp.second);
	}
	for(int i=n;i<len;++i) buick.push_back(vec[i]);
	return false;
}

void proc(){
	V[0].clear();
	V[1].clear();

	if(5 == N){
		pii t1 = proc(1, 2, 3, 4);
		pii t2;
		if(1!=t1.first&&1!=t1.second){
			t2 = proc(5, t1.first, t1.second, 1);
		}else if(2!=t1.first&&2!=t1.second){
			t2 = proc(5, t1.first, t1.second, 2);
		}else if(3!=t1.first&&3!=t1.second){
            t2 = proc(5, t1.first, t1.second, 3);
		}else{
			throw runtime_error("ZZZ");
		}
		
		printf("! %d %d\n", t2.first, t2.second);
		fflush(stdout);
		return;		
	}

    int t = N / 4;
	int n = t * 4;
	for(int i=1;i<=n;i+=4){
		pii tmp = proc(i, i+1, i+2, i+3);
		V[0].push_back(tmp.first);
		V[0].push_back(tmp.second);
	}
	for(int i=n+1;i<=N;++i) V[0].push_back(i);

    int cur = 0;
	while(1){
        if(proc(cur)) break;
		cur ^= 1;
	}
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif    
    int nofkase;
	scanf("%d", &nofkase);
    while(nofkase--){
        scanf("%d", &N);
		proc();
    }
    return 0;
}
