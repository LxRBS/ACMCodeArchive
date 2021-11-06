import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.regex.Matcher;
import java.util.regex.Pattern;
import java.lang.Math;

public class fastest {
	public static void main(String[] args) {
		BufferedReader br;
		try {
			br = new BufferedReader(new InputStreamReader(System.in));
			String encoded = br.readLine();


			int current = 0;
			int val = 0;
			StringBuilder tmp = new StringBuilder();
			StringBuilder msg = new StringBuilder();
			boolean isBad = false;
			for (int i = 0; i < encoded.length(); i++) {
				char c = encoded.charAt(i);
				if (!isBad && (c == 'u' || c == 'm')) {
					tmp.append(c);
				} else if (Character.isLetter(c) || Character.isDigit(c)) {
                    tmp.setLength(0);
					isBad = true;
				} else if (c == ' ') {
                    if (!isBad) {
                        for (int j = 0; j < tmp.length(); j++) {
                            char k = tmp.charAt(j);
                            short v = k == 'u'? (short)1 : (short)0;
                            val = (val << 1) | v;
                            if (current % 7 == 6) {
                                msg.append((char)val);
                                val = 0;
                            }
                            current++;
                        }
                        tmp.setLength(0);
                    }
                    isBad = false;
				}
			}

			if (!isBad && tmp.length() > 0) { //still some stuff in tmp
				for (int j = 0; j < tmp.length(); j++) {
					char k = tmp.charAt(j);
					short v = k == 'u'? (short)1 : (short)0;
					val = (val << 1) | v;
					if (current % 7 == 6) {
						msg.append((char)val);
						val = 0;
					}
					current++;
				}
			}
			tmp.setLength(0);


						
			System.out.println(msg.toString());

		} catch (IOException e) {
			System.out.println("Error: " + e);
		}
	}
}
