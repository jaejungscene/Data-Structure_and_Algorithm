import java.io.*;
import java.util.*;

public class Main {
    public static void main(String[] args) throws IOException{
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = new StringTokenizer(br.readLine());
        int N = Integer.parseInt(st.nextToken());
        int newScore = Integer.parseInt(st.nextToken());
        int P = Integer.parseInt(st.nextToken());

        if (N == 0) {
            System.out.println(1);
            return;
        }

        int[] scoreArr = new int[N];
        st = new StringTokenizer(br.readLine());
        for (int i = 0; i < N; i++) {
            scoreArr[i] = Integer.parseInt(st.nextToken());
        }

        if (N == P && scoreArr[N-1] >= newScore) {
            System.out.println(-1);
            return;
        }

        int rank = 1;
        for(int i=0; i<N; i++) {
            if(scoreArr[i] <= newScore) {
                rank = i + 1;
                break;
            } else {
                rank = i + 2;
            }
        }
        System.out.println(rank);
    }
}