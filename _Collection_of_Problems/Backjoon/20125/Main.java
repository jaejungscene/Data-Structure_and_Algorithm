import java.io.*;
import java.util.*;

public class Main {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = new StringTokenizer(br.readLine());
        int N = Integer.parseInt(st.nextToken());

        char[][] square = new char[N][N];
        for (int i = 0; i < N; i++) {
            square[i] = br.readLine().toCharArray();
        }

        int[] heartLoc = new int[2];
        boolean heartFound = false;
        for (int i = 1; i < N - 1; i++) {
            for (int j = 1; j < N - 1; j++) {
                if (
                    square[i][j] == '*'
                    && square[i][j-1] == '*' 
                    && square[i][j+1] == '*' 
                    && square[i-1][j] == '*' 
                    && square[i+1][j] == '*'
                ) {
                    heartLoc[0] = i;
                    heartLoc[1] = j;
                    heartFound = true;
                    break;
                }
            }
            if (heartFound) break;
        }

        int leftArmLength = 0;
        for (int j = heartLoc[1]-1; j > -1 && square[heartLoc[0]][j] == '*' ; j--) {
            leftArmLength++;
        }

        int rightArmLength = 0;
        for (int j = heartLoc[1]+1; j < N && square[heartLoc[0]][j] == '*' ; j++) {
            rightArmLength++;
        }

        int waistEndi = -1;
        int waistLength = 0;
        for (waistEndi = heartLoc[0]+1; waistEndi < N && square[waistEndi][heartLoc[1]] == '*'; waistEndi++) {
            waistLength++;
        }

        int leftLegLength = 0;
        for (int i = waistEndi; i < N && square[i][heartLoc[1]-1] == '*'; i++) {
            leftLegLength++;
        }

        int rightLegLength = 0;        
        for (int i = waistEndi; i < N && square[i][heartLoc[1]+1] == '*'; i++) {
            rightLegLength++;
        }

        System.out.println(
            String.format(
                "%d %d\n%d %d %d %d %d", 
                heartLoc[0] + 1, heartLoc[1] + 1,
                leftArmLength, rightArmLength, waistLength, leftLegLength, rightLegLength
            )
        );
    }
}