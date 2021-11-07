#include <cmath>
#include <cstdio>
#include <string>
#include <vector>
#include <cstring>
#include <fstream>
#include <algorithm>
using namespace std;

// #define GROMAH_LOCAL_TEST

#define AC 0
#define WA 1
#define ERROR -1
#define MAXN 5000 + 5
#define LENGTH 10000000
#define LIM 10000000
#define max(a, b) (a) > (b) ? (a) : (b)

int n, k, pos, P[MAXN];
bool Flag[MAXN];
char buf[LENGTH];
vector<int> Loops;

int spj(ifstream &input, ifstream &user_output);

int main(int argc, char *args[]){
#ifdef GROMAH_LOCAL_TEST
	for (int i = 1; i <= 10; i ++)
	{
		ifstream input(to_string(i) + ".in");
		ifstream user_output(to_string(i) + ".out");
    	int result = spj(input, user_output);
		fprintf(stderr, "Case #%d: %s\n", i, result == AC ? "AC" : "WA");
	}
	return 0;
#else
	ifstream input("input");
	ifstream user_output("user_output");
    int result = spj(input, user_output);
    return result;
#endif
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

int spj(ifstream &input, ifstream &user_output)
{
	// Preset
    if (!(input >> n >> k)) return ERROR;
	bool fail = (n * (n - 1) / 2) % n != k;
    
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
			Flag[i] = false;
		for (int l = 1; l <= n; l ++)
			for (int r = l, sum = 0; r <= n; r ++)
			{
				sum += P[r];
				if (sum % n == k)
					Flag[r - l + 1] = true;
			}
		for (int i = 1; i <= n; i ++)
			if (!Flag[i])
				return WA;
	}
    
    return AC;
}
