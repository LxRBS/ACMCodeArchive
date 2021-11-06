// Author Alexander Rass
#include <bits/stdc++.h>
using namespace std;
// TODO add minimal allowed distance between points
const int MAXN = 1024;
vector<int> adj[MAXN];
long long min_y[MAXN], x[MAXN], y[MAXN];
void rek_init(int n, int d = 0, int p=-1){
    for(auto to: adj[n])if(to != p){
        min_y[d] = y[to] = max(min_y[d] + 2000, y[n] - 500 + 1);
        x[to] = x[n] + 999999001;
        rek_init(to, d+1, n);
    }
}

void printnum(long long n){
    if(n < 0)printf("-");
    n = abs(n);
    printf("%lld.%09lld",n/1000000000, n%1000000000);
}
int main(){
    int N,a,b;
    cin >> N;
    for(int i = 1; i < N; i++){
        cin >> a >> b;
        adj[--a].push_back(--b);
        adj[b].push_back(a);
    }
    for(int i = 0; i < MAXN; i++)min_y[i] = -1e9;
    x[0] = y[0] = 0;
    rek_init(0);
    for(int i = 0; i < N; i++){
        printnum(x[i]);
        printf(" ");
        printnum(y[i]);
        printf("\n");
    }
	return 0;
}
