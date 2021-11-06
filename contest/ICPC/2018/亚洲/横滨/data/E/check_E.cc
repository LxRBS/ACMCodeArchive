// This software is free for use by anyone for any purpose without restriction.
// The software is provided as is, with all faults, defects and errors,
// and without warranty of any kind, either expressed or implied.
//
// ./validator judge_in judge_ans feedback_dir [options] < team_out
//    ==> AC:42
//    ==> WA:43
//    ==> info to $feedback_dir/judgemessage.txt
//
#include <iostream>
#include <fstream>
#include <map>
#include <set>
#include <vector>
using namespace std;

enum ReturnTypeToEnsureDiffout { AC=42, WA=43 };
#define INTERNAL_ERROR(x) \
	(*g_diffout << "INTERNAL ERROR" << endl << x << endl, WA)
#define MALFORMED(x) \
	(*g_diffout << "MALFORMED OUTPUT" << endl << x << endl, WA)
#define WRONG_ANSWER(x) \
	(*g_diffout << "WRONG ANSWER" << endl << x << endl, WA)
#define OK() (AC)  // No stdout, in case of correct answer

ofstream* g_diffout = nullptr;

struct UnionFind
{
	vector<int> uf, sz;
	int nc;

	UnionFind(int N): uf(N), sz(N,1), nc(N)
		{ for(int i=0; i<N; ++i) uf[i] = i; }
	int size()
		{ return nc; }
	int size(int a)
		{ return sz[Find(a)]; }
	int Find(int a)
		{ return uf[a]==a ? a : uf[a]=Find(uf[a]); }
	bool Union(int a, int b)
		{
			a = Find(a);
			b = Find(b);
			if( a != b )
			{
				if( sz[a] >= sz[b] ) swap(a, b);
				uf[a] = b;
				sz[b] += sz[a];
				--nc;
			}
			return (a!=b);
		}
};

ReturnTypeToEnsureDiffout check(
	int V, const set<pair<int,int>>& E, // input data
	const set<pair<int,int>>& out)  // output data
{
	vector<int> d(V, 0);
	UnionFind uf(V);
	for(auto&& e: E) {
		d[e.first]++;
		d[e.second]++;
		uf.Union(e.first, e.second);
	}
	for(auto&& e: out) {
		d[e.first]++;
		d[e.second]++;
		uf.Union(e.first, e.second);
	}

	for(int v=0; v<V; ++v)
		if(d[v]%2 != 0)
			return WRONG_ANSWER("Non-even degree node: "<<v+1<<" d="<<d[v]);
	if(uf.size()!=1)
		return WRONG_ANSWER("Disconnected: (TODO:show sample)");
	return OK();
}

ReturnTypeToEnsureDiffout typed_main(int argc, const char* argv[])
{
	if(argc < 4) {
		cerr << "Insufficent number of arguments" << endl;
		return WA;
	}

	ofstream diffout(argv[3] + string("/judgemessage.txt"));
	if(!diffout) {
		cerr << "Cannot open diff.out" << endl;
		return WA;
	}
	g_diffout = &diffout;

	ifstream fin(argv[1]);
	ifstream fans(argv[2]);

	// input file
	int V=0, E=0; fin>>V>>E;
	set<pair<int,int>> Edges;
	for(int _=0; _<E; ++_) {
		int a,b; fin>>a>>b; --a,--b;
		Edges.emplace(a, b);
	}
	if(!fin)
		return INTERNAL_ERROR("Could not read the input: " << argv[1]);

	// answer file	
	bool is_possible_case; {
		int n; fans>>n;
		is_possible_case = (n!=-1);
	}
	if(!fans)
		return INTERNAL_ERROR("Could not read the correct-output: " << argv[2]);

	// output (submitted) file
	int n=-178116; cin>>n;
	if(!cin)
		return MALFORMED("Cannot read: n");
	if(n<-1)
		return MALFORMED("Invalid output: n=" << n);
	if(n==-1)
		return is_possible_case ? WRONG_ANSWER("possible case said impossible") : OK();

	set<pair<int,int>> out;
	for(int _=0; _<n; ++_) {
		int a,b; cin>>a>>b; --a, --b;
		if(!cin)
			return MALFORMED("Cannot read: index");
		if(a<0 || a>=V)
			return MALFORMED("Invalid output: a="<<a+1);
		if(b<0 || b>=V)
			return MALFORMED("Invalid output: b="<<b+1);
		if(a>=b)
			return MALFORMED("Invalid output: a,b="<<a+1<<","<<b+1);
		if(Edges.count(make_pair(a,b)))
			return MALFORMED("Already in input: a,b="<<a+1<<","<<b+1);
		if(out.count(make_pair(a,b)))
			return MALFORMED("Dupped output: a,b="<<a+1<<","<<b+1);
		out.emplace(a, b);
	}

	return check(V, Edges, out);
}

int main(int argc, const char* argv[])
{
	return int(typed_main(argc, argv));
}
