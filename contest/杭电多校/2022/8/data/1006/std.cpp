//1006, std
#include<bits/stdc++.h>
using namespace std;
const char* name[4] = {"Alice", "Bob", "Carol", "David"};
struct Player {
	pair<int, int> pos[4];
	int score, state[4], lst, cnt, fail;
	inline void Init() {
		memset(state, 0, sizeof state);
		score = 0;
		memset(pos, 0, sizeof pos);
		lst = -1, cnt = 0, fail = 0;
	}
	inline void Calc(int x) {
		if(lst == -1)
			lst = x, cnt = 1;
		else {
			if(lst != x)
				score += (6 - lst) * (cnt - 1) * (cnt - 1), lst = x, cnt = 1;
			else
				++ cnt;
		}
	}
}player[4];
int col[55], in[4], id[4], beg[4], fly[4];
pair<int, int> cell[55], lines[4][10]; // (type, cnt)

uint32_t x, y, z, w;
inline uint32_t Xor128(void) {
	uint32_t t;

	t = x ^ (x << 11);
	x = y; y = z; z = w;
	return w = w ^ (w >> 19) ^ (t ^ (t >> 8));
}
inline int GetDice() {
	return Xor128() % 6 + 1;
}

inline int Win(int p) {
	for(int i = 0; i < 4; ++ i)
		if(player[p].state[i] != 2)
			return 0;
	return 1;
}
inline void Crash(int p1, int p2, int x, int y, int pos1, int pos2) {
// cout << "Crash Happened!" << endl;
// cout << "player " << name[p1] << "'s " << x << " planes from " << pos1 << " crashes player " << name[p2] << "'s " << y << " planes at " << pos2 << endl;
	int tmp = min(x, y);
	player[p1].score += 5 * tmp;
	for(int i = 0, j = 0; i < 4 && j < tmp; ++ i)
		if(player[p2].pos[i].first == 0 && player[p2].pos[i].second == pos2)
			player[p2].pos[i] = make_pair(0, 0), player[p2].state[i] = 0, ++ j;
	if(y > tmp)
		cell[pos2] = make_pair(p2, y - tmp);
	else
		cell[pos2] = make_pair(0, 0);
	tmp = min(x, y - 1);
	player[p2].score += 2 * tmp;
	for(int i = 0, j = 0; i < 4 && j < tmp; ++ i)
		if(player[p1].pos[i].first == 0 && player[p1].pos[i].second == pos1)
			player[p1].pos[i] = make_pair(0, 0), player[p1].state[i] = 0, ++ j;
	if(pos1 != -1)
		cell[pos1] = make_pair(0, 0);
	if(x > tmp) {
		cell[pos2] = make_pair(p1, x - tmp);
		for(int i = 0, j = 0; i < 4 && j < x - tmp; ++ i)
			if(player[p1].pos[i].first == 0 && player[p1].pos[i].second == pos1)
				player[p1].pos[i] = make_pair(0, pos2), ++ j;
	}
}
inline pair<int, int> GetNext(int type, pair<int, int> pos, int d) {
	if(pos.first) {
		if(pos.second + d > 6)
			return make_pair(1, 6 - (pos.second + d - 6));
		else
			return make_pair(1, pos.second + d);
	}
	else {
		if(pos.second == -1) {
			int nxt = beg[type] + d - 1;
			if(nxt == fly[type]) {
				nxt += 16;
				if(nxt > 52)
					nxt -= 52;
			}
			else if(type == col[nxt]) {
				nxt += 4;
				if(nxt > 52)
					nxt -= 52;
				if(nxt == fly[type]) {
					nxt += 12;
					if(nxt > 52)
						nxt -= 52;
				}
			}
			return nxt == in[type] ? make_pair(1, 0) : make_pair(0, nxt);
		}
		if(pos.second < in[type] && pos.second + d >= in[type])
			return make_pair(1, pos.second + d - in[type]);
		else {
			int nxt = pos.second + d;
			if(nxt > 52)
				nxt -= 52;
			if(nxt == fly[type]) {
				nxt += 16;
				if(nxt > 52)
					nxt -= 52;
			}
			else if(type == col[nxt]) {
				nxt += 4;
				if(nxt > 52)
					nxt -= 52;
				if(nxt == fly[type]) {
					nxt += 12;
					if(nxt > 52)
						nxt -= 52;
				}
			}
			return nxt == in[type] ? make_pair(1, 0) : make_pair(0, nxt);
		}
	}
}
inline int GetDisToEnd(int type, pair<int, int> pos) {
	if(pos.first)
		return 6 - pos.second;
	int d = in[type] - pos.second;
	if(pos.second == -1)
		d = in[type] - beg[type] + 1;
	if(d < 0)
		d += 52;
	return d + 6;
}
inline int GetDis(int type, pair<int, int> s, pair<int, int> t) {
	if(s.first == 0 && t.first == 0) {
		int d = t.second - s.second;
		if(s.second == -1)
			d = t.second - beg[type] + 1;
		if(d < 0)
			d += 52;
		return d;
	}
	else if(s.first == 0 && t.first == 1) {
		int d = in[type] - s.second;
		if(d < 0)
			d += 52;
		return d + t.second;
	}
	else if(s.first == 1 && t.first == 1) {
		return t.second - s.second;
	}
	else
		assert(0);
}
inline int Move(int p, int d) {
// cout << "Move (" << name[p] << ", " << d << ")" << endl;
	int now = -10, mv = -1;
	if(p == 0) { // Alice
		for(int i = 0; i < 4; ++ i) {
			if(player[p].state[i] == 0 || player[p].state[i] == 2)
				continue;
			pair<int, int> nxt = GetNext(p, player[p].pos[i], d);
			int tmp = 0;
			if(player[p].pos[i].first)
				tmp = lines[p][player[p].pos[i].second].second;
			else if(player[p].pos[i].second >= 1)
				tmp = cell[player[p].pos[i].second].second;
			else
				tmp = 1;
			if(nxt.first)
				tmp += lines[p][nxt.second].second;
			else if(cell[nxt.second].first == p)
				tmp += cell[nxt.second].second;
			if(tmp > now)
				now = tmp, mv = i;
			else if(tmp == now) {
				if(mv == -1 || GetDisToEnd(p, player[p].pos[i]) < GetDisToEnd(p, player[p].pos[mv]))
					mv = i;
			}
		}
	}
	else if(p == 1) { // Bob
		for(int i = 0; i < 4; ++ i) {
			if(player[p].state[i] == 0 || player[p].state[i] == 2)
				continue;
			pair<int, int> nxt = GetNext(p, player[p].pos[i], d);
			int tmp = 0, c = player[p].pos[i].first == 0 ? player[p].pos[i].second >= 1 ? cell[player[p].pos[i].second].second : 0 : lines[p][player[p].pos[i].second].second;
			if(nxt.first == 0 && cell[nxt.second].second && cell[nxt.second].first != p)
				tmp = min(c, cell[nxt.second].second);
			if(tmp > now)
				now = tmp, mv = i;
			else if(tmp == now) {
				if(mv == -1 || GetDisToEnd(p, player[p].pos[i]) < GetDisToEnd(p, player[p].pos[mv]))
					mv = i;
			}
		}
	}
	else if(p == 2) { // Carol
		for(int i = 0; i < 4; ++ i) {
			if(player[p].state[i] == 0 || player[p].state[i] == 2)
				continue;
			pair<int, int> nxt = GetNext(p, player[p].pos[i], d);
			int tmp = GetDis(p, player[p].pos[i], nxt);
			if(tmp > now)
				now = tmp, mv = i;
			else if(tmp == now) {
				if(mv == -1 || GetDisToEnd(p, player[p].pos[i]) < GetDisToEnd(p, player[p].pos[mv]))
					mv = i;
			}
		}
	}
	else if(p == 3) { // David
		for(int i = 0; i < 4; ++ i) {
			if(player[p].state[i] == 0 || player[p].state[i] == 2)
				continue;
			int tmp = GetDisToEnd(p, player[p].pos[i]);
			if(tmp > now)
				now = tmp, mv = i;
		}
	}
	else
		assert(0);
	if(mv == -1)
		return 0;
// cout << "Move the planes on (" << player[p].pos[mv].first << ", " << player[p].pos[mv].second << ")" << endl;
	pair<int, int> nxt = GetNext(p, player[p].pos[mv], d);
// cout << "End at (" << nxt.first << ", " << nxt.second << ")" << endl;
	if(player[p].pos[mv].second == -1) {
		assert(nxt.first == 0);
		if(cell[nxt.second].second && cell[nxt.second].first != p)
			Crash(p, cell[nxt.second].first, 1, cell[nxt.second].second, -1, nxt.second);
		else {
			player[p].pos[mv] = make_pair(0, nxt.second);
			cell[nxt.second].first = p;
			++ cell[nxt.second].second;
		}
	}
	else {
		int c = player[p].pos[mv].first == 0 ? cell[player[p].pos[mv].second].second : lines[p][player[p].pos[mv].second].second;
		if(nxt.first == 1 && nxt.second == 6) {
			int tmp = 0;
			for(int i = 0; i < 4; ++ i) {
				if(p == i)
					continue;
				for(int j = 0; j < 4; ++ j)
					if(player[i].state[j] != 2)
						++ tmp;
			}
			player[p].score += 5 * tmp * c;
			assert(player[p].pos[mv].first == 1);
			lines[p][player[p].pos[mv].second].second -= c;
			pair<int, int> pre = player[p].pos[mv];
			for(int i = 0; i < 4; ++ i)
				if(player[p].pos[i] == pre)
					player[p].state[i] = 2, player[p].pos[i] = make_pair(0, 0);
		}
		else {
			if(player[p].pos[mv].first == 1) {
				assert(nxt.first == 1);
				lines[p][player[p].pos[mv].second].second -= c;
				lines[p][nxt.second].second += c;
				pair<int, int> pre = player[p].pos[mv];
				for(int i = 0; i < 4; ++ i)
					if(player[p].pos[i] == pre)
						player[p].pos[i] = nxt;
			}
			else {
				if(nxt.first == 1) {
					cell[player[p].pos[mv].second] = make_pair(0, 0);
					lines[p][nxt.second].second += c;
					pair<int, int> pre = player[p].pos[mv];
					for(int i = 0; i < 4; ++ i)
						if(player[p].pos[i] == pre)
							player[p].pos[i] = nxt;
				}
				else {
					if(cell[nxt.second].second && cell[nxt.second].first != p)
						Crash(p, cell[nxt.second].first, c, cell[nxt.second].second, player[p].pos[mv].second, nxt.second);
					else {
						cell[player[p].pos[mv].second] = make_pair(0, 0);
						cell[nxt.second].first = p;
						cell[nxt.second].second += c;
						pair<int, int> pre = player[p].pos[mv];
						for(int i = 0; i < 4; ++ i)
							if(player[p].pos[i] == pre)
								player[p].pos[i] = nxt;
					}
				}
			}
		}
	}
	return 1;
}
inline void Operate(int p) {
// cout << "Operate " << name[p] << ": " << endl;
	int d = GetDice();
	while(d == 6) {
// cout << "Roll " << d << endl;
		player[p].Calc(d);
		int flag = -1;
		for(int i = 0; i < 4; ++ i)
			if(player[p].state[i] == 0) {
				flag = i;
				break;
			}
		if(flag != -1)
			player[p].state[flag] = 1, player[p].pos[flag] = make_pair(0, -1), player[p].fail = 0;
		else {
			if(!Move(p, d)) {
				++ player[p].fail;
				if(player[p].fail == 10) {
					int flag = -1;
					for(int i = 0; i < 4; ++ i)
						if(player[p].state[i] == 0) {
							flag = i;
							break;
						}
					assert(flag != -1);
					if(flag != -1)
						player[p].state[flag] = 1, player[p].pos[flag] = make_pair(0, -1);
					player[p].fail = 0;
				}
			}
		}
		if(Win(p))
			return;
		d = GetDice();
	}
// cout << "Roll " << d << endl;
	player[p].Calc(d);
	if(!Move(p, d)) {
		++ player[p].fail;
		if(player[p].fail == 10) {
// cout << name[p] << " " << "Failed" << endl;
			int flag = -1;
			for(int i = 0; i < 4; ++ i)
				if(player[p].state[i] == 0) {
					flag = i;
					break;
				}
			assert(flag != -1);
			if(flag != -1)
				player[p].state[flag] = 1, player[p].pos[flag] = make_pair(0, -1);
			player[p].fail = 0;
		}
	}
	else
		player[p].fail = 0;
	if(Win(p))
		return;
}
inline int Cmp(int a, int b) {
	return player[a].score == player[b].score ? a < b : player[a].score > player[b].score;
}
inline void Print(int p) {
	for(int i = 0; i < 4; ++ i)
		player[i].Calc(-1);
	player[p].score += 50;
	printf("%s win!\n", name[p]);
	for(int i = 0; i < 4; ++ i)
		id[i] = i;
	sort(id, id + 4, Cmp);
	for(int i = 0; i < 4; ++ i)
		printf("%s: %d\n", name[id[i]], player[id[i]].score);
}
int T, C;
int main() {
	for(scanf("%d", &T); T --; ) {
		// printf("Case #%d:\n", ++ C);
		scanf("%u%u%u%u", &x, &y, &z, &w);
		for(int i = 1; i <= 52; ++ i)
			col[i] = (i + 2) % 4;
		for(int i = 0; i < 4; ++ i)
			player[i].Init();
		memset(cell, 0, sizeof cell);
		memset(lines, 0, sizeof lines);
		beg[0] = 1, beg[1] = 14, beg[2] = 27, beg[3] = 40;
		fly[0] = 18, fly[1] = 31, fly[2] = 44, fly[3] = 5;
		in[0] = 50, in[1] = 11, in[2] = 24, in[3] = 37;
		int flag = 1;
		while(flag) {
			for(int i = 0; i < 4; ++ i) {
				Operate(i);
// for(int k = 0; k < 4; ++ k) {
// cout << name[k] << "'s score = " << player[k].score << endl;
// cout << "States of " << name[k] << "'s planes: ";
// for(int j = 0; j < 4; ++ j)
// 	cout << player[k].state[j] << " ";
// cout << endl;
// cout << "Position: ";
// for(int j = 0; j < 4; ++ j)
// 	cout << "(" << player[k].pos[j].first << ", " << player[k].pos[j].second << ")" << " ";
// cout << endl << endl;}
				if(Win(i)) {
					Print(i);
					// return 0;
					flag = 0;
					break;
				}
			}
		}
	}
}