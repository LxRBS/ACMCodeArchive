#include <bits/stdc++.h>

#if defined(_WIN32) || defined(_WIN64)
#define COPY_COMMAND "copy"
#define RUN_COMMAND ""
#define DEL_COMMAND "del"
#else
#define COPY_COMMAND "cp"
#define RUN_COMMAND "./"
#define DEL_COMMAND "rm -f"
#endif
namespace Random
{
	const int Seed = -1;
	std::mt19937 rng;
	
	void prework()
	{
		if(Seed == -1) rng = std::mt19937(std::chrono::high_resolution_clock().now().time_since_epoch().count());
		else rng = std::mt19937(Seed);
	}
	int rnd(int x, int y) { return std::uniform_int_distribution<int>(x, y)(rng); }
	int rnd() { return rng(); }
	long long rndll(long long x, long long y) { return std::uniform_int_distribution<long long>(x, y)(rng); }
	long long rndll() { return (static_cast<long long>(rng()) << 32) + rng(); }
	template<typename Tp> void shuffle(Tp __first, Tp __last) { std::shuffle(__first, __last, rng); }
}
using Random::rnd;
using Random::rndll;

const std::string inSuf  =  ".in";
const std::string outSuf = ".out";
const std::string ansSuf = ".ans";
const std::string probName = "tree";
const int NumTest = 20;
const int TestIdFrom = 1;
const bool MultipleTests = false;
const bool FileIO = false;
const int CaseCnt[NumTest] = {}; // This must be filled if MultipleTests is set to true.

void Generate();
void Validate();
void Print(FILE *);
std::string toString(int x)
{
	if(x == 0) return "0";
	std::string ret = "";
	while(x) { ret = char('0' + x % 10) + ret; x /= 10; }
	return ret;
}

// current number of test you are generating (starting from zero)
int curTest;
// current case you are generating (if MultipleTests is set to true)
int curCase;
// test number used as file names
int realTest;
int main()
{
	Random::prework();
	
	std::string exe = RUN_COMMAND + probName;
	std::string inName = probName + inSuf;
	std::string outName = probName + outSuf;
	if(!FileIO) exe = exe + " < " + inName + " > " + outName;
	
	system("@echo off");
	for(curTest = 0; curTest < NumTest; curTest++)
	{
		realTest = curTest + TestIdFrom;
		
		std::string realIn = probName + toString(realTest) + inSuf;
		std::string realAns = probName + toString(realTest) + ansSuf;
		
		printf("Test Number %d: generating\n", realTest);
		FILE *inF = fopen(inName.c_str(), "w");
		
		if(!MultipleTests)
		{
			Generate();
			Validate();
			Print(inF);
			fclose(inF);
		}
		else
		{
			fprintf(inF, "%d\n", CaseCnt[curTest]);
			for(curCase = 1; curCase <= CaseCnt[curTest]; curCase++)
			{
				Generate();
				Validate();
				Print(inF);
			}
			fclose(inF);
		}
		
		printf("Test Number %d: Running\n", realTest);
		auto start_time = std::chrono::high_resolution_clock().now();
		
		system(exe.c_str());
		
		auto end_time = std::chrono::high_resolution_clock().now();
		double time_used = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count() / 1e3;
		
		fprintf(stderr,"Test Number %d: run time= %.6lf\n", realTest, time_used);
		
		system((COPY_COMMAND" "  + inName + " " + realIn).c_str());
		system((COPY_COMMAND" "  + outName + " " + realAns).c_str());
		
		puts("\n");
	}
	system((DEL_COMMAND" " + inName).c_str());
	system((DEL_COMMAND" " + outName).c_str());
	 
	return 0;
}

const int maxn = 1000111;
int n, eu[maxn], ev[maxn], s, t;

int M;

void addedge(int u, int v)
{
	M++;
	eu[M] = u;
	ev[M] = v;
}
void gen_array(const std::vector<int> &a)
{
	int cnt = 0, last = 0;
	s = 1;
	for(int i=0; i<a.size(); i++)
	{
		cnt++;
		if(last) addedge(last, cnt);
		last = cnt;
		for(int j=1; j<a[i]; j++)
		{
			cnt++;
			addedge(cnt-1, cnt);
		}
	}
	t = last;
}

void Generate()
{
	M = 0;
	
	if(curTest < 4) n = 50;
	else if(curTest < 10) n = 1000;
	else n = 500000;
	n = rnd(n - 10, n);
	
	int chain = rnd(2, n);
	std::vector<int> vs(chain, 0);
	for(int i=0; i<chain/3; i++) vs[rnd(0, chain-1)]++;
	for(int i=chain/3; i<chain; i++) vs[int(sqrt(rnd(0, chain-1)))]++;
	
	std::sort(vs.begin(), vs.end(), std::greater<int>());
	while(vs.size() && vs.back() == 0) vs.pop_back();
	if(curTest % 2 == 0) Random::shuffle(vs.begin(), vs.end());
	else
	{
		std::vector<int> v1, v2;
		for(auto v : vs)
		{
			if(rnd(0, 1)) v1.emplace_back(v);
			else v2.emplace_back(v);
		}
		for(int i=0; i<(int)v1.size(); i++) std::swap(v1[i], v1[std::max(0, rnd(i-4, i))]);
		for(int i=0; i<(int)v2.size(); i++) std::swap(v2[i], v2[std::max(0, rnd(i-4, i))]);
		if(rnd(0, 1))
		{
			std::reverse(v1.begin(), v1.end());
			std::reverse(v2.begin(), v2.end());
		}
		vs.clear();
		for(auto v : v1) vs.emplace_back(v);
		for(auto v : v2) vs.emplace_back(v);
	}
	gen_array(vs);
	for(int i=chain; i<n; i++) addedge(i+1, rnd(1, chain));
}

int F[maxn];
int gf(int x) { return x == F[x] ? x : F[x] = gf(F[x]); }
void Validate() // use asserts to validate test data
{
	assert(1 <= n && n <= 500000);
	assert(1 <= s && s <= n);
	assert(1 <= t && t <= n);
	assert(s != t);
	for(int i=1; i<=n; i++) F[i] = i;
	for(int i=1; i<n; i++)
	{
		assert(1 <= eu[i] && eu[i] <= n);
		assert(1 <= ev[i] && ev[i] <= n);
		F[gf(eu[i])] = gf(ev[i]);
	}
	for(int i=1; i<=n; i++) assert(gf(i) == gf(1));
}

#define printf(...) fprintf(fin, __VA_ARGS__)
void Print(FILE *fin)
{
	static int ord[maxn];
	for(int i=1; i<=n; i++) ord[i] = i;
	Random::shuffle(ord+1, ord+n+1);
	printf("%d %d %d\n", n, ord[s], ord[t]);
	for(int i=1; i<n; i++) printf("%d %d\n", ord[eu[i]], ord[ev[i]]);
}
