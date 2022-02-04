/**
 * 交互问题，给定N，猜x，1<=x<N
 * 只有一个操作，给定c，系统会返回 x+c/N， 而且x变成了x+c
 * 很显然，第一个c选N/2，如果得0，则原x必然小于N/2，如果得1，则大于N/2
 * 所以二分即可
 * 令[left, right)为可行范围，则令c=N-mid
 * 如果得数不变则x在前一半，否则x在后一半
 * 最后Left是答案，注意左闭右开
*/
#include <bits/stdc++.h>
using namespace std;

#ifndef ONLINE_JUDGE
int const SIZE = 15;
#else
int const SIZE = 1010;
#endif

int N, M;
int Left, Right;

bool proc(){
    int mid = (Left + Right) >> 1;
	printf("+ %d\n", N - mid);
    fflush(stdout);

	int m;
    scanf("%d", &m);
    if(m == M){
        Right = mid;
	}else{
        Left = mid;
		M = m;
	}
	Left = (Left + N - mid) % N;
	Right = (Right + N - mid) % N;
	if(0 == Right) Right = N;
	if(Left + 1 >= Right){
		printf("! %d\n", Left + M * N);
		return false;
	}
	return true;
}

int main() {
#ifndef ONLINE_JUDGE
    // freopen("1.txt", "r", stdin);
#endif  
	scanf("%d", &N);  
	Left = 1, Right = N;
	M = 0;
	while(proc());  
    return 0;
}
