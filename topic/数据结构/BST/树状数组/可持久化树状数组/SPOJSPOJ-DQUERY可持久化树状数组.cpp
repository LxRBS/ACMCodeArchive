/**
    给定一个数组，查询区间中不同权值的数量
*/
#include <bits/stdc++.h>
using namespace std;

typedef int llt;

int getUnsigned(){
	char ch = getchar();
	while( ch < '0' || ch > '9' ) ch = getchar();

	int ret = (int)(ch-'0');
	while( '0' <= ( ch = getchar() ) && ch <= '9' ) ret = ret * 10 + (int)(ch-'0');
	return ret;
}

struct bit_node_t{
    llt value;
    int timestamp;
    bit_node_t(llt a=0,int b=0):value(a),timestamp(b){}
    void disp(ostream&os=cout)const{cout<<"("<<value<<","<<timestamp<<")";}
};

int const SIZE = 30010;
//可持久化树状数组
vector<bit_node_t> BIT[SIZE];
inline int lowbit(int x){return x&-x;}


void dispBIT(int n){
    for(int i=1;i<=n;++i){
        for(int j=0;j<BIT[i].size();++j){
            BIT[i][j].disp();
        }
        cout<<endl;
    }
}

//将树状数组的第x个节点增加delta
//timestamp表示时间戳，实际上就是第timestamp个修改操作
int modify(int timestamp,int x,llt delta,int n){
    for(;x<=n;x+=lowbit(x)){//需要修改BIT[x]
        BIT[x].push_back(*--BIT[x].end());
        bit_node_t& node = *--BIT[x].end();
        node.value += delta;
        node.timestamp = timestamp;
    }
}

//查询操作，查询[1,x]之间的数据，timestamp是时间戳
llt query(int timestamp,int x){
    llt ans = 0;
    for(;x>0;x-=lowbit(x)){//累加BIT[x][timestamp]
        vector<bit_node_t>const& v = BIT[x];
        int mid, left = 0, right = v.size()-1;
        do{//找到最后一个timestamp<=给定的时间戳
            mid = (left+right)>>1;
            if(v[mid].timestamp<=timestamp) left = mid + 1;
            else right = mid - 1;
        }while(left<=right);//right就是答案
        ans += v[right].value;
    }
    return ans;
}

inline llt query(int timestamp,int s,int e){
    return query(timestamp,e) - query(timestamp,s-1);
}


int A[SIZE],B[SIZE];
int LastPos[SIZE];
int Time[SIZE];

int main(){
    //freopen("1.txt","r",stdin);
    int n = getUnsigned();
    for(int i=1;i<=n;++i){
        A[i] = B[i] = getUnsigned();
        BIT[i].assign(1,bit_node_t(0,0));//初始化
    }
    //离散化
    sort(B,B+n+1);
    int nn = unique(B+1,B+n+1) - B - 1;

    int time = 0;
    fill(LastPos,LastPos+nn+1,0);
    for(int i=1;i<=n;++i){
        int tmp = lower_bound(B+1,B+nn+1,A[i]) - B;

        if(LastPos[tmp]){
            modify(++time,LastPos[tmp],-1,n);
            modify(++time,i,+1,n);
        }else{
            modify(++time,i,+1,n);
        }
        Time[LastPos[tmp] = i] = time;
    }
    //dispBIT(n);
    int q = getUnsigned();
    while(q--){
        int a = getUnsigned();
        int b = getUnsigned();
        //在第b个树状数组上查询[a,n]的值
        printf("%d\n",query(Time[b],a,n));
    }
    return 0;
}
