#include <cstdio>
#include <vector>
#include <cstring>
#include <fstream>
using namespace std;

#define AC 0
#define WA 1
#define ERROR -1
#define MAXN 200000 + 5
#define LOGN 20
#define LENGTH 10000000
#define LIM 10000000
#define max(a, b) (a) > (b) ? (a) : (b)

int n, m, cnt, pos, T[MAXN], Deg[MAXN], Dep[MAXN], Go[MAXN][LOGN];
char buf[LENGTH];
bool Flag[MAXN];
vector<int> Vec[MAXN];

int spj(ifstream &input, ifstream &user_output);

int main(int argc, char *args[]){
	ifstream input("input");
	ifstream user_output("user_output");
    int result;

    result = spj(input, user_output);
    //printf("result: %d\n", result);
    
    return result;
}

int IsBlank(char c)
{
	int res = (c == ' ' || c == '\t' || c == '\n') ? 1 : 0;
	return res;
}

int IsDigit(char c)
{
	int res = (c >= '0' && c <= '9') ? 1 : 0;
	return res;
}

int ReadBlank(const char *p, int *st)
{
	char ch = p[*st];
	(*st) ++;
	return (ch == ' ') ? 1 : 0;
}

static int read_int_strict = 0;
int ReadInt(const char *p, int *st, int *x)
{
	if (!read_int_strict)
		for (; p[*st] != '\n' && IsBlank(p[*st]); (*st) ++) ;
	if (p[*st] == '\n') return 0;
	if (p[*st] != '-' && !IsDigit(p[*st])) return 0;
	int f = p[*st] == '-' ? -1 : 1;
	*x = p[*st] == '-' ? 0 : p[*st] - '0';
	for ((*st) ++; IsDigit(p[*st]); (*st) ++)
	{
		*x = (*x) * 10 + p[*st] - '0';
		if (*x > LIM) return 0;
	}
	*x = *x * f;
	return 1;
}

static int read_any_strict = 0;
int ReadAny(const char *p, int *st)
{
	if (!read_any_strict)
		for (; p[*st] != '\n' && p[*st] != '\0' && IsBlank(p[*st]); (*st) ++) ;
	if (p[*st] == '\n' || p[*st] == '\0') return 0;
	return 1;
}

static int read_eof_strict = 0;
int ReadEof(ifstream &fin)
{
	char ch;
	fin >> ch;
	if (!read_eof_strict)
	{
		while (fin && IsBlank(ch))
			fin >> ch;
	}
	return !fin;
}

void SetStrictMode(int read_int_strict_mode, int read_any_strict_mode, int read_eof_strict_mode)
{
	read_int_strict = read_int_strict_mode;
	read_any_strict = read_any_strict_mode;
	read_eof_strict = read_eof_strict_mode;
}

void SetStrictMode(int mode)
{
	SetStrictMode(mode, mode, mode);
}

void dfs(int z)
{
	for (int d : Vec[z])
	{
		if (d == Go[z][0]) continue ;
		Go[d][0] = z, Dep[d] = Dep[z] + 1;
		for (int j = 1, x = z; Go[x][j - 1]; x = Go[x][j - 1], j ++)
			Go[d][j] = Go[x][j - 1];
		dfs(d);
	}
}

int LCA(int u, int v)
{
	if (Dep[u] < Dep[v])
		swap(u, v);
	for (int t = Dep[u] - Dep[v]; t; t -= (t & -t))
		u = Go[u][__builtin_ffs(t) - 1];
	if (u == v) return u;
	for (int i = LOGN - 1; Go[u][0] != Go[v][0]; i --)
		if (Go[u][i] != Go[v][i])
			u = Go[u][i], v = Go[v][i];
	return Go[u][0];
}

void DFS(int z)
{
	for (int d : Vec[z])
	{
		if (d == Go[z][0]) continue ;
		DFS(d);
		T[z] += T[d];
	}
}

int spj(ifstream &input, ifstream &user_output)  
{
	// Preset
    if (!(input >> n))
		return ERROR;
    for (int i = 1, u, v; i < n; i ++)
    {
    	if (!(input >> u >> v))
    		return ERROR;
    	Deg[u] ++, Deg[v] ++;
    	Vec[u].push_back(v);
    	Vec[v].push_back(u);
    }
    for (int i = 1; i <= n; i ++)
    	if (Deg[i] == 1)
    		cnt ++;
    m = (cnt + 1) >> 1;
    dfs(1);
    
    // Read User Output
    // Read m
    string line;
    if (!getline(user_output, line)) return WA;
    pos = 0;
    int res;
    if (ReadInt(line.data(), &pos, &res) != 1)
		return WA;
	if (ReadAny(line.data(), &pos)) return WA;
	if (res != m) return WA;
	
	// Read Chains
	for (int i = 1, u, v; i <= m; i ++)
	{
		if (!getline(user_output, line)) return WA;
		pos = 0;
		if (ReadInt(line.data(), &pos, &u) != 1)
			return WA;
		if (ReadInt(line.data(), &pos, &v) != 1)
			return WA;
		if (ReadAny(line.data(), &pos))
			return WA;
		if (u < 1 || u > n || v < 1 || v > n)
			return WA;
		int lca = LCA(u, v);
		T[u] ++, T[v] ++, T[lca] -= 2;
	}
	if (!ReadEof(user_output))
		return WA;
	// Validation
	DFS(1);
	for (int i = 2; i <= n; i ++)
		if (T[i] <= 0)
			return WA;
	
    return AC;
}
