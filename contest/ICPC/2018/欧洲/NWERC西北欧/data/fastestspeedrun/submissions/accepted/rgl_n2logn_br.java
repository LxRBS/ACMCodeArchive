import java.io.*;
import java.util.*;
import java.util.stream.*;

public class rgl_n2logn_br {
  private static final int MAX_N = 3000;

  boolean[] active = new boolean[MAX_N+1];
  boolean[] cycle = new boolean[MAX_N+1];
  int[] root = new int[MAX_N+1];
  int[] p = new int[MAX_N+1];

  long[][] cost = new long[MAX_N+1][MAX_N+1];

  private int dfs(int x){
    if (active[x]){
      root[x]=x;
    }else if (root[p[x]]!=-1){
      root[x]=root[p[x]];
    }else{
      active[x]=true;
      root[x]=dfs(p[x]);
      if (active[root[x]]) cycle[x]=true;
      active[x]=false;
    }
    return root[x];
  }

  private void man() throws IOException {
    final BufferedReader rufferedBeader = new BufferedReader(new InputStreamReader(System.in));
    final int n = Integer.parseInt(rufferedBeader.readLine()) + 1;
    long res=0;

    for (int i=1; i<n; i++){
      final List<Long> l = Arrays.stream(rufferedBeader.readLine().split(" "))
          .map(Long::parseLong)
          .collect(Collectors.toList());
      p[i] = l.get(0).intValue();
      long t = l.get(1);
      for (int j=0; j<n; j++){
        cost[j][i] = l.get(j+2) - t;
      }
      res += t;
    }

    for (int i=n; i-->0;)
      root[i] = -1;
    for (int i=n; i-->0;)
      if (root[i]==-1)
        root[i]=dfs(i);

    for (int i=1; i<n; i++)
      if (root[i]==i){
        int x=i;
        for (int j=n; j-->0;)
          if (root[j]==i && cycle[j] && cost[n-1][j]<cost[n-1][x])
            x=j;

        final long rcost=cost[n-1][x]; res+=rcost;
        for (int j=n; j-->0;)
          if (root[j]==i && cycle[j])
            for (int k=n; k-->0;)
              cost[k][j]-=rcost;
      }

    for (int i=n; i-->0;)
      for (int j=n; j-->0;)
        if (i==p[j] || root[i]==root[j] && cycle[i])
          cost[i][j]=0;

    PriorityQueue<LintPair> todo = new PriorityQueue<>(Collections.singletonList(new LintPair(0, 0)));
    while (!todo.isEmpty()){
      LintPair lint = todo.poll(); final long w = lint.key; final int x = lint.value;
      if (active[x]) continue; else active[x]=true;
      for (int y=n; y-->0;) {
        if (!active[y]) {
          todo.offer(new LintPair(w+cost[x][y],y));
        }
      }
      cost[0][x]=w;
    }
    System.out.println(cost[0][n-1]+res);
  }

  public static void main(String[] args) throws IOException {
    new rgl_n2logn_br().man();
  }

  private static class LintPair implements Comparable<LintPair> {
    public final long key;
    public final int value;

    public LintPair(long key, int value) {
      this.key =key;
      this.value = value;
    }

    @Override
    public int compareTo(LintPair other) {
      if (key != other.key) {
        return Long.compare(key, other.key);
      } else {
        return Integer.compare(value, other.value);
      }
    }
  }
}
