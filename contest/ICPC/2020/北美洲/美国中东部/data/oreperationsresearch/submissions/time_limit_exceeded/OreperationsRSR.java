import java.util.*;
import java.io.*;

class Pair {
  public int a,b;
  public Pair(int a, int b) {
    this.a = a; this.b = b;
  }
  // In order to be have a hash set of pairs, we need to redefine the
  // hash code and the method for resolving collisions:
  @Override
  public int hashCode() {
    long u = a;
    long v = b;
    return (int)(u^(v>>>32));
  }

  @Override
  public boolean equals(Object o) {
    Pair other = (Pair)o;
    return (this.a == other.a && this.b == other.b);
  }

}

public class OreperationsRSR {
  public static int r,s,n;
  public static long[] a,b,c;
  public static long asum,bsum;
  public static long t1,t2,g;
  public static long am[], bm[];

  public static void main(String[] args) throws IOException {
    BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
    StringTokenizer st = new StringTokenizer(in.readLine());
    r = Integer.parseInt(st.nextToken());
    s = Integer.parseInt(st.nextToken());
    n = Integer.parseInt(st.nextToken());
    a = Arrays.stream(in.readLine().split(" ")).mapToLong(x->Long.parseLong(x)).
        toArray();
    b = Arrays.stream(in.readLine().split(" ")).mapToLong(x->Long.parseLong(x)).
        toArray();
    c = Arrays.stream(in.readLine().split(" ")).mapToLong(x->Long.parseLong(x)).
        toArray();
    asum = Arrays.stream(a).sum();
    bsum = Arrays.stream(b).sum();
    long[] ginfo = gcd(asum,bsum);
    g = ginfo[0];
    t1 = ginfo[1];
    t2 = ginfo[2];
    am = new long[2*r+1];
    bm = new long[2*s+1];
    for (int i = 0; i < 2*r; i++) {
      am[i+1] = am[i]+a[i%r];
    }
    for (int i = 0; i < 2*s; i++) {
      bm[i+1] = bm[i]+b[i%s];
    }

    // find all places we could end up after filling first car, assuming
    // both A and B carts are 0 to begin with:
    HashSet<Pair> next = allposs(0,0,0);

    // now use element of 'next' as all possible starting points for
    // the next car, and so on until all cars are filled or next is
    // empty:
    for(int i = 1; i < n && !next.isEmpty(); i++) {
      HashSet<Pair> old = next;
      next = new HashSet<Pair>();
      for (Pair p: old) {
        next.addAll(allposs(i,p.a,p.b));
      }
    }
    if (next.isEmpty()) {
      System.out.println("no");
    } else {
      System.out.println("yes");
    }
  }

  public static HashSet<Pair> allposs(int ci,int ai, int bi) {
    HashSet<Pair> ans = new HashSet<Pair>();
    for (int i = ai; i <= ai+r; i++) {
      long ap = am[i]-am[ai];
      if (ap > c[ci])
        break;
      for (int j = bi; j <= bi+s; j++) {
        long bp = bm[j]-bm[bi];
        if (ap+bp > c[ci])
          break;
        if ((c[ci]-ap-bp)%g == 0) {
          long temp = c[ci]-ap-bp;
          long mult = temp/g;
          long mt1 = mult*t1;
          long mt2 = mult*t2;
          if (t1 < 0) {
            long k = (long)Math.ceil((-mt1)*1.0/(bsum/g));
            if (mt2 >= k*asum/g) {
              ans.add(new Pair(i%r,j%s));
            }
          } else if (t2 < 0) {
            long k = (long)Math.ceil((-mt2)*1.0/(asum/g));
            if (mt1 >= k*bsum/g) {
              ans.add(new Pair(i%r,j%s));
            }
          } else {
            ans.add(new Pair(i%r,j%s));
          }
        }
      }
    }
    return ans;
  }


  // Stolen straight from Wikipedia: Extended Euclidean alg
  public static long[] gcd(long a, long b) {
    long s = 0;    long old_s = 1;
    long r = b;    long old_r = a;
    while (r != 0) {
        long quotient = old_r / r;
        long temp = r;
        r = old_r - quotient*r;
        old_r = temp;
        temp = s;
        s = old_s - quotient*s;
        old_s = temp;
      }
    long bezout_t;
    if (b != 0) {
        bezout_t = (old_r - old_s * a)/ b;
    } else {
        bezout_t = 0;
      }
    return  new long[]{old_r,old_s,bezout_t};
  }
}
