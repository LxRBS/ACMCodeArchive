import java.util.*;
import java.io.*;

public class check_tree
{
	public static void main(String[] args) throws Exception
	{
		BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
		int n = Integer.valueOf(in.readLine());
		UnionFind uf = new UnionFind(n);
		for(int i = 0; i < n - 1; i++) {
			String[] ps = in.readLine().split(" ");
			int a = Integer.valueOf(ps[0]) - 1;
			int b = Integer.valueOf(ps[1]) - 1;
			if(uf.get(a) == uf.get(b)) throw new Exception("Cycle found");
			uf.join(a, b);
		}

		for(int i = 1; i < n; i++)
			if(uf.get(i) != uf.get(0))
				throw new Exception("Points " + (i+1) + " and 1 not connected");

		// All right!
		System.exit(42);
	}
}


class UnionFind {
	int[] mapping;
	
	public UnionFind(int N) {
		mapping = new int[N];
		for(int i = 0; i < N; i++)
			mapping[i] = i;
	}
	
	public int get(int i) {
		if(mapping[i] == i) return i;
		return mapping[i] = get(mapping[i]);
	}
	
	public void join(int i, int j) {
		mapping[get(i)] = get(j);
	}
}
