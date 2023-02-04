/**
 * 有三类事件，两个数据库，分别记作Pro和Rank
 * 1 t时刻在Rank中查询name的值
 * 2 t时刻Pro[name] += w
 * 3 t时刻将Pro的数据拷贝到Rank，此事件不是由输入直接给定的，而是分两种情况
 * 每T个时刻，将Pro的数据全部拷贝到Rank。或者，对每一个1事件，R时刻之后将name的数据从Pro拷贝到Rank
 * 现在给定了一系列的1和2事件，对每一个1事件，输出查询结果
 * 第3类事件的第一种情况，拷贝Pro全体，这是唯一耗时的操作，需要考虑。
 * 有两种思路，第一种是只需要保证查询操作正确即可，即不拷贝全部，而只拷贝那些被查了的name的，不过此处可能不适用
 * 第二种是考虑在一个全拷贝中，其实有很多东西是没有变化的，也就是不需要拷贝，只拷贝那些有变化的需要拷贝的东西
 * 显然是2操作的name的值发生了变化，需要拷贝。而2操作最多是N，因此按照这个思路，最多单点拷贝N次，是可以接受的
 * 注意输入并不是按照时间顺序给出的，因此需要离线回答。
 * 为了模拟时间，使用了优先队列。但实际上输入以后，全过程事件都是确定的，因此做个排序即可，效率更高。
 */
#include <bits/stdc++.h>
using namespace std;
 
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
 
#ifndef ONLINE_JUDGE
int const SIZE = 13;
#else
int const SIZE = 1E6+10;
#endif

using llt = long long;
/// 时间, 类型, 姓名, 题数
using _t = tuple<int, int, string, llt>;

int const SHUA = 1;
int const PA = 2;
int const CHA = 4;

map<string, llt> Rank;
map<string, llt> Pro;
priority_queue<_t, vector<_t>, greater<_t>> Q;

int N, T, R;
vector<llt> Ans;

int main(){
#ifndef ONLINE_JUDGE
    freopen("1.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> N >> T >> R;
    int t, w, cmd;
    string name;
    int c = 0;
    for(int i=0;i<N;++i){
        cin >> cmd >> t >> name;
        if(1 == cmd){
            Q.push({t, CHA, name, c++});
        }else{
            cin >> w;
            Q.push({t, SHUA, name, w});
        }
    }
    Ans.assign(c, 0LL);
    while(!Q.empty()){
        auto h = Q.top(); Q.pop();
        int time = get<0>(h);
        int type = get<1>(h);
        string name = get<2>(h);
        int w = get<3>(h);
        switch(type){
            case SHUA:{
                Pro[name] += w;
                if(time % T == 0) Q.push({time, PA, name, 0});
                else Q.push({time/T*T+T, PA, name, 0}); 
            }break;
            case PA:{
                Rank[name] = Pro[name];     
            }break;
            case CHA:{
                Ans[w] = Rank[name];
                Q.push({time+R, PA, name, 0});     
            }break;
            default: assert(0);
        }
    }
    for(auto i : Ans) printf("%lld\n", i);
    return 0;
}