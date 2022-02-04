/**
 * 给N个字符串的数组A，再给一个目标串T，所有字符串长度均为M
 * 问T能否由Ai中的片段拼接而成，片段长度大于等于2，需要输出任意可行方案，没有方案输出-1
 * 任意足够长的字符串都能够切成仅有2、3长度的片段，因此无需去寻找更长的片段
 * 首先预处理出所有存在的2-片段与3-片段
 * 然后对T做一个DP并记录方案即可 
*/
#include <bits/stdc++.h>
using namespace std;

#ifndef ONLINE_JUDGE
int const SIZE = 15;
#else
int const SIZE = 1010;
#endif

typedef tuple<int, int, int> t3t;

int N, M;
char A[SIZE][SIZE];
char S[SIZE];

t3t Two[100] = {{0, 0, 0}};
t3t Thr[1000] = {{0, 0, 0}};

void f(int idx){
	const char * a = A[idx];
    for(int t,i=0;i<M-1;++i){
		t = (a[i] - '0') * 10 + a[i+1] - '0';
		if(0 == get<0>(Two[t])){
			Two[t] = {idx, i, i+1};
		}
	}
	for(int t,i=0;i<M-2;++i){
		t = (a[i]-'0')*100 + (a[i+1]-'0')*10 + a[i+2]-'0';
		if(0 == get<0>(Thr[t])){
			Thr[t] = {idx, i, i+2};
		}
	}
}

void proc(){
	if(1 == M) return (void)puts("-1");

	t3t d[1010] = {{0, 0, 0}};
	int pre[1010] = {0};
	int t = (S[0]-'0')*10 + S[1]-'0';
	if(get<0>(Two[t])){
		d[1] = Two[t];
		pre[1] = -1;
	}
	if(2 == M){
		if(get<0>(d[1])){
			printf("1\n1 2 %d\n", get<0>(d[1]));
		}else{
			puts("-1");
		}
		return;
	}

	t = (S[0]-'0')*100 + (S[1]-'0')*10 + S[2]-'0';
    if(get<0>(Thr[t])){
		d[2] = Thr[t];
		pre[2] = -1;
	}
	for(int i=3;i<M;++i){
        t = (S[i-1]-'0')*10 + S[i]-'0';
		if(get<0>(d[i-2]) && get<0>(Two[t])){
            pre[i] = i - 2;
			d[i] = Two[t];
			continue;
		}
	    t += (S[i-2]-'0') * 100;
		if(get<0>(d[i-3]) && get<0>(Thr[t])){
			pre[i] = i - 3;
			d[i] = Thr[t];
		}
	}

	if(0 == get<0>(d[M-1])) return (void)puts("-1");

	vector<t3t> ans;
	t = M - 1;
	while(t != -1){
		ans.push_back(d[t]);
		t = pre[t];
	}
	printf("%d\n", (int)ans.size());
	for(auto it=ans.rbegin(),eit=ans.rend();it!=eit;++it){
		printf("%d %d %d\n", 1+get<1>(*it), 1+get<2>(*it), get<0>(*it));
	}
	return;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif  
    int nofkase;
	scanf("%d", &nofkase);
	while(nofkase--){
		memset(Two, 0, sizeof(Two));
		memset(Thr, 0, sizeof(Thr));

		scanf("%d%d", &N, &M);	
		for(int i=1;i<=N;++i){
			scanf("%s", A[i]);
			f(i);
		}
		scanf("%s", S);
		proc();
	}
    return 0;
}
