#include <bits/stdc++.h>
using namespace std;

namespace DS{

struct UFSet{ // 并查集

vector<int> father;

void init(int n){father.assign(n+1, 0);for(int i=1;i<=n;++i)father[i]=i;}

int find(int x){return father[x]==x?x:father[x]=find(father[x]);}

void unite(int x, int y){father[find(y)]=find(x);}

};


}