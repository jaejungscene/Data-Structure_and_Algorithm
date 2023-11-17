/*
 * 연산자 끼워넣기
 * https://www.acmicpc.net/problem/14888
 */
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.*;

public class Main {

    int min = 1000000001;
    int max = -1000000001;
    public void search(int now, int[] A, int[] opsN, int result){
        if(now >= A.length){
            min = Math.min(min, result);
            max = Math.max(max, result);
        }
        for(int i=0; i<4; i++){
            if(opsN[i]>0){
                opsN[i]--;
                if(i == 0)
                    search(now+1, A, opsN, result+A[now]);
                else if(i == 1)
                    search(now+1, A, opsN, result-A[now]);
                else if(i == 2)
                    search(now+1, A, opsN, result*A[now]);
                else if(i == 3)
                    search(now+1, A, opsN, result/A[now]);
                opsN[i]++;
            }
        }
    }

    public void solution(int N, int[] A, int[] opsN){
        search(1, A, opsN, A[0]);
        System.out.println(max);
        System.out.println(min);
    }

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st;

        st = new StringTokenizer(br.readLine(), " ");
        int N = Integer.parseInt(st.nextToken());

        st = new StringTokenizer(br.readLine(), " ");
        int[] A = new int[N];
        for(int i=0; i<N; i++){
            A[i] = Integer.parseInt(st.nextToken());
        }

        // +, -, x, /
        st = new StringTokenizer(br.readLine(), " ");
        int[] opsN = new int[4];
        for(int i=0; i<4; i++){
            opsN[i] = Integer.parseInt(st.nextToken());
        }


        new Main().solution(N, A, opsN);
    }
}
/*
2
5 6
0 0 1 0

30
30
 */