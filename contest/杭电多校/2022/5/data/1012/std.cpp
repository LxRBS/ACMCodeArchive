#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int N= 2e5 + 5;
struct Data { int arrival, spent; }data[N];
struct Timeline {
	ll time; int type, id;
	Timeline(ll _time = 0, int _type = 0, int _id = 0) :
		time(_time), type(_type), id(_id) {}
	// type = 0 for departure, type = 1 for arrival
	bool operator < (const Timeline &t) const {
		if(time != t.time) return time > t.time;
		return type > t.type;
	}
};
priority_queue<Timeline> Tl;
struct Queue {
	int num, id;
	Queue(int _num = 0, int _id = 0) :
		num(_num), id(_id) {}
	bool operator < (const Queue &t) const {
		if(num == t.num) return id < t.id;
		return num < t.num;
	}
}q[N];
set<Queue> Que;
int T, n, m, Queue_select[N];
ll ans, Last[N];
int main() {
	// freopen("test.in", "r", stdin);
	// freopen("test.out", "w", stdout);
	scanf("%d", &T);
	while(T--) {
		scanf("%d%d", &n, &m);
		for(int i = 1; i <= n; ++i)
			scanf("%d%d", &data[i].arrival, &data[i].spent);
		for(int i = 1; i <= n; ++i)
			Tl.push(Timeline(data[i].arrival, 1, i));
		Que.clear();
		for(int i = 1; i <= m; ++i) {
			q[i].num = 0, q[i].id = i;
			Que.insert(q[i]);
			Last[i] = 0;
		}
		while(!Tl.empty()) {
			auto tl = Tl.top(); Tl.pop();
			ll time = tl.time; int type = tl.type, id = tl.id;
			if(type == 0) {
				int qid = Queue_select[id];
				Que.erase(Queue(q[qid].num, q[qid].id));
				Que.insert(Queue(--q[qid].num, q[qid].id));
			}
			else {
				auto que = *Que.begin();
				int num = que.num, qid = que.id;
				Que.erase(que);
				Queue_select[id] = qid;
				if(num == 0) Last[qid] = time + data[id].spent;
				else Last[qid] += data[id].spent;
				q[qid].num++; que.num++;
				Que.insert(que);
				Tl.push(Timeline(Last[qid], 0, id));
			}
		}
		ans = 0;
		for(int i = 1; i <= m; ++i) ans = max(ans, Last[i]);
		printf("%lld\n", ans);
	}
	
	return 0;
}
