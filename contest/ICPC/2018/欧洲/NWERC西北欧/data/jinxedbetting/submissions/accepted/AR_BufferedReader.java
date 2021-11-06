import java.io.*;
import java.util.*;

public class AR_BufferedReader{
static final int MAXN = (int)1.1e6;
static long v[];

public static void main(String[] args) throws Exception{
    BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
    int N = Integer.parseInt(reader.readLine());
    v = new long[N];
    String input[] = reader.readLine().split(" ");
    for(int i = 0; i < N; i ++)v[i] = Long.parseLong(input[i]);
    Arrays.sort(v);
    for(int i= 0; i < N-i-1; i++){
        long tmp = v[i];
        v[i] = v[N-i-1];
        v[N-i-1] = tmp;
    }
    long dif = v[0] - v[1] + 1;
    int active = 1;
    long slowadd = v[1] - v[2];
    long res = v[1] - v[2];
    while(true){
        while(active+1 < N && v[active + 1] + slowadd >= v[1])++active;
        long S = 0;
        while((((long)1)<<(S+1)) <= active)++S;
        long T = (dif - 1) / S;
        if(active+1 < N)T = Math.min(T, v[1] - (v[active + 1] + slowadd));
        if(T == 0){
            System.out.println(res + dif - 1);
            return;
        }
        res += (S + 1) * T;
        slowadd += T;
        dif -= S * T;
    }
}
}
