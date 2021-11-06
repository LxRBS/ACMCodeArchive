/**
  ����2000���㣨û���ظ��ĵ㣬Ҳû��ԭ�㣩
  ��һ��Բ��ԭ�㣬�ҹ����ĵ㣬�������������
  ˫��ѭ������ÿһ��ij����ԭ�����㹲Բ�����Բ
  ���г��ִ�������Բ����Ӧ�ĵ��������һ���ۼӺ�
  �����������������
  Բ��������ӳ����Hash��ɣ���Map��ʱ��
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long llt;

int getInt(){
	int sgn = 1;
	char ch = getchar();
	while( ch != '-' && ( ch < '0' || ch > '9' ) ) ch = getchar();
	if ( '-' == ch ) {sgn = 0;ch=getchar();}

	int ret = (int)(ch-'0');
	while( '0' <= (ch=getchar()) && ch <= '9' ) ret = ret * 10 + (int)(ch-'0');
	return sgn ? ret : -ret;
}

llt gcd(llt a,llt b){
    while( b ){
        llt r = b;
        b = a % b;
        a = r;
    }
    return a;
}

struct point_t{
    llt x,y;
    point_t(llt a=0,llt b=0):x(a),y(b){}
}Point[2100];

struct circle_t{
    llt a,b,c;//ƽ��ϵ�����Լ�x��y��ϵ�����϶������
    circle_t():a(0),b(0),c(0){}
    circle_t(const point_t& A,const point_t& B){
        llt fangA = A.x*A.x+A.y*A.y;
        llt fangB = B.x*B.x+B.y*B.y;
        a = A.x*B.y-B.x*A.y;
        b = fangB*A.y-fangA*B.y;
        c = fangA*B.x-fangB*A.x;
        llt g = gcd(gcd(a,b),c);
        a /= g, b /= g, c /= g;
        if(a<0)a=-a,b=-b,c=-c;
    }
};

bool operator < (const circle_t &lhs,const circle_t&rhs){
    return lhs.a<rhs.a||(lhs.a==rhs.a&&lhs.b<rhs.b)||(lhs.a==rhs.a&&lhs.b==rhs.b&&lhs.c<rhs.c);
}

bool operator == (const circle_t &lhs,const circle_t&rhs){
    return (lhs.a==rhs.a&&lhs.b==rhs.b&&lhs.c==rhs.c);
}
struct hash_t{
    typedef circle_t key_t;
    typedef int value_t;
    enum{MOD=0x1FFFFF};

    key_t keys[MOD+1];
    value_t values[MOD+1];

    int head[MOD+1];
    int next[MOD+1];

    int toUsed;

    hash_t():toUsed(0){fill(head,head+MOD+1,-1);}

    void clear(){toUsed=0;fill(head,head+MOD+1,-1);}

    int getKey(key_t const&key)const{
        int ret = key.a;
        ret = ret * 1331 + key.b;//31�����Ӿͳ�ʱ��
        ret = ret * 1331 + key.c;
        return ret;
    }

    void insert(key_t const&key,value_t const&value){
        int k = getKey(key) & MOD;
        keys[toUsed] = key;
        values[toUsed] = value;
        next[toUsed] = head[k];
        head[k] = toUsed++;
    }

    value_t find(key_t const&key)const{
        int k = getKey(key) & MOD;
        for(int i=head[k];i!=-1;i=next[i]){
            if ( keys[i] == key ) return values[i];
        }
        return -1;
    }

    value_t& operator [] (key_t const&key){
        int k = getKey(key) & MOD;
        for(int i=head[k];i!=-1;i=next[i]){
            if ( keys[i] == key ) return values[i];
        }

        keys[toUsed] = key;
        values[toUsed] = 0;//����û��key�Ͳ���һ��Ĭ��ֵ
        next[toUsed] = head[k];
        head[k] = toUsed++;
        return values[toUsed-1];
    }
}Hash;

int main(){
    //freopen("1.txt","r",stdin);
    int n = getInt();
    for(int i=1;i<=n;++i){
        Point[i].x = getInt();
        Point[i].y = getInt();
    }

    int ans = 0;
    for(int i=1;i<n;++i)for(int j=i+1;j<=n;++j){
        if(Point[j].x*Point[i].y==Point[j].y*Point[i].x) continue;
        ans = max(ans, Hash[circle_t(Point[i],Point[j])] += 1);
    }
    if(0==ans){
        cout<<1<<endl;
        return 0;
    }
    int k = 0;
    for(int i=1;i<=n;++i){
        k += i;
        if(ans<=k){
            cout<<i+1<<endl;
            return 0;
        }
    }
    return 0;
}
