/**
    给定N个点，选4个点使得构成的四边形面积最大
    首先做一个凸包
    如果凸包只有3个点，则再做一个O(N)算法，枚举凸包中的每一个点
    如果凸包多于4个点，则用旋转卡壳法，对每一个对角线，枚举另外两个点，O(N^2)
*/
#include <bits/stdc++.h>
using namespace std;

int getUnsigned(){
	char ch = getchar();
	while( ch < '0' || ch > '9' ) ch = getchar();

	int ret = (int)(ch-'0');
	while( '0' <= ( ch = getchar() ) && ch <= '9' ) ret = ret * 10 + (int)(ch-'0');
	return ret;
}

typedef long long llt;
inline llt ABS(llt x) {return x>=0?x:-x;}

struct point_t{
    llt x, y;
    point_t(llt a=0,llt b=0):x(a),y(b){}
    bool operator == (const point_t&rhs)const{
        return this->x == rhs.x && this->y == rhs.y;
    }
    bool operator != (const point_t&rhs)const{
        return this->x != rhs.x || this->y != rhs.y;
    }
    bool operator < (const point_t&rhs){
        return this->x < rhs.x || (this->x==rhs.x&&this->y<rhs.y);
    }
};

struct point_hash{
	inline size_t operator()(const point_t&p)const{
		return p.x * 1331 + p.y;
	}
};

//叉积，OA×OB
llt cross(point_t const&O,point_t const&A,point_t const&B){
    llt xoa = A.x - O.x;
	llt yoa = A.y - O.y;
	llt xob = B.x - O.x;
	llt yob = B.y - O.y;
	return xoa * yob - xob * yoa;
}

//A如果比B更靠下更靠左返回真
bool isLowLeft(point_t const&A,point_t const&B){
	return A.y < B.y || ( A.y == B.y && A.x < B.x );
}

//按对于pO的极角排序，极角相等的距离近的排在前面
point_t* pO;
bool comp4Graham(point_t const&A,point_t const&B){
    llt t = cross(*pO,A,B);
	if ( t ) return t > (llt)0;

	llt a1 = A.x > pO->x ? A.x - pO->x : pO->x - A.x;
	llt a2 = B.x > pO->x ? B.x - pO->x : pO->x - B.x;
    if ( a1 != a2 ) return a1 < a2;

	a1 = A.y > pO->y ? A.y - pO->y : pO->y - A.y;
	a2 = B.y > pO->y ? B.y - pO->y : pO->y - B.y;
	return a1 < a2;
}

//Graham求凸包，结果当中有共线点，起点总是最下最左点
int Graham(point_t P[],int n){
    if ( 1 == n ) return 1;

	//寻找最下最左点
	point_t *p = min_element(P,P+n,isLowLeft);

	//交换
	swap(*p,P[0]);

	if ( 2 == n ) return 2;

	//按极角排序，极角相等，距离近的排在前面
	pO = P;
	sort(P+1,P+n,comp4Graham);

	//将最后一条边的共线点倒过来排序
	int k = n - 1;
	while( k && 0LL == cross(P[0],P[n-1],P[--k]) );//k为0说明所有点共线
	if ( k ) for(int i=k+1;i<(n+k+1)>>1;++i) swap(P[i],P[n+k-i]);

	//真正的Graham循环
	int top = 2;
	for(int i=2;i<n;++i){
		while( top > 1 && cross(P[top-2],P[top-1],P[i]) < (llt)0 )
			--top;
		P[top++] = P[i];
	}
	return top;
}

void disp(point_t const P[], int n){
    for(int i=0;i<n;++i)printf("(%lld, %lld)\n",P[i].x,P[i].y);
    printf("\n");
}

/**
   凸多边形P上面挑4个点，使得四边形面积最大
   复杂度O(N^2)
   P: 逆时针的多边形点集
   n: 点的数量，必然大于3
   return: 四边形面积的2倍!!!
*/
llt max4Convex(point_t P[],int n){
    P[n] = P[0];//保证前后两点一样

    llt ans = 0;
    for(int i=0;i<n-2;++i){
        int a = i + 1;
        int b = i + 3;
        for(int j=i+2;j<n;++j){
            while(a+1!=j&&cross(P[i],P[a],P[j])<cross(P[i],P[a+1],P[j])){
                ++a;
            }
            while(b<n-1&&cross(P[i],P[j],P[b])<cross(P[i],P[j],P[b+1])){
                ++b;
            }
            ans = max(ans, cross(P[i],P[a],P[j])+cross(P[i],P[j],P[b]));
        }
    }
    return ans;
}

//从pos位置开始塞cnt个v到数组a中,返回插入后的长度
template<typename T>
int insertArray(T a[],int n,int pos,T const&v,int cnt=1){
    for(int i=n-1;i>=pos;--i) a[i+cnt] = a[i];
    for(int i=0;i<cnt;++i) a[pos+i] = v;
    return n + cnt;
}

int N;
point_t P[5000];
unordered_map<point_t,int,point_hash> Map;
unordered_map<point_t,int,point_hash>::iterator It;

int main(){
    //freopen("1.txt","r",stdin);
    int nofkase = getUnsigned();
    while(nofkase--){
        Map.clear();
        //输入
        N = getUnsigned();
        for(int i=0;i<N;++i){
            P[i].x = getUnsigned(), P[i].y = getUnsigned();
            if((It=Map.find(P[i]))==Map.end()){
                Map.insert(It, make_pair(P[i], 1));
            }else{
                ++It->second;
            }

        }

        //取唯一点
        int n = 0;
        for(It=Map.begin();It!=Map.end();++It) P[n++] = It->first;

        //不严格凸包
        n = Graham(P, n);

        //再把重复的点又塞回去
        for(int i=n-1;i>=0;--i){
            It = Map.find(P[i]);
            if(It->second>1){
                n = insertArray(P,n,i,It->first,It->second-1);
            }
        }

        //作答
        if(1==n||2==n){
            puts("0");
            continue;
        }
        if(3==n&&cross(P[0],P[1],P[2])==0){
            puts("0");
            continue;
        }
        if(3==n){//把剩下的点和这三点减一下
            llt tmp = -1;
            for(It=Map.begin();It!=Map.end();++It){
                if(It->first==P[0]||It->first==P[1]||It->first==P[2]) continue;

                llt a[3] = {
                    ABS(cross(It->first,P[0],P[1])),
                    ABS(cross(It->first,P[0],P[2])),
                    ABS(cross(It->first,P[2],P[1]))
                };
                sort(a,a+3);
                if(tmp==-1) tmp = a[0];
                else tmp = min(tmp, a[0]);
            }
            llt ans = cross(P[0],P[1],P[2]) - tmp;
            if(ans<0)throw runtime_error("XXXx");
            if(ans&1){
                printf("%lld.5\n",ans>>1);
            }else{
                printf("%lld\n",ans>>1);
            }
            continue;
        }

        llt ans = max4Convex(P,n);
        if(ans&1){
            printf("%lld.5\n",ans>>1);
        }else{
            printf("%lld\n",ans>>1);
        }
    }
    return 0;
}
