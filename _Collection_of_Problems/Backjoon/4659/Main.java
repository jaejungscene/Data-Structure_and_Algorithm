import java.io.*;
import java.util.*;

public class Main {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringBuilder sb = new StringBuilder();

        String password;
        while (!(password = br.readLine()).equals("end")) {
            boolean result = checkPassword(password);
            if (result) {
                sb.append(String.format("<%s> is acceptable.%n", password));
            } else {
                sb.append(String.format("<%s> is not acceptable.%n", password));
            }
        }

        System.out.print(sb.toString());
    }

    public static boolean checkPassword(String password) {
        boolean hasVowel = false;
        int continueVowel = 0;
        int continueConsonant = 0;

        for (int i = 0; i < password.length(); i++) {
            char nowChar = password.charAt(i);
            if (isVowel(nowChar)) {
                hasVowel = true;
                continueConsonant = 0;
                continueVowel++;
            } else {
                continueVowel = 0;
                continueConsonant++;
            }


            if (continueVowel >= 3 || continueConsonant >= 3) {
                return false;
            }

            if (
                i != 0 &&
                password.charAt(i-1) == nowChar &&
                nowChar != 'e' && 
                nowChar != 'o'
            ) {
                return false;
            }
        }

        if (!hasVowel) {
            return false;
        }

        return true;
    }

    public static boolean isVowel(char c) {
        c = Character.toLowerCase(c);
        return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';
    }
}
