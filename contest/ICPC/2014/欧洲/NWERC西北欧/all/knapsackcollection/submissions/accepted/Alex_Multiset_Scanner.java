import java.util.*;
import java.math.*;
import java.io.*;

public class Alex_Multiset_Scanner{
	public static void main(String[] args) throws Exception{
		new Alex_Multiset_Scanner().main();
	}
	// greatest common divisor
	long gcd(long a, long b){
		if(b != 0)return gcd(b, a % b);
		return a;
	}

	long x[]; // positions
	long N, P, R;
	int main() {
		Scanner scan = new Scanner(System.in);
		N = scan.nextInt();
		P = scan.nextInt();
		R = scan.nextInt();
		x = new long[(int)N];
		for(int i = 0; i < N; i++){
			x[i] = scan.nextInt();
		}
		Arrays.sort(x);
		long MINDIST = (1L<<60);
		long MAXDIST = 0;
		long AVERAGE = 0;
		long RUNS = 0;

		// try all possible starts
		long laststart = x[(int)N-1] - P;
		for(int j = 0; j < N; j ++){
			if(x[j] != laststart){ // calculate values for current start if not already done
				// initialize available targets
				TreeSet<Long> aims = new TreeSet<Long>();
				// insert all possible targets
				for(int i = 0; i < N; i++)aims.add((x[i] << 30) | i);
				aims.remove((x[j] << 30) | j); // initial target is destroyed
				long DIST = R; // represents the time since this test run has started
				// DIST is initially R as it counts storing the initial bag
				long cur = x[j]; // current position
				for(int i = 1; i < N; i++){
					// calculate next possible position
					long nco = cur + R;
					nco %= P;
					long n;
					Long tmpn = aims.ceiling(nco << 30);
					if(tmpn == null)tmpn = aims.first();
					n = tmpn >> 30;
					// calculate the waiting time to shoot at the next target 
					long dist = n - cur;
					long toGo = R - dist;
					dist += ((toGo + P - 1) / P) * P; // do not forget the full cycles such recharging is finished
					// update distance and remove next object
					DIST += dist;
					cur = n;
					aims.remove(tmpn);
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
