// This software is free for use by anyone for any purpose without restriction.
// The software is provided as is, with all faults, defects and errors,
// and without warranty of any kind, either expressed or implied.
//
// ./validator judge_in judge_ans feedback_dir [options] < team_out
//    ==> AC:42
//    ==> WA:43
//    ==> info to feedback_dir/diff.out
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

ReturnTypeToEnsureDiffout check(
	const vector<pair<int,int> >& es, // input data
	const vector<int>& colors)  // output data
{
	for(auto e: es) {
		if(colors[e.first] == colors[e.second])
			return WRONG_ANSWER("Same color: {"<<e.first+1<<","<<e.second+1<<"}");
	}
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
	int n, m;
	fin >> n >> m;
	for(int _=0; _<n; ++_) {
		int x, y;
		fin >> x >> y;
	}
	vector<pair<int,int> > es;
	for(int _=0; _<m; ++_) {
		int a,b; fin>>a>>b; --a,--b;
		es.push_back(make_pair(a, b));
	}
	if(!fin)
		return INTERNAL_ERROR("Could not read the input: " << argv[1]);

	// output (submitted) file
	vector<int> colors;
	for (int _=0; _<n; ++_) {
		int c;
		cin >> c;
		colors.push_back(c);
		if(!cin)
			return MALFORMED("Cannot read: index");
		if(c<=0 || c>4)
			return MALFORMED("Invalid output: c="<<c);
	}
//	if(!cin.eof())
//		return MALFORMED("Too many lines");
	return check(es, colors);
}

int main(int argc, const char* argv[])
{
	return int(typed_main(argc, argv));
}
