import java.io.*;
import java.util.*;
import java.math.*;

public class Alex_PathCompression_BufferedReader{
	public static void main(String[] args) throws Exception {
		new Alex_PathCompression_BufferedReader().main();
	}

	// greatest common divisor
	long gcd(long a, long b){
		if(b != 0)return gcd(b, a % b);
		return a;
	}

	long x[];    // positions
	int next_[]; // next possible index after shooting on the current index and recharging
	int gNext[]; // next position to shoot at - for implementation of path compression
	boolean removed[]; // specifies whether this target is already eliminated

	int FUNCCALLS = 0; // just counts number of getNext-function calls - for debugging

	// getNext returns the id of the next target, which should be eliminated
	// it uses path compression
	int getNext(int n){
		++FUNCCALLS;
		if(removed[n]){
			return gNext[n] = getNext(gNext[n]);
		}
		return n;
	}

	int N, P, R;
	int main() throws Exception {
		BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
		String tmpin[] = reader.readLine().split(" ");
		N = Integer.parseInt(tmpin[0]);
		P = Integer.parseInt(tmpin[1]);
		R = Integer.parseInt(tmpin[2]);
		x = new long[N];
		next_ = new int[N];
		gNext = new int[N];
		removed = new boolean[N];
		tmpin = reader.readLine().split(" ");
		for(int i = 0; i < N; i++){
			x[i] = Integer.parseInt(tmpin[i]);
		}
		Arrays.sort(x);
		// calculate next possible position if recharging
		long toGo = (R) % P;
		boolean fliped = false;
		for(int i = 0; i < N; i++){
			next_[i] = (i>0?next_[i-1]:1);
			if(!fliped){
				while(next_[i] < N && x[next_[i]] < x[i] + toGo)++next_[i];
			}
			if(next_[i] == N){
				next_[i] = 0;
				fliped = true;
			}
			if(fliped) {
				while(x[next_[i]] + P < x[i] + toGo)++next_[i];
			}
		}
		long MINDIST = (1L<<60);
		long MAXDIST = 0;
		long AVERAGE = 0;
		long RUNS = 0;

		// try all possible starts once
		long laststart = x[(int)N-1] - P;
		for(int j = 0; j < N; j++){
			if(x[j] != laststart){ // calculate values for current start if not already done
				// initialize removed and gNext
				for(int i = 0; i < N; i++) removed[i] = false;
				for(int i = 0; i < N; i++) gNext[i] = (i+1);
				gNext[N-1] = 0;
				long DIST = R; // represents the time since this test run has started
				// DIST is initially R as it counts storing the initial bag

				int cur = j; // current index
				removed[cur] = true; // initial target is destroyed
				for(int i = 1; i < N; i++) {
					int n = next_[cur]; // next possible index after recharging
					n = getNext(n); // next possible index which is not already removed
					// calculate the waiting time to shoot at the next target 
					long dist = x[n] - x[cur];
					toGo = R - dist;
					dist += ((toGo + P - 1) / P) * P; // do not forget the full cycles such recharging is finished
					// update distance and remove next object
					DIST += dist;
					cur = n;
					removed[n] = true;
				}
				// update result values
				long mult = x[j] - laststart;
				MINDIST = Math.min(MINDIST, DIST);
				MAXDIST = Math.max(MAXDIST, DIST + mult - 1);
				AVERAGE += DIST * mult;
				AVERAGE += (mult * (mult - 1)) / 2;
				RUNS += mult;
				laststart = x[j];
			}
		}
		long gc = gcd(AVERAGE, RUNS);
		AVERAGE /= gc;
		RUNS /= gc;
		System.out.println(MINDIST);
		System.out.println(MAXDIST);
		System.out.println(AVERAGE + "/" + RUNS);
		return 0;
	}
}
