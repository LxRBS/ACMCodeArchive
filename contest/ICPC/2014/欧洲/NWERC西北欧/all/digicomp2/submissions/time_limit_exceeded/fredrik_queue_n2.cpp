#include <iostream>
#include <queue>
#include <set>
#include <vector>
using namespace std;


struct Switch
{
	long long totballsin;
	long long ballsin;
	char start;
	bool inq;
	int idx;
	int left;
	int right;
	set<int> inputs;

	void doit();
};

vector<Switch> switches;
queue<int> q;


void Switch::doit()
{
	if (idx == 0)
		return;
	if (ballsin == 0)
		return;
	if ((start == 'L') ^ ((totballsin % 2) == 1))
	{
		switches[left].ballsin += (ballsin+1)/2;
		switches[right].ballsin += (ballsin)/2;
	}
	else
	{
		switches[left].ballsin += (ballsin)/2;
		switches[right].ballsin += (ballsin+1)/2;
	}
	if (!switches[left].inq)
	{
		switches[left].inq = true;
		q.push(left);
	}
	if (!switches[right].inq)
	{
		switches[right].inq = true;
		q.push(right);
	}
	totballsin += ballsin;
	ballsin = 0;
}

int main()
{
	long long balls;
	int switchcount;
	cin >> balls >> switchcount;
	switches.resize(switchcount+1);
	for (int i = 1; i <= switchcount; ++i)
	{
		char str[4];
		int a, b;
		cin >> str >> a >> b;
		switches[a].inputs.insert(i);
		switches[b].inputs.insert(i);
		switches[i].idx = i;
		switches[i].left = a;
		switches[i].right = b;
		switches[i].start = str[0];
		switches[i].inq = false;
		switches[i].ballsin = 0;
		switches[i].totballsin = 0;
	}
	switches[0].inq = true;
	switches[1].ballsin = balls;
	q.push(1);
	while (!q.empty())
	{
		int i = q.front();
		q.pop();
		switches[i].inq = false;
		switches[i].doit();
	}
	for (int i = 1; i <= switchcount; ++i)
		cout << (char)((switches[i].totballsin & 1) == 0 ? switches[i].start : ('L' + 'R' - switches[i].start));
	cout << endl;
	return 0;
}
