/**
 * 给定数组A和一个数值X，问是否存在A中的两个元素使得
 * Ai - Aj == X
 * 稍微做一下变形，基本的查找问题
 */
#include <bits/stdc++.h>
using namespace std;

int X;
int N;
vector<int> A;

bool proc(){
	multiset<int> s(A.begin(), A.end());
	for(int i : A){
		if(s.count(i + X)) return true;
	}
	return false;
}


int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> N >> X;
	A.assign(N, 0);
	for(int & i : A) cin >> i;
	puts(proc()?"Yes":"No");
    return 0; 
}
