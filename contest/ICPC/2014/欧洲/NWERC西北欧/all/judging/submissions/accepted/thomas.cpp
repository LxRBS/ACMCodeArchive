// Solution to Judging Troubles
// Author: Thomas Beuman

// Time complexity: O(n*log(n))
// Memory: O(n)

// Expected result: accepted

#include <cstdio>
#include <map>
#include <string>
using namespace std;

map<string,int> Nr;

int main()
{	int n, i, match = 0;
	char buf[16];
	string result;
	scanf("%d\n", &n);
	for (i = 0; i < 2*n; i++)
	{	scanf("%s", buf);
		result = buf;
		if (i < n)
			Nr[result]++;
		else if (Nr[result] > 0)
		{	Nr[result]--;
			match++;
		}
	}
	printf("%d\n", match);
}
