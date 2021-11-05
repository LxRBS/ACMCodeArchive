// author: Alexander Rass
import java.util.*;
import java.io.*;

public class Alex_O_N_BufferedReader{
	public static void main(String args[]) throws IOException{
		new Alex_O_N_BufferedReader().main();
	}

	BufferedReader reader;
	int x[], y[];

	int gcd(int a, int b){
		if(b == 0)return a;
		return gcd(b, a % b);
	}

	// memoization of sampled gradients
	int S = 0; // number of already sampled gradients
	HashMap<Pair,Integer > gradients;
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
	void insertGradient(int id1, int id2){
		// make gradient unique
		int dx = x[id1] - x[id2];
		int dy = y[id1] - y[id2];
		int g = gcd(Math.abs(dx), Math.abs(dy));
		dx /= g;
		dy /= g;
		if(dx < 0 || (dx == 0 && dy < 0)){
			dx *= -1;
			dy *= -1;
		}
		// memoization of gradient
		Pair p = new Pair(dx,dy);
		if(gradients.containsKey(p))gradients.put(p, gradients.get(p) + 1);
		else gradients.put(p, 1);
		S++;
	}

	int main() throws IOException {
		BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
		gradients = new HashMap<Pair,Integer>();
		int N = Integer.parseInt(reader.readLine());
		int p = Integer.parseInt(reader.readLine());
		if(2 * 100 >= N * p){
			System.out.print("possible\n");
			return 0;
		}
		x = new int [N];
		y = new int [N];
		for(int i = 0; i < N; i++){
			String[] arr = reader.readLine().split(" ");
			x[i] = Integer.parseInt(arr[0]);
			y[i] = Integer.parseInt(arr[1]);
		}
		if(N * (long)N < 10000){ // sample all gradients if N is small
			for(int i = 0; i < N; i++){
				for(int j = 0; j < i; j++){
					insertGradient(i,j);
				}
			}
		} else { // sample 10^4 gradients if N is large
			Random rand = new Random(1234567899876543L);
			for(int i = 0; i < 10000; i++){
				int a = rand.nextInt(N);
				int b = rand.nextInt(N);
				while(b == a)b = rand.nextInt(N);
				insertGradient(a,b);
			}
		}
		ArrayList<Integer> numgra = new ArrayList<Integer>();
		for(Pair it: gradients.keySet())numgra.add(gradients.get(it));
		int numgra2[] = new int[numgra.size()];
		for(int i = 0; i < numgra.size(); i++)numgra2[i] = numgra.get(i);
		Arrays.sort(numgra2);
		int limit = numgra2[Math.max(numgra2.length - 20, 0)];
		int DONE = 0;
		for(Pair it: gradients.keySet()){
			int value = gradients.get(it);
			if(value < limit)continue;
			if(value == limit && DONE >= 20)continue;
			DONE++;
			{

				HashMap<Long, Integer> t = new HashMap<Long, Integer>();
				// generate orthogonal vector to gradient
				long dx = -(it.b);
				long dy = it.a;
				// scalar product with orthogonal vector results in value which identifies
				// the position of the line
				for(int i = 0; i < N; i++){
					long scal = dx * x[i] + dy * y[i];
					if(t.containsKey(scal))t.put(scal, t.get(scal)+1);
					else t.put(scal, 1);
				}
				for(Long l: t.keySet()){
					if(t.get(l) * 100 >= N * p){
						System.out.print("possible\n");
						return 0;
					}
				}
			}
		}
		System.out.print("impossible\n");
		return 0;
	}
}
