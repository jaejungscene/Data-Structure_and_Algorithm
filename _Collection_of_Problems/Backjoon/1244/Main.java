import java.io.*;
import java.util.*;

public class Main {
    private static final int MALE = 1;
    private static final int FEMALE = 2;

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        int switchCount = Integer.parseInt(br.readLine());

        int[] switches = new int[switchCount + 1];
        StringTokenizer st = new StringTokenizer(br.readLine());
        for (int i=1; i<=switchCount; i++) {
            switches[i] = Integer.parseInt(st.nextToken());
        }

        int studentCount= Integer.parseInt(br.readLine());
        for (int i=0; i<studentCount; i++) {
            st = new StringTokenizer(br.readLine());
            int gender = Integer.parseInt(st.nextToken());
            int switchIdx = Integer.parseInt(st.nextToken());
            changeSwitcheStatus(switches, gender, switchIdx);
        }

        StringBuilder sb = new StringBuilder();
        for (int i=1; i<=switchCount; i++) {
            sb.append(switches[i]).append(" ");
            if (i % 20 == 0) {
                sb.append("\n");
            }
        }

        System.out.println(sb);
    }

    public static void changeSwitcheStatus(int[] switches, int gender, int switchIdx) {
        switch(gender) {
            case MALE:
                for (int i=switchIdx; i<switches.length; i+=switchIdx) {
                    switches[i] ^= 1;
                }
                break;
            case FEMALE:
                switches[switchIdx] ^= 1;
                int left = switchIdx - 1;
                int right = switchIdx + 1;
                while(
                    left > 0 &&
                    right < switches.length &&
                    switches[left] == switches[right]
                ) {
                    switches[left] ^= 1;
                    switches[right] ^= 1;
                    left--;
                    right++;
                }
                break;
            default:
                break;
        }
    }
}