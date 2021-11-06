import java.io.*;
import java.util.*;
import java.util.stream.*;

// Direct translation of sl.cpp with Scanner instead of BufferedReader.

public class sl {
  private interface DepthFirstSearch {
    int dfs(int x);
  }

  public static void main(String[] args) throws IOException {
    final Scanner sc = new Scanner(System.in);
    final int n = sc.nextInt() + 1;
    long res=0;

    int[][] mat = new int[n][n];
    int[] par = new int[n];
    List<Integer>[] ch = new List[n];
    for (int i = 0; i < n; i++) {
      ch[i] = new ArrayList<Integer>();
    }
    ch[0].add(0);

    for (int i=1; i<n; i++){
      par[i] = sc.nextInt();
      int t = sc.nextInt();
      res += t;
      for (int j=0; j<n; j++){
        mat[i][j] = sc.nextInt() - t;
      }
      ch[par[i]].add(i);
    }

    int[] seen = new int[n];
    int[] best = new int[n];
    DepthFirstSearch dfs = new DepthFirstSearch() {
      @Override
      public int dfs(int x) {
        if (seen[x] == 2) return best[x];
        if (seen[x] == 1) return Integer.MAX_VALUE;
        seen[x] = 1;
        int r = x;
        for (int y : ch[x]) {
          r = Math.max(r, dfs(y));
        }
        seen[x] = 2;
        best[x] = r;
        return r;
      }
    };

    for (int start = 0; start < n; start++) {
      if (seen[start] != 0) {
        continue;
      }
      if (dfs.dfs(start) == Integer.MAX_VALUE) { // cycle
        int minc = Integer.MAX_VALUE;
        int i = start, r = 0;
        for (int z = 0; z == 0 || i != start; z++) {
          int prev = i;
          i = par[i];
          r = Math.max(r, i);
          for (int y : ch[i]) {
            if (y != prev) {
              r = Math.max(r, best[y]);
            }
          }
          minc = Math.min(minc, mat[i][n-1]);
        }
        res += minc;
        for (int z = 0; z == 0 || i != start; z++) {
          best[i] = r;
          for (int k = 0; k < n; k++) {
            mat[i][k] -= minc;
          }
          i = par[i];
        }
      }
    }

    long[] dp = new long[n];
    for (int i = 1; i < n; i++) {
      dp[i] = Long.MAX_VALUE;
    }
    for (int i = 0; i < n; i++) {
      if (dp[i] == Long.MAX_VALUE) {
        continue;
      }
      for (int j = 0; j < n; j++) {
        int y = best[j];
        if (y <= i) continue;
        dp[y] = Math.min(dp[y], dp[i] + mat[j][i]);
      }
    }

    System.out.println(res + dp[n-1]);
  }
}
