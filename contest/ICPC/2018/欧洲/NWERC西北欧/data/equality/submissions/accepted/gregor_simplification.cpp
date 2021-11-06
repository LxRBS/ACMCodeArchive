#include <bits/stdc++.h>
using namespace std;
#define FORIT(i,c) for (__typeof__((c).begin()) i = (c).begin(); i != (c).end(); i++)
#define FOR(i,a,b) for (int i = (a); i < (b); i++)

int val[4][1000000];

struct tree{
	int type; // 0 = value, 1 = sort, 2 = shuffle, 3 = concat
	vector<int> v;
	tree *l,*r;
	int fi,la;
	void allVal(vector<int> & vv){
		if (type == 0){
			FORIT(i,v) vv.push_back(*i);
		} else if (type == 1 || type == 2)
			l->allVal(vv);
		else {
			l->allVal(vv);
			r->allVal(vv);
		}
	}

	void extract(vector<tree*> & vv){
		if (type == 0) {}
		else if (type == 1){
			l->allVal(v);
			sort(v.begin(),v.end());
			type = 0;
		} else if (type == 2){
			l->allVal(v);
			sort(v.begin(),v.end());
			// check if identical
			int i = v[0];
			bool allid = v[0] == v[v.size()-1];
			if (allid) type = 0;
		} else {
			l->extract(vv);
			r->extract(vv);
			return; // don't add myself
		}
		
		vv.push_back(this);
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


tree* combine(tree* l, tree* r, vector<tree*> &vv){
	if (l->type == 0 && r->type == 0){
		// both are lists
		FORIT(i,r->v) l->v.push_back(*i);
		return l;
	}
	vv.push_back(l);
	return r;
}


int main(){
	tree * t1 = parse(0);
	tree * t2 = parse(0);

	if (t1->la != t2->la){
		cout << "not equal" << endl;
		return 0;
	}


	vector<tree*> expr1; t1->extract(expr1);
	vector<tree*> expr2; t2->extract(expr2);

	
	vector<tree*> res1;
	tree* t1c = expr1[0];
	FOR(i,1,expr1.size()) t1c = combine(t1c,expr1[i],res1);
	res1.push_back(t1c);
	
	vector<tree*> res2;
	tree* t2c = expr2[0];
	FOR(i,1,expr2.size()) t2c = combine(t2c,expr2[i],res2);
	res2.push_back(t2c);

	if (res1.size() != res2.size()){
		cout << "not equal" << endl;
		return 0;
	}

	FOR(i,0,res1.size()){
		if (res1[i]->type != res2[i]->type)	{
			cout << "not equal" << endl;
			return 0;
		}
		if (res1[i]->v.size() != res2[i]->v.size())	{
			cout << "not equal" << endl;
			return 0;
		}
		FOR(j,0,res1[i]->v.size())
			if (res1[i]->v[j] != res2[i]->v[j])	{
				cout << "not equal" << endl;
				return 0;
			}
	}


	
	cout << "equal" << endl;
	return 0;
}
