#include <iostream>
#include <cstdio>
#include <vector>
#include <set>
using namespace std;

int main(void)
{
	int n, q;
	scanf("%d%d", &n, &q);
	if(!(1 <= n && n <= 200000))
	{
		cerr << "n out of bounds\n";
		return 1;
	}
	if(!(1 <= q && q <= 200000))
	{
		cerr << "q out of bounds\n";
		return 2;
	}

	set<string> S;
	int totlen = 0;
	for(int i = 0;i < n;i++)
	{
		string T;
		cin >> T;
		for(auto it: T)
		{
			if(!('a' <= it && it <= 'z'))
			{
				cerr << "not all characters belong to [a-z]\n";
				return 3;
			}
		}
		S.insert(T);
		totlen += int(T.size());
	}

	if(int(S.size()) != n)
	{
		cerr << "not all strings are distinct\n";
		return 4;
	}
	if(!(1 <= totlen && totlen <= 200000))
	{
		cerr << "total length of strings out of bounds\n";
		return 5;
	}

	int totk = 0;
	for(int j = 0;j < q;j++)
	{
		int k, l;
		scanf("%d%d", &k, &l);
		if(!(1 <= k && k <= n))
		{
			cerr << "k out of bounds\n";
			return 6;
		}
		if(!(1 <= l && l <= k))
		{
			cerr << "l out of bounds\n";
			return 7;
		}

		set<int> X;
		for(int i = 0;i < k;i++)
		{
			int tmp;
			scanf("%d", &tmp);
			X.insert(tmp);
		}
		if(int(X.size()) != k)
		{
			cerr << "not all indices are distinct\n";
			return 8;
		}

		totk += k;
	}

	if(!(1 <= totk && totk <= 1000000))
	{
		cerr << "total value of k is out of bounds\n";
		return 9;
	}

    int blah1, blah2;
    if (cin >> blah1 >> blah2) {
        cerr << "input too long\n";
        return 10;
    }

	cerr << "OK.\nn, q, totk, totlen: " << n << " " << q << " " << totk << " " << totlen << "\n";
    return 42;
}