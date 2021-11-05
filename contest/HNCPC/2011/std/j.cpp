#include<cmath>
#include<cstring>
#include<cstdio>
#include<cassert>
#include<algorithm>
#include <ctime> 

#define rept(i,n) for(int i = 0; i < (n); i++)

#define PI 3.14159265358979323846264338327950288

using namespace std;

struct pdd
{
   double x,y;
   pdd():x(0),y(0) {}
   pdd(double _x,double _y):x(_x),y(_y) {}
};
inline pdd operator +(const pdd &a,const pdd &b)
{
   return pdd(a.x+b.x,a.y+b.y);
}
inline pdd operator -(const pdd &a,const pdd &b)
{
   return pdd(a.x-b.x,a.y-b.y);
}
inline pdd operator *(const pdd &a,const pdd &b)
{
   return pdd(a.x*b.x-a.y*b.y,a.x*b.y+a.y*b.x);
}
inline pdd operator /(const pdd &a,const double &b)
{
   return pdd(a.x/b,a.y/b);
}
inline pdd conj(const pdd &a)
{
   return pdd(a.x,-a.y);
}


const int maxn = 300000;
struct FFT {
  int n;
  int SN;
  int rv[1<<18];
  pdd w[1<<18];

  void fft(pdd *a, bool inv)
  {
     int cc=0;
     rept(i,30) if (n&1<<i) cc=i;
     if (cc!=SN)
     {
       SN=cc;
       rv[0]=0; rv[1]=1;
       for(int st = 1; st <= SN-1; st++)
       {
           int k=1<<st;
           rept(i,k)
           {
               rv[i+(1<<st)]=rv[i]*2+1;
               rv[i]*=2;
           }
       }
       rept(i,1<<SN) w[i]=pdd(cos(2.0*PI*i/n),sin(2.0*PI*i/n));
     }
     rept(i,n) if (rv[i]<=i) swap(a[i],a[rv[i]]);
     for (int st=2;st<=n;st*=2)
     {
       int d=n/st,o=st/2;
       for (int i=0;i<n;i+=st)
       {
           for (int j=0;j<o;++j)
           {
               pdd u=a[i+j],v=a[i+j+o]*(inv?conj(w[j*d]):w[j*d]);
               a[i+j]=u+v;
               a[i+j+o]=u-v;
           }
       }
     }
     if (inv) rept(i,n) a[i]=a[i]/n;
  }

  void Multi(long long* A, int NA, long long* B, int NB, long long* C, pdd* tA, pdd* tB) {
    SN = -1;
    n = 1;
    while(n < NA + NB) n *= 2;
    n *= 2;

    for(int i = 0; i < n; i++) {
      tA[i] = (i < NA ? pdd(A[i], 0) : pdd(0, 0));
      tB[i] = (i < NB ? pdd(B[i], 0) : pdd(0, 0));
    }

    fft(tA, 0);
    fft(tB, 0);
    for(int i = 0; i < n; i++)
      tA[i] = tA[i] * tB[i];
    fft(tA, 1);

    for(int i = 0; i < n; i++)
      C[i] = (long long)(tA[i].x + 0.5);
  }
};

FFT fft;

int vis[100000];

void sieve(int n) {
  int m = (int)sqrt(n+0.5);
  memset(vis, 0, sizeof(vis));
  for(int i = 2; i <= m; i++) if(!vis[i])
    for(int j = i*i; j <= n; j+=i) vis[j] = 1;
}

long long poly[7][maxn];
pdd tA[maxn], tB[maxn];

int getSuit(char s) {
  if(s == 'S') return 0;
  if(s == 'H') return 1;
  if(s == 'C') return 2;
  if(s == 'D') return 3;
}

int main() {
  int a, p, c;
	
  double cl = clock();
	
  sieve(50000);
  while(scanf("%d%d%d", &a, &p, &c) == 3 && p) {
    for(int i = 0; i < p; i++) {
      int v = 0;
      if(i >= 4 && vis[i]) v = 1;
      poly[0][i] = poly[1][i] = poly[2][i] = poly[3][i] = v;
    }
    for(int i = 0; i < c; i++) {
      char card[9];
      scanf("%s", card);
      int len = strlen(card);
      int suit = getSuit(card[len-1]);
      int rank;
      card[len-1] = '\0';
      sscanf(card, "%d", &rank);
      assert(rank >= 4 && vis[rank]);
      poly[suit][rank] = 0;
    }
    fft.Multi(poly[0], p, poly[1], p, poly[4], tA, tB);
    fft.Multi(poly[2], p, poly[3], p, poly[5], tA, tB);
    fft.Multi(poly[4], p, poly[5], p, poly[6], tA, tB);
    for(int i = a; i <= p; i++)
      printf("%d\n", poly[6][i] % 1000000); // linuxÏÂ¸Ä³É%lld
    printf("\n");
  }
  
  cl = clock() - cl;
  fprintf(stderr, "Total Execution Time = %lf seconds\n", cl / CLOCKS_PER_SEC);
  
  return 0;
}
