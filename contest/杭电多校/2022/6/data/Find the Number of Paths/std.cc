#include <bits/stdc++.h>
typedef unsigned long long ull;
typedef long long ll;
using namespace std;
const int N=4e5+5,mod=998244353,G=3,Gi=332748118;
int inv[N],f[N],invf[N];
namespace Polynomial 
{
    using Poly = std::vector<int>;
    constexpr int P(998244353),G(3);
    inline void inc(int &x, int y) { (x+=y)>=P?x-=P:0;}
    inline int sum(int x,int y){return x+y>=P?x+y-P:x+y;}
    inline int sub(int x,int y){return x<y?x-y+P:x-y;}
    inline int fpow(int x,int k=P-2)
    {
        int r=1;
        for(;k;k>>=1,x=1ll*x*x%P)
            if(k&1) r=1ll*r*x%P;
        return r;
    }
    std::vector<int> w;
    void getOmega(int k)
    {
        w.resize(k);
        w[0]=1;
        int base=fpow(G,(P-1)/(k << 1));
        for(int i=1;i<k;i++) w[i]=1LL*w[i-1]*base%P;
    }
    void dft(int *a,int n) 
    {
        assert((n&n-1)==0);
        for(int k=n>>1;k;k>>=1) 
        {
            getOmega(k);
            for(int i=0;i<n;i+=k<<1) 
                for (int j=0;j<k;j++) 
                {
                    int y=a[i+j+k];
                    a[i+j+k]=(1ll*a[i+j]-y+P)*w[j]%P;
                    inc(a[i+j],y);
                }
        }
    }
    void dft(Poly &a) {dft(a.data(),a.size());}
    void idft(int *a,int n) 
    {
        assert((n&n-1)==0);
        for (int k=1;k<n;k<<=1) 
        {
            getOmega(k);
            for(int i=0;i<n;i+=k<<1)
            for(int j=0;j<k;j++) 
            {
                int x=a[i+j],y=1ll*a[i+j+k]*w[j]%P;
                a[i+j]=sum(x,y),a[i+j+k]=sub(x,y);
            }
        }
        for (int i=0,inv=P-(P-1)/n;i<n;i++)
            a[i]=1ll*a[i]*inv%P;
        std::reverse(a+1,a+n);
    }
    void idft(Poly &a) {idft(a.data(), a.size());}
    Poly operator*(Poly a, Poly b) 
    {
        int len=a.size()+b.size()-1;
        if (a.size()<=8||b.size()<=8) 
        {
            Poly c(len);
            for (size_t i=0;i<a.size();i++)
            for (size_t j=0;j<b.size();j++)
                c[i+j]=(c[i+j]+1ll*a[i]*b[j])%P;
            return c;
        }
        int n=1<<std::__lg(len-1)+1;
        a.resize(n),b.resize(n);
        dft(a),dft(b);
        for(int i=0;i<n;i++) a[i]=1ll*a[i]*b[i]%P;
        idft(a);
        a.resize(len);
        return a;
    }
    Poly operator+(Poly a, Poly b) 
    {
        a.resize(std::max(a.size(),b.size()));
        for (int i=0;i<b.size();i++) inc(a[i],b[i]);
        return a;
    }
    Poly operator-(Poly a, Poly b) 
    {
        a.resize(std::max(a.size(), b.size()));
        for (int i=0;i<b.size();i++) inc(a[i],P-b[i]);
        return a;
    }
    Poly shift(Poly a, int x) 
    {
        if(x<0) 
            return -x>a.size()?Poly():Poly(a.begin()-x,a.end());
        a.insert(a.begin(),x,0);
        return a;
    }
    Poly polyInv(Poly &a,int n)
    {
        if(n==1) {Poly b(1);b[0]=fpow(a[0],P-2);return b;}
        Poly b=polyInv(a,(n+1)/2);
        Poly c=Poly(a.begin(),a.begin()+std::min(n,int(a.size())));
        int len=1;
        while(len<n<<1) len<<=1;
        b.resize(len);c.resize(len);
        dft(b);dft(c);
        for(int i=0;i<len;i++) b[i]=(2+P-1ll*b[i]*c[i]%P)%P*b[i]%P;
        idft(b);
        b.resize(n);
        return b;
    }
    void Derivation(Poly &a)
    {
        if(a.size()==0) return;
        for(int i=0;i+1<a.size();i++)
            a[i]=1ll*a[i+1]*(i+1)%P;
        a.pop_back();
    }
    void Integral(Poly &a)
    {
        for(int i=0;i<a.size();i++)
            a[i]=1ll*a[i]*inv[i+1]%P;
        a.insert(a.begin(),0);
    }
    void polyIn(Poly &a,int n)
    {
        Poly b=polyInv(a,n);
        Derivation(a);
        a.resize(n);
        a=a*b;
        Integral(a);
        a.resize(n);
    }
    Poly polyExp(Poly &a,int n)
    {
        if(n==1){Poly b;b.push_back(1);return b;}
        Poly b=polyExp(a,(n+1)/2);
        Poly c=b;
        polyIn(b,n);
        if(a.size()<b.size()) a.resize(b.size());
        for(int i=0;i<b.size();i++) b[i]=((i==0)+P-b[i]+a[i])%P;
        b=b*c;
        b.resize(n);
        return b;
    }
}
using namespace Polynomial;
void init()
{
  f[0]=f[1]=invf[0]=invf[1]=inv[1]=1;
  for(int i=2;i<N;++i)
  {
    f[i]=1ll*f[i-1]*i%mod;
    inv[i]=1ll*(mod-mod/i)*inv[mod%i]%mod;
    invf[i]=1ll*invf[i-1]*inv[i]%mod;
  }
}
int main()
{
  init();
  int t;scanf("%d",&t);
  while(t--)
  {
      int n,k;
      scanf("%d%d",&n,&k);
      Poly g(n+1);
      for(int i=2;i<=n;++i)
      {
        scanf("%d",&g[i]);
        g[i]=1ll*g[i]*inv[i]%mod;
      }
      g=polyExp(g,k+1);
      Poly h=polyInv(g,n);
      g.insert(g.begin(),n-1,0);
      for(int i=k;i<n+k;++i)
        g[i-k]=1ll*g[i]*f[i]%mod*invf[i-k]%mod;
      g.resize(n);
      g=g*h;
      for(int i=n-1;i>=0;--i)
        printf(i==0?"%d\n":"%d ",g[i]);
  }
}