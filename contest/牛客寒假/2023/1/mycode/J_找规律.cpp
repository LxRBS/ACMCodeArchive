/**
 * 给定A、B、C三个数，已知C必然是用A和B位运算得到的。位运算包括位与、位或、异或。
 * 甲乙两人，甲知道AC、不知道B，乙知道BC、不知道A。且甲乙均不知道数的取值范围。
 * 甲乙轮流判断，轮到某人时，如果该人能够完全确定C是如何运算得到的，则游戏结束；
 * 否则该人不会说话，直接换人进行下一轮。
 * 现在给定ABC，问游戏在第几轮结束。无法结束返回-1。
 * 首先站在A的角度，已知AC，则有4种可能性:00，01，10，11，一共可以组合出15种可能，
 * 用二进制位表示，则可以用1~15来表示状态。
 * 例如考虑状态6，表示只存在{10, 01}的变换，即A中的1全都变成了C中的0，A中的0全变成了C中的1
 * 此时等价于 A=10, C=01, 考虑B，一共有4种可能性，且一定要成立，因此B只能取11，使用异或运算。
 * 类似推导15种状态，除{4,5,9,12,13}五种情况之外，其余A都能首轮确定。
 * 现在轮到B考虑，如果C中有1，于是可以肯定是状态{9,12,13}，因此可以肯定对于C为1的位A必然也是1。
 * 现在不知道的是C为0的为，A可能是0可能是1。
 * 因此对于B而言，现在的可能性是 1(10) -> 10
 * B取值有4种可能。
 * 00，此时A位必须是0，异或即可；
 * 01，此时A位必须是1，异或即可；
 * 10，无论A如何，与即可；
 * 11，此时A位必须是0，与即可。
 * 对于{4,5}情况，B只能知道C是全0，而A有可能是全1，也有可能是01混合。总之等价于(10) -> 0
 * 此时如果B是0，直接用与运算即可。但B如果是1，有可能要与，也有可能要异或，无法确定。
 * 因此到第三轮，A拿到的信息就是：C全0，B可能全1也可能01混合，但是不知道对位信息。于是存在两种可能，
 * 要么是 10 ^ 10 = 00, 要么是 10 & 01 = 00。即可能与，也可能异或。
 * 再进行下去，A和B也无法获得更多的信息。
 */
#include <bits/stdc++.h>
using namespace std;

#include <bits/extc++.h>
using namespace __gnu_pbds;

char *__abc147, *__xyz258, __ma369[100000];
#define __hv007() ((__abc147==__xyz258) && (__xyz258=(__abc147=__ma369)+fread(__ma369,1,100000,stdin),__abc147==__xyz258) ? EOF : *__abc147++)

int getInt(){
	int sgn = 1;
	char ch = __hv007();
	while( ch != '-' && ( ch < '0' || ch > '9' ) ) ch = __hv007();
	if ( '-' == ch ) {sgn = 0;ch=__hv007();}

	int ret = (int)(ch-'0');
	while( '0' <= (ch=__hv007()) && ch <= '9' ) ret = ret * 10 + (int)(ch-'0');
	return sgn ? ret : -ret;
}

using llt = long long;
using vll = vector<llt>;
using vvll = vector<vll>;
using v3ll = vector<vvll>;
using si = set<int>;

const si Set = {4, 5, 9, 12, 13};

int A, B, C;

int proc(){
    int status = 0;
    for(int i=0;i<32;++i){
        int abit = (A >> i) & 1;
        int cbit = (C >> i) & 1;
        status |= (1 << ((abit << 1) | cbit));
    }
    assert(1 <= status && status < 16);
    if(!Set.count(status)) return 1;

    if(4 == status || 5 == status){
        return B ? -1 : 2;
    }

    return 2;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif 
    int nofkase = getInt();
    while(nofkase--){
        A = getInt();
        B = getInt();
        C = getInt();
        printf("%d\n", proc());
    }
    return 0;
}
