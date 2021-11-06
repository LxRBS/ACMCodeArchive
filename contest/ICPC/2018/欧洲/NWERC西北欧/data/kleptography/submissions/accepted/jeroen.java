import java.util.*;
import java.io.*;

public class jeroen
{
	public static void main(String[] args) throws Exception
	{
		// Read input
		BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
		in.readLine();
		String last = in.readLine();
		String enc = in.readLine();

		// Fill in known part
		char[] solution = new char[enc.length()];
		for(int i = 0; i < last.length(); i++)
			solution[enc.length() - last.length() + i] = last.charAt(i);

		// Work backwards
		for(int i = enc.length() - last.length() - 1; i >= 0; i--)
			solution[i] = (char)('a' + (26 + (enc.charAt(i+last.length())-'a') - (solution[i+last.length()]-'a')) % 26);

		System.out.println(new String(solution));
	}
}
