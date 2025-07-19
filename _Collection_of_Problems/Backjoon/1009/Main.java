// import java.io.BufferedReader;
// import java.io.InputStreamReader;
// import java.math.BigInteger;
// import java.io.IOException;

// public class Main {
//     public static void main(String[] args) throws IOException {
//         BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
//         final int COMPUTER_NUM = 10;
//         int T = Integer.parseInt(br.readLine());
//         for(int i=0; i<T; i++){
//             String[] nowArgs = br.readLine().split(" ");
//             int a = Integer.parseInt(nowArgs[0]);
//             int b = Integer.parseInt(nowArgs[1]);
            
//             int result = 1;
//             for(int j=0; j<b; j++) {
//                 result = (result * a) % COMPUTER_NUM;
//             }

//             if(result == 0) result = COMPUTER_NUM;
//             System.out.println(result);
//         }
//     }
// }


import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.IOException;
import java.util.StringTokenizer;

public class Main {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        int T = Integer.parseInt(br.readLine());

        for (int t = 0; t < T; t++) {
            StringTokenizer st = new StringTokenizer(br.readLine());
            int a = Integer.parseInt(st.nextToken());
            int b = Integer.parseInt(st.nextToken());

            // 마지막 자릿수만 보면 되므로 0~9만 고려
            int[] pattern = new int[10];
            int idx = 0;
            int last = a % 10;
            pattern[idx++] = last;

            // 주기 찾기
            while (true) {
                int next = (pattern[idx - 1] * last) % 10;
                if (next == pattern[0]) break;
                pattern[idx++] = next;
            }

            // b번째 거듭제곱의 마지막 자릿수 인덱스 (1-based)
            int pos = (b - 1) % idx;
            int answer = pattern[pos];
            if (answer == 0) answer = 10; // 0번 컴퓨터는 10번 컴퓨터로 처리
            System.out.println(answer);
        }
    }
}
