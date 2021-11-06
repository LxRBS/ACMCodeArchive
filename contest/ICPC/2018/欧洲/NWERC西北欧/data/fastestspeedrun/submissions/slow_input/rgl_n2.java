import java.util.*;

public class rgl_n2 {
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

  private void man(){
    final Scanner nanananaBatman = new Scanner(System.in);
    final int n = nanananaBatman.nextInt() + 1;
    long res=0;

    for (int i=1; i<n; i++){
      p[i] = nanananaBatman.nextInt();
      long t = nanananaBatman.nextLong();
      for (int j=0; j<n; j++){
        cost[j][i] = nanananaBatman.nextLong() - t;
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
        if (cost[i][j] < 0){
          throw new Error("Bad cost "+i+" "+j+": " + cost[i][j]);
        }

    for (int i=n; i-->0;)
      for (int j=n; j-->0;)
        if (i==p[j] || root[i]==root[j] && cycle[i])
          cost[i][j]=0;

    boolean[] visited=new boolean[n];
    for (int z=0; z<n; z++){
      int x=n;
      for (int i=n; i-->0;){
        if (!visited[i] && (x==n || cost[0][i]<cost[0][x])){
          x=i;
        }
      }
      visited[x]=true;
      for (int i=n; i-->0;){
        cost[0][i]=Math.min(cost[0][i],cost[0][x]+cost[x][i]);
      }
    }

    System.out.println(cost[0][n-1]+res);
  }

  public static void main(String[] args) {
    new rgl_n2().man();
  }
}
