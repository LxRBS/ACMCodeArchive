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
#include <bitset>
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

const int MAX_N = 10000;

class SCC {
    public:
    SCC(int n) : size(n), graph(n), num_scc(0), mapping(n) {};
    void add_edge(int from, int to);
    void decompose();
    int get_size();
    vector <vector <int> > get_graph();
    vector <int> get_mapping();
    
    private:
    vector <vector <int> > graph;
    int size;
    int num_scc;
    vector <int> mapping;
};

void SCC::add_edge(int from, int to) {
    graph[from].push_back(to);
}

void SCC::decompose() {
    int num_visit = 0, num_stack = 0, num_dfs = 0;
    int *order = (int *)malloc(sizeof(int) * size);
    int *low = (int *)malloc(sizeof(int) * size);
    bool *in = (bool *)malloc(sizeof(bool) * size);
    int *stack = (int *)malloc(sizeof(int) * size);
    int *dfs_v = (int *)malloc(sizeof(int) * size);
    int *dfs_index = (int *)malloc(sizeof(int) * size);
    
    for (int i = 0; i < size; i++) {
        order[i] = -1;
        in[i] = false;
    }
    for (int i = 0; i < size; i++) {
        if (order[i] != -1) continue;
        dfs_v[num_dfs] = i;
        dfs_index[num_dfs++] = -1;
        while (num_dfs > 0) {
            int v = dfs_v[--num_dfs];
            int index = dfs_index[num_dfs];
            if (index == -1) {
                order[v] = low[v] = num_visit++;
                stack[num_stack++] = v;
                in[v] = true;
            } else {
                low[v] = min(low[v], low[graph[v][index]]);
            }
            for (index++; index < graph[v].size(); index++) {
                int w = graph[v][index];
                if (order[w] == -1) {
                    dfs_v[num_dfs] = v;
                    dfs_index[num_dfs++] = index;
                    dfs_v[num_dfs] = w;
                    dfs_index[num_dfs++] = -1;
                    break;
                } else if (in[w] == true) {
                    low[v] = min(low[v], order[w]);
                }
            }
            if (index == graph[v].size() && low[v] == order[v]) {
                while (true) {
                    int w = stack[--num_stack];
                    in[w] = false;
                    mapping[w] = num_scc;
                    if (v == w) break;
                }
                num_scc++;
            }
        }
    }
    
    free(order);
    free(low);
    free(in);
    free(stack);
    free(dfs_v);
    free(dfs_index);
}

int SCC::get_size() {
    return num_scc;
}

vector <vector <int> > SCC::get_graph() {
    vector <vector <int> > new_graph(num_scc);
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < graph[i].size(); j++) {
            if (mapping[i] != mapping[graph[i][j]]) new_graph[mapping[i]].push_back(mapping[graph[i][j]]);
        }
    }
    return new_graph;
}

vector <int> SCC::get_mapping() {
    return mapping;
}

ReturnTypeToEnsureDiffout check(
	int n, const vector<pair<int, int>>& routes, // input data
	const vector<pair<int,int>>& edges)  // output data
{
    SCC scc(n);
    for (int i = 0; i < edges.size(); i++) scc.add_edge(edges[i].first, edges[i].second);
    scc.decompose();
    int num = scc.get_size();
    vector <vector <int>> graph = scc.get_graph();
    vector <int> mapping = scc.get_mapping();
    
    vector <bitset <MAX_N>> reachable(num);
    for (int i = 0; i < num; i++) reachable[i].set(i);
    for (int i = 0; i < num; i++) {
        for (int j = 0; j < graph[i].size(); j++) reachable[i] |= reachable[graph[i][j]];
    }
    
    for (int i = 0; i < routes.size(); i++) {
        int x = routes[i].first, y = routes[i].second;
        int mx = mapping[x], my = mapping[y];
        if (!reachable[mx][my]) {
        	return WRONG_ANSWER("Could not reach from " << x + 1 << " to " << y + 1);
        }
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
    int n, m, k;
    map <pair<int, int>, int> edges;
    vector <pair<int, int>> routes;
    fin >> n >> m;
    for (int i = 0; i < m; i++) {
        int x, y;
        fin >> x >> y;
        if (x > y) swap(x, y);
        x--;
        y--;
        edges[make_pair(x, y)] = 1;
    }
    fin >> k;
    for (int i = 0; i < k; i++) {
        int x, y;
        fin >> x >> y;
        x--;
        y--;
        routes.emplace_back(x, y);
    }
	if (!fin) {
		return INTERNAL_ERROR("Could not read the input: " << argv[1]);
    }

	// answer file
    string expected;
    fans >> expected;
	if (!fans) {
		return INTERNAL_ERROR("Could not read the correct-output: " << argv[2]);
    }

	// output (submitted) file
    string ans;
    cin >> ans;
    if (!cin) {
		return MALFORMED("Cannot read: answer");
    }
	if (ans != expected) {
		return WRONG_ANSWER("Output doesn't match the expected answer");
    }
	if (ans == "No") {
        /*
    	if (!cin.eof()) {
        	return MALFORMED("Too many lines");
        }
        */
		return OK();
    }

	vector <pair<int, int>> out;
    for (int i = 0; i < m; i++) {
        int x, y, mx, my;
        cin >> x >> y;
        x--;
        y--;
        mx = min(x, y);
        my = max(x, y);
		if (!cin) {
			return MALFORMED("Cannot read: index");
        }
		if (x < 0 || x >= n) {
			return MALFORMED("Invalid output: x=" << x + 1);
        }
		if (y < 0 || y >= n) {
			return MALFORMED("Invalid output: y=" << y + 1);
        }
		if (!edges.count(make_pair(mx, my))) {
			return MALFORMED("Invalid output: x,y=" << x + 1 << "," << y + 1);
        }
		if (edges[make_pair(mx, my)] == 0) {
			return MALFORMED("Dupped output: x,y=" << x + 1 << "," << y + 1);
        }
		edges[make_pair(mx, my)]--;
		out.emplace_back(x, y);
	}
    
    /*
    if (!cin.eof()) {
    	return MALFORMED("Too many lines");
    }
    */

	return check(n, routes, out);
}

int main(int argc, const char* argv[])
{
    return int(typed_main(argc, argv));
}
