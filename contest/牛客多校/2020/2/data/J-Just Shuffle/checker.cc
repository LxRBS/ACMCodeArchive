#include <cmath>
#include <cstdio>
#include <vector>
#include <cstring>
#include <fstream>
#include <algorithm>
using namespace std;

#define AC 0
#define WA 1
#define ERROR -1
#define MAXN 200000 + 5
#define LENGTH 10000000
#define LIM 10000000
#define max(a, b) (a) > (b) ? (a) : (b)

int n, k, pos, A[MAXN], P[MAXN], RP[MAXN];
bool Flag[MAXN];
char buf[LENGTH];
vector<int> Loops;

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

bool Fail(int k)
{
	for (int sz : Loops)
		if (__gcd(sz, k) != 1)
			return true;
	return false;
}

void Merge(int *src, int *obj)
{
	static int src_rk[MAXN], obj_rk[MAXN], ret_rk[MAXN], ret[MAXN];
	for (int i = 1; i <= n; i ++)
	{
		src_rk[src[i]] = i;
		obj_rk[obj[i]] = i;
	}
	for (int i = 1; i <= n; i ++)
		ret_rk[i] = obj_rk[src_rk[i]];
	for (int i = 1; i <= n; i ++)
		ret[ret_rk[i]] = i;
	for (int i = 1; i <= n; i ++)
		src[i] = ret[i];
}

int spj(ifstream &input, ifstream &user_output)
{
	// Preset
    if (!(input >> n >> k)) return ERROR;
    for (int i = 1; i <= n; i ++)
    {
    	if (!(input >> A[i]))
    		return ERROR;
    }
	for (int i = 1; i <= n; i ++)
		if (!Flag[i])
		{
			int cnt = 0;
			Flag[i] = 1, cnt ++;
			for (int x = A[i]; x != i; x = A[x])
				Flag[x] = 1, cnt ++;
			Loops.push_back(cnt);
		}
	sort(Loops.begin(), Loops.end());
	Loops.resize(unique(Loops.begin(), Loops.end()) - Loops.begin());
	bool fail = Fail(k);
    
    // Read
    string line;
    if (!getline(user_output, line)) return WA;
	pos = 0;
	if (!ReadEof(user_output))
		return WA;
	// Check Answer
    if (fail)
    {
    	// No Solution
	    int res;
	    if (ReadInt(line.data(), &pos, &res) != 1)
			return WA;
		if (ReadAny(line.data(), &pos)) return WA;
		if (res != -1) return WA;
	}
	else
	{
		// Has Solution
		// Read
		for (int i = 1; i <= n; i ++)
			Flag[i] = false;
		for (int i = 1; i <= n; i ++)
		{
			if (ReadInt(line.data(), &pos, P + i) != 1)
				return WA;
			if (P[i] <= 0 || P[i] > n)
				return WA;
			if (Flag[P[i]])
				return WA;
			Flag[P[i]] = 1;
		}
		
		// Validate
		for (int i = 1; i <= n; i ++)
			RP[i] = i;
		for (; k; k >>= 1)
		{
			if (k & 1)
				Merge(RP, P);
			Merge(P, P);
		}
		for (int i = 1; i <= n; i ++)
			if (A[i] != RP[i])
				return WA;
	}
    
    return AC;
}
