// author: Alexander Rass
import java.util.*;
import java.io.*;

public class Alex_O_N_log_N_BufferedReader{
	public static void main(String[] args) throws IOException{
		new Alex_O_N_log_N_BufferedReader().main();
	}

	int x[], y[];
	int percentage;
	class Pair{
		int a,b;
		Pair(int aa, int bb){a = aa; b = bb;}
		public int hashCode(){
			return a * 10007 + b;
		}
		public boolean equals(Object o){
			Pair op = (Pair) o;
			return a == op.a && b == op.b;
		}
	}

	// isOnLine returns true if the i-th point lies on the line represented by the index pair in "line"
	boolean isOnLine(int i, Pair line){
		int f = line.a, t = line.b;
		long dx = y[t] - y[f];
		long dy = x[f] - x[t];
		return dx * x[f] + dy * y[f] == dx * x[i] + dy * y[i];
	}

	// muchPointsOnLine returns true if on the line represented by the index pair "line"
	// contains at least M points in the index range f to t
	boolean muchPointsOnLine(Pair line , int f, int t, int M){
		for(int i = f; i < t; i++)if(isOnLine(i,line))--M;
		return M <= 0;
	}

	// sameLine returns true if the index pairs represent the same line
	boolean sameLine(Pair line1, Pair line2){
		return isOnLine(line1.a, line2) && isOnLine(line1.b, line2);
	}


	// find(f,t) returns all lines, which contains at least floor((t - f) / 2) points
	// from the index range f to t
	ArrayList<Pair> find(int f, int t){
		if(((t - f) / 2) * percentage  <= 2 * 200){ // if number of points is small all index pairs need to be analysed
			ArrayList<Pair> res = new ArrayList<Pair>();
			for(int i = f; i < t; i++)for(int j = f; j < i; j++){
				if(muchPointsOnLine(new Pair(j,i), f, t, (percentage * (t-f))/100)){
					res.add(new Pair(j,i));
				}
			}
			return res;
		}
		// else try all possible lines of the first and second half
		ArrayList<Pair > res = new ArrayList<Pair>(), a, b;
		int mid = f + (t-f) / 2;
		a = find(f,mid);
		b = find(mid,t);
		for(int i = 0; i < a.size(); i++)for(int j = 0; j < b.size(); j++){
			if(sameLine(a.get(i), b.get(j))){
				a.set(i, null);
				j = b.size();
				continue;
			}
		}
		a.addAll(b);
		for(Pair p: a){
			if(p == null)continue;
			if(muchPointsOnLine(p, f, t, (percentage * (t-f))/100)){
				res.add(p);
			}
		}
		return res;
	}

	// returns true if a line with ceil(N/2) points on it exists
	boolean findLine(){
		if(x.length * percentage <= 2 * 100)return true;
		ArrayList<Pair> lines = find(0, x.length);
		for(Pair it: lines){
			if(muchPointsOnLine(it, 0, x.length, (x.length * percentage + 99) / 100)){
				return true;
			}
		}
		return false;
	}


	int main() throws IOException {
		BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
		int N = Integer.parseInt(reader.readLine());
		percentage = Integer.parseInt(reader.readLine());
		x = new int [N];
		y = new int [N];
		for(int i = 0; i < N; i++){
			String[] arr = reader.readLine().split(" ");
			x[i] = Integer.parseInt(arr[0]);
			y[i] = Integer.parseInt(arr[1]);
		}
		if(findLine())System.out.print("possible\n");
		else System.out.print("impossible\n");
		return 0;

	}
}
