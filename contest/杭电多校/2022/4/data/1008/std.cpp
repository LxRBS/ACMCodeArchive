#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
#include<cstdio>
#include<cmath>
#include<set>
#include<vector>
using namespace std;
using namespace __gnu_pbds;

int sgn(long long x) {return x>0?1:(x==0?0:-1);}
struct Point{
    int x,y;
    Point() : x(0),y(0) {}
    Point (int x,int y) : x(x),y(y) {}
    friend Point operator + (Point p1,Point p2) {
        return Point(p1.x+p2.x,p1.y+p2.y);
    }
    friend Point operator - (Point p1,Point p2) {
        return Point(p1.x-p2.x,p1.y-p2.y);
    }
    friend long long operator ^ (Point u,Point v) {
        return (1ll*u.x*v.y-1ll*u.y*v.x);
    }
    friend long long operator * (Point u,Point v) {
        return (1ll*u.x*v.x+1ll*u.y*v.y);
    }
    friend bool operator == (Point p1,Point p2) {
        return p1.x==p2.x && p1.y==p2.y;
    }
    friend bool operator != (Point p1,Point p2) {
        return p1.x!=p2.x || p1.y!=p2.y;
    }
    friend bool operator < (Point p1,Point p2);
    long long mod2() {return (1ll*x*x+1ll*y*y);}
}O(0,0);
bool operator <(Point p1,Point p2) {
    Point v1 = (p1-O), v2 = (p2-O);
    int tmp = sgn(v1^v2);
    if (tmp==0) return v1.mod2() < v2.mod2();
    return tmp>0;
}

const long double pi = acosl(-1);
struct Fraction {
    int y,x;
    Fraction (Point p) : y(p.y),x(p.x) {}
    friend bool operator < (Fraction f1,Fraction f2) {
        long double atan_f1 = atan2(f1.y,f1.x)-pi/2;
        long double atan_f2 = atan2(f2.y,f2.x)-pi/2;
        if (atan_f1 <= -pi+1e-3) atan_f1+=2*pi;
        if (atan_f2 <= -pi+1e-3) atan_f2+=2*pi;
        if (fabsl(atan_f1-atan_f2)>1e-3) return atan_f1<atan_f2;
        return 1ll*f1.x*f2.y-1ll*f1.y*f2.x>0;   
    }
    friend bool operator == (Fraction f1,Fraction f2) {
        long double atan_f1 = atan2(f1.y,f1.x);
        long double atan_f2 = atan2(f2.y,f2.x);
        if (fabsl(atan_f1-atan_f2)>1e-3) return false;
        return 1ll*f1.x*f2.y-1ll*f1.y*f2.x==0;   
    }  
};

template<typename T>
struct CircleSet {
    using iter = typename set<T>::iterator;
    set<T> st;
    iter end;

    iter add (iter it) const {
        ++it;
        if (it==st.end()) return st.begin();
        return it;
    }
    iter dec (iter it) const {
        if (it==st.begin()) return end;
        return --it;
    }
    iter upper_bound(const T &p) const {
        auto it = st.upper_bound(p);
        if (it == st.end()) return st.begin();
        return it;
    }
    int size() {
        return st.size();
    }
    bool count(const T &p) {
        return (st.find(p)!=st.end());
    }
    iter deleteAndGetLast(iter lst) {
        auto tmp = dec(lst);
        if (lst==end) end = dec(end);
        st.erase(lst);
        return tmp;
    }
    iter deleteAndGetNext(iter nxt) {
        auto tmp = add(nxt);
        if (nxt==end) end = dec(end);
        st.erase(nxt);
        return tmp;
    }
    void insert(const T &p) {
        st.insert(p);
        if (st.size()==1) {
            end=st.begin();
        }else{
            while (add(end)!=st.begin()) ++end;
        }
        
    }
    T getBegin() {
        return *st.begin();
    }
    T getEnd() {
        return *end;
    }
    void clear() {
    	st.clear();
    	end = st.end();
	}
};

struct Convex{
    CircleSet<Point> cset;
    bool isinConvex(const Point &p) const
    {
        auto nxt = cset.upper_bound(p);
        auto lst = cset.dec(nxt);
        return (((*nxt-*lst)^(p-*lst))>0) || 
               (((*nxt-*lst)^(p-*lst))==0 && ((*nxt-*lst)*(p-*lst))>=0);
    }

    Point Segment(Point p1,Point p2){return p2-p1;}
    bool isdone=false;
    void addConvex(const Point &p,vector<Point> &deleteList,vector<Point> &createList)
    {
        if (cset.count(p)) return;
    
        if (cset.size()>=2) {
            if (isinConvex(p)) return;   
            auto nxt = cset.upper_bound(p);
            auto lst = cset.dec(nxt);
            deleteList.push_back(Segment(*lst,*nxt));
            while (cset.size()>=2 && ( (*cset.dec(lst)-*lst)^(p-*lst) )>=0) {
                deleteList.push_back(Segment(*cset.dec(lst),*lst));
                lst = cset.deleteAndGetLast(lst);
            } 
            while (cset.size()>=2 && ( (*cset.add(nxt)-*nxt)^(p-*nxt) )<=0) {
                deleteList.push_back(Segment(*nxt,*cset.add(nxt)));
                nxt = cset.deleteAndGetNext(nxt);
            }
            createList.push_back(Segment(*lst,p));
            createList.push_back(Segment(p,*nxt));
        }
        cset.insert(p);
        if (isdone==false && cset.size()==2) {
            createList.push_back(Segment(cset.getBegin(),cset.getEnd()));
            createList.push_back(Segment(cset.getEnd(),cset.getBegin()));
            isdone=true;
        }
    }
    void clear(){
    	cset.clear();
    	isdone = false;
	}
}convex[100005];

