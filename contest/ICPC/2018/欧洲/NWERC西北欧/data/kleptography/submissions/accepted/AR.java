// Author Alexander Rass
import java.util.*;

public class AR{
    public static void main(String[] args){
        Scanner scan = new Scanner(System.in);
        int N = scan.nextInt(),M = scan.nextInt();
        String last_part = scan.next(), encrypted = scan.next();
        char[] plain = new char[M];
        for(int i = 0; i < N; i++)
            plain[M-N+i] = last_part.charAt(i);
        for(int i = M-N-1; i >= 0; i--)plain[i] = (char)((((encrypted.charAt(i+N) - 'a') - (plain[i+N] - 'a') + 26) % 26) + 'a');
        for(int i = 0; i < M; i++)System.out.print(plain[i]);
        System.out.println();
    }
}
