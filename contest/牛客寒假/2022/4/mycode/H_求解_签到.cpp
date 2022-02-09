/**
 * 就是给定立方体对角线的长度的一半，求体积
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif    
    double x; cin >> x;
	printf("%.12f\n", pow(x/sqrt(3.0)*2, 3.0));
    return 0;
}