#define Lower_convex_shell 0
#define Upper_convex_shell 1
struct BalanceTree{
    Point startp;
    int type;
    struct Node{
        Point delta;
        Fraction f;
        int id;
        Node (Point p) : delta(p),f(delta),id(0) {}
        friend bool operator < (Node a1,Node a2) {
            if (a1.f==a2.f && a1.delta.x==a2.delta.x) return a1.id<a2.id;
            if (a1.f==a2.f) return a1.delta.x<a2.delta.x;
            return a1.f<a2.f;
        }
    };

    template<class Node_CItr,class Node_Itr,class Cmp_Fn,class _alloc> 
    struct my_node_update
    {
        virtual Node_CItr node_begin() const =0;
        virtual Node_CItr node_end() const =0;
        typedef Point metadata_type;

        void operator()(Node_Itr it, Node_CItr end_it)
        {
            Node_Itr l=it.get_l_child();
            Node_Itr r=it.get_r_child();
            Point left,right;
            if(l!=end_it) left=l.get_metadata();
            if(r!=end_it) right=r.get_metadata();
            Point cur(left.x+right.x+(*it)->delta.x,left.y+right.y+(*it)->delta.y);
            const_cast<Point&> (it.get_metadata())=cur;
        }
        bool my_isin(Point p,BalanceTree *bt) 
        {
            auto cmp = [&] (int x,int y) {
                if (bt->type==Lower_convex_shell) return x<y;
                else return x>y;
            };
            auto cmp_eq = [&] (int x,int y) {
                if (bt->type==Lower_convex_shell) return x>=y;
                else return x<=y;
            };
            auto checkin = [] (Point p1,Point p2,Point p) {
                return ((p2-p1)^(p-p1))>=0;
            };
            int delta_x = p.x - bt->startp.x;
            Point sump = bt->startp;
            if (cmp(delta_x,0)) return false;
            Node_CItr it=node_begin();
            while (it!=node_end()) {
                Node_CItr l=it.get_l_child();
                Node_CItr r=it.get_r_child();

                if (l!=node_end() && cmp_eq(l.get_metadata().x,delta_x)) {
                    it = l;
                }else{
                    Point lsump(0,0);
                    if (l!=node_end()) lsump = l.get_metadata();
                    
                    if (cmp_eq(lsump.x+(*it)->delta.x,delta_x)) {
                        Point from_p = sump + lsump;
                        Point to_p = from_p + Point((*it)->delta.x,(*it)->delta.y);
                        return checkin(from_p,to_p,p);
                    }else{
                        if (r!=node_end()) {
                            delta_x -= lsump.x+(*it)->delta.x;
                            sump = sump + lsump + Point((*it)->delta.x,(*it)->delta.y);
                            it = r;
                        }else{
                            return false;
                        }
                    }
                }
            }
            return false;
        }
    };    
    Point endp;

    map<Node,int> map_l,map_r;
    tree<Node,null_type,less<Node>,rb_tree_tag,my_node_update> tr;
    void del(Point sv) {
        endp=endp-sv;
        Node node(sv);
        node.id = map_l[node]++;
        tr.erase(node);
    }
    void add(Point sv) {
        endp=endp+sv;
        Node node(sv);
        node.id = map_r[node]++;
        tr.insert(node);
    }
    bool query(Point p) {
        return tr.my_isin(p,this);
    }
    void clear() {
    	map_l.clear();
		map_r.clear();
		tr.clear();
	}
}bt_l,bt_u;

void work(int i,Point p){
    vector<Point> deleteList,createList;
    convex[i].addConvex(p,deleteList,createList);
    for (auto s : deleteList) {
        if (s.x>=0 && s.y>=0) bt_l.del(s);
        else bt_u.del(s);
    }
    for (auto s : createList) {
        if (s.x>=0 && s.y>=0) bt_l.add(s);
        else bt_u.add(s);
    }
}

void solve() 
{
    int n,q;
    scanf("%d%d",&n,&q);
    bt_l.type=Lower_convex_shell;
    bt_u.type=Upper_convex_shell;  
    bt_l.startp=bt_u.startp=Point(0,0); 
    bt_l.endp=bt_u.endp=Point(0,0); 

    for (int i=1;i<=n;i++) {
        static int p[100005],m[100005],k;
        scanf("%d",&k);
        for (int j=1;j<=k;j++) scanf("%d",&p[j]);
        for (int j=1;j<=k;j++) scanf("%d",&m[j]);
        work(i,Point(0,0));
        for (int j=1;j<=k;j++) {
            work(i,Point(p[j],m[j]));
        }
    }
    while (q--) {
        int hpp,hpm,pi,mi,sr;
        scanf("%d%d%d%d%d",&hpp,&hpm,&pi,&mi,&sr);
        Point p = Point(hpp,hpm);
        bt_u.startp = bt_l.endp;
        puts((bt_l.query(p)&bt_u.query(p))?"YES":"NO");
        work(sr,Point(pi,mi));
    }
    bt_l.clear();
    bt_u.clear();
    for (int i=1;i<=n;i++){
    	convex[i].clear();
    }
}

int main()
{
	freopen("test.in","r",stdin);
	freopen("test.out","w",stdout);
	int t;
	scanf("%d",&t);
	while (t--) solve();
}


