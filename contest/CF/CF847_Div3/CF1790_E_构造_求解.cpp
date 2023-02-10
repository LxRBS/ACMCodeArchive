/**
 * 给定X，要求构造A和B，使得 X = A ^ B = (A + B) / 2
 * 根据样例就能观察出规律, X如果有1的话，低一位必须是0，且这两位A和B分别对应01和11
 * 0的话直接对应0即可。
 */
#include <bits/stdc++.h>
using namespace std;

int X;
int A, B;

void proc(){
	if(X & 1) return (void)printf("-1\n");

    int a = 0, b = 0;
    int k = 1;
	while(k<=30){
		if(((1<<k) & X) && ((1<<k+1) & X)) return (void)printf("-1\n");
		if((1 << k) & X){
			a |= 1 << k - 1;
			b |= 1 << k - 1;
			b |= 1 << k;
			k += 2;			
		}else{
			++k;
		}
	}
	printf("%d %d\n", a, b);
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    int nofkase; scanf("%d", &nofkase);
    while(nofkase--){
        scanf("%d", &X);
        proc();
    }
    return 0;
}
