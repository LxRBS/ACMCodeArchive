#include <bits/stdc++.h>
using namespace std;
#define FORIT(i,c) for (__typeof__((c).begin()) i = (c).begin(); i != (c).end(); i++)
#define FOR(i,a,b) for (int i = (a); i < (b); i++)

struct tree{
	int type; // 0 = value, 1 = sort, 2 = shuffle, 3 = concat
	vector<int> v;
	tree *l,*r;
	vector<int> eval(int mode){
		if (type == 0) return v;
		if (type == 1){
			v = l->eval(mode);
			sort(v.begin(),v.end());
			return v;
		}
		if (type == 2){
			v = l->eval(mode);
			sort(v.begin(),v.end());
			if (mode == 1) reverse(v.begin(),v.end());
			return v;
		}
		v = l->eval(mode);
		vector<int> v2 = r->eval(mode);
		FORIT(i,v2) v.push_back(*i);
		return v;
	}
};


tree* parse(){
	tree * t = new tree();
	char c; cin >> c;
	if (c == '['){
		int cnum = 0;
		while (c != ']'){
			cin >> c;
			if ('0' <= c && c <= '9') cnum  = cnum * 10 + c-'0';
			else t->v.push_back(cnum),cnum = 0;
		}
		t->type = 0;
	} else if (c == 's'){
		cin >> c;
		if (c == 'h') cin >> c, t->type = 2;
		else t->type = 1;
		FOR(i,0,5) cin >> c;
		t->l = parse();
		cin >> c;
	} else if (c == 'c'){
		FOR(i,0,6) cin >> c;
		t->l = parse();
		cin >> c;
		t->r = parse();
		cin >> c;
		t->type = 3;
	};
	return t;
}

int main(){
	tree * t1 = parse();
	tree * t2 = parse();

	vector<int> v1 = t1->eval(0);
	vector<int> w1 = t2->eval(0);
	vector<int> v2 = t1->eval(1);
	vector<int> w2 = t2->eval(1);
	if (v1.size() != w1.size()){
		cout << "not equal" << endl;
		return 0;
	}

	FOR(i,0,v1.size()) {
		if (v1[i] != w1[i] || v2[i] != w2[i]){
			cout << "not equal" << endl;
			return 0;
		}
	}
	cout << "equal" << endl;
	return 0;
}
