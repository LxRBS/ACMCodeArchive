/**
    ����һ�����飬��ѯ�����в�ͬȨֵ������
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
//�ɳ־û���״����
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

//����״����ĵ�x���ڵ�����delta
//timestamp��ʾʱ�����ʵ���Ͼ��ǵ�timestamp���޸Ĳ���
int modify(int timestamp,int x,llt delta,int n){
    for(;x<=n;x+=lowbit(x)){//��Ҫ�޸�BIT[x]
        BIT[x].push_back(*--BIT[x].end());
        bit_node_t& node = *--BIT[x].end();
        node.value += delta;
        node.timestamp = timestamp;
    }
}

//��ѯ��������ѯ[1,x]֮������ݣ�timestamp��ʱ���
llt query(int timestamp,int x){
    llt ans = 0;
    for(;x>0;x-=lowbit(x)){//�ۼ�BIT[x][timestamp]
        vector<bit_node_t>const& v = BIT[x];
        int mid, left = 0, right = v.size()-1;
        do{//�ҵ����һ��timestamp<=������ʱ���
            mid = (left+right)>>1;
            if(v[mid].timestamp<=timestamp) left = mid + 1;
            else right = mid - 1;
        }while(left<=right);//right���Ǵ�
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
        BIT[i].assign(1,bit_node_t(0,0));//��ʼ��
    }
    //��ɢ��
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
        //�ڵ�b����״�����ϲ�ѯ[a,n]��ֵ
        printf("%d\n",query(Time[b],a,n));
    }
    return 0;
}
