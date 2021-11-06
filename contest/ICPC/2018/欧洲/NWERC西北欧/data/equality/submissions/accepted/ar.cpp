// Author Alexander Rass
#include <bits/stdc++.h>
using namespace std;

typedef long long dt;
const dt MAXNUM = 999999999;

struct Expression{virtual void linearize(vector<dt> &values) = 0;};
struct Concat: public Expression{
    Expression *a, *b;
    Concat(Expression* a, Expression* b):a(a),b(b){}
    void linearize(vector<dt> & values){
        a->linearize(values);
        b->linearize(values);
    }
};
dt num_rand = 0;
struct RandExp: public Expression{
    Expression* a;
    RandExp(Expression* a):a(a){}
    void linearize(vector<dt> & values){
        int S1 = values.size();
        a->linearize(values);
        int S2 = values.size();
        sort(values.begin() + S1, values.end());
        if(S1 != S2 && values[S1] != values[S2-1]){
            num_rand++;
            for(int i = S1; i < S2; i++)values[i] += num_rand * (MAXNUM + 1); // TODO check whether this suits well
        }
    }
};
struct SortExp: public Expression{
    Expression* a;
    SortExp(Expression* a):a(a){}
    void linearize(vector<dt> & values){
        int S1 = values.size();
        a->linearize(values);
        int S2 = values.size();
        sort(values.begin() + S1, values.end());
    }
};
struct Base: public Expression{
    vector<dt> data;
    void linearize(vector<dt> & values){
        for(auto it: data)values.push_back(it);
    }
};

Expression* parse(string & in, int & pos, bool already_ordered){
    if(in[pos] == 's' && in[pos+1] == 'o'){ // sorted
        pos += string("sorted(").size();
        Expression* res = parse(in, pos, true);
        assert(in[pos] == ')');
        ++pos;
        if(already_ordered)return res;
        return new SortExp(res);
    } else if(in[pos] == 's' && in[pos+1] == 'h'){ // shuffle
        pos += string("shuffle(").size();
        Expression* res = parse(in, pos, true);
        if(in[pos] != ')')cout << "pos=" << pos << " [" << in[pos] << "]" << endl;
        assert(in[pos] == ')');
        ++pos;
        if(already_ordered)return res;
        return new RandExp(res);
    } else if(in[pos] == 'c'){// concat
        pos += string("concat(").size();
        Expression* res1 = parse(in, pos, already_ordered);
        assert(in[pos] == ',');
        ++pos;
        Expression* res2 = parse(in, pos, already_ordered);
        assert(in[pos] == ')');
        ++pos;
        return new Concat(res1,res2);
    } else if(in[pos] == '['){// bare array
        Base* res = new Base();
        res->data.clear();
        while(in[pos] != ']'){
            int cpos = ++pos;
            while(in[pos] != ',' && in[pos] != ']')++pos;
            istringstream is(in.substr(cpos, pos - cpos));
            dt tmp;
            is >> tmp;
            res->data.push_back(tmp);
        }
        pos++;
        return res;
    } else {
        assert(false);
        return NULL;
    }
    assert(false);
    return NULL;
}

int main(){
    string p1, p2;
    cin >> p1 >> p2;
    int pos = 0;
    Expression* e1 = parse(p1,pos,false);
    pos = 0;
    Expression* e2 = parse(p2,pos,false);
    vector<dt> data1, data2;
    num_rand = 0;
    e1->linearize(data1);
    num_rand = 0;
    e2->linearize(data2);
    if(data1 == data2){
        cout << "equal" << endl;
    } else {
        cout << "not equal" << endl;
    }
	return 0;
}
