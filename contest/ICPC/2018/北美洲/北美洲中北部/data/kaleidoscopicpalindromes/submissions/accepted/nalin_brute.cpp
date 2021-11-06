#include <iostream>
#include <cstdio>
#include <vector>
#include <cmath>
using namespace std;

bool check(int x, int y)
{
	string T;
	while(x)
	{
		T += char(x%y);
		x /= y;
	}
	return bool(T == string(T.rbegin(), T.rend()));
}

int main(void)
{
	int a, b, k, res = 0;
	scanf("%d%d%d", &a, &b, &k);
	for(int i = a;i <= b;i++)
	{
		bool done = 1;
		for(int j = 2;j <= k;j++)
		{
			if(!check(i, j))
			{
				done = false;
				break;
			}
		}
		res += done;
	}
	printf("%d\n", res);
}