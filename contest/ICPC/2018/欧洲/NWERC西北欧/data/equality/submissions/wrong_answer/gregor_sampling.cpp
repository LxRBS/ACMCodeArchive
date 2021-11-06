#include <bits/stdc++.h>
using namespace std;
#define FORIT(i,c) for (__typeof__((c).begin()) i = (c).begin(); i != (c).end(); i++)
#define FOR(i,a,b) for (int i = (a); i < (b); i++)

int val[4][1000000];
int rrand(int i){ return rand() % i; }

struct tree{
	int type; // 0 = value, 1 = sort, 2 = shuffle, 3 = concat
	vector<int> v;
	tree *l,*r;
	int fi,la;
	void eval(int mode, int tar, bool noop){
		if (type == 0) {
			FOR(i,fi,la) val[tar][i] = v[i - fi];
		} else if (type == 1){
			l->eval(mode,tar,true);
			if (!noop) sort(val[tar]+fi,val[tar]+la);
		} else if (type == 2){
			l->eval(mode,tar,noop);
			if (!noop){
				// sample
				random_shuffle(val[tar]+fi, val[tar]+la, rrand);
				//sort(val[tar]+fi,val[tar]+la);
				if (mode == 1) reverse(val[tar]+fi,val[tar]+la);
			}
		} else {
			l->eval(mode,tar,noop);
			r->eval(mode,tar,noop);
		}
	}
};

tree* parse(int start){
	tree * t = new tree();
	t->fi = start;
	char c; cin >> c;
	if (c == '['){
		int cnum = 0;
		while (c != ']'){
			cin >> c;
			if ('0' <= c && c <= '9') cnum  = cnum * 10 + c-'0';
			else t->v.push_back(cnum),cnum = 0;
		}
		t->type = 0;
		t->la = t->fi + t->v.size();
	} else if (c == 's'){
		cin >> c;
		if (c == 'h') cin >> c, t->type = 2;
		else t->type = 1;
		FOR(i,0,5) cin >> c;
		t->l = parse(start);
		t->la = t->l->la;
		cin >> c;
	} else if (c == 'c'){
		FOR(i,0,6) cin >> c;
		t->l = parse(start);
		cin >> c;
		t->r = parse(t->l->la);
		cin >> c;
		t->la = t->r->la;
		t->type = 3;
	};
	return t;
}

int main(){
	tree * t1 = parse(0);
	tree * t2 = parse(0);

	if (t1->la != t2->la){
		cout << "not equal" << endl;
		return 0;
	}
	

	int seed = 8;
	srand(seed);
	t1->eval(0,0,false);
	t1->eval(1,2,false);
	srand(seed+1);
	t2->eval(0,1,false);
	t2->eval(1,3,false);

	//FOR(i,0,t1->la) cout << val[0][i] << " "; cout << endl;
	//FOR(i,0,t1->la) cout << val[1][i] << " "; cout << endl;
	//FOR(i,0,t1->la) cout << val[2][i] << " "; cout << endl;
	//FOR(i,0,t1->la) cout << val[3][i] << " "; cout << endl;


	FOR(i,0,t1->la) {
		if (val[0][i] != val[1][i] || val[2][i] != val[3][i]){
			cout << "not equal" << endl;
			return 0;
		}
	}
	cout << "equal" << endl;
	return 0;
}
