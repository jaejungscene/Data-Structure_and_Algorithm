/**
 * 톱니바퀴
 * https://www.acmicpc.net/problem/14891
 */
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.StringTokenizer;

public class Main {
    public static void moveWheel(int num, StringBuilder[] wheel, int[] right, int[] left, int way){
        if(way == 1){
            right[0] = 3;
            left[0] = 7;
            wheel[num].insert(0, wheel[num].charAt(7));
            wheel[num].deleteCharAt(8);
        }
        else if(way == -1){
            right[0] = 1;
            left[0] = 5;
            wheel[num].append(wheel[num].charAt(0));
            wheel[num].deleteCharAt(0);
        }
    }

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st;

        StringBuilder[] wheel = new StringBuilder[5];
        for(int i=1; i<5; i++){
            wheel[i] = new StringBuilder(br.readLine());
        }

        int K = Integer.parseInt(br.readLine());
        int num, way;
        int[] right = new int[1];
        int[] left = new int[1];
        int tempR, tempL, tempWay;
        for(int i=0; i<K; i++){
            st = new StringTokenizer(br.readLine(), " ");
            num = Integer.parseInt(st.nextToken());
            way = Integer.parseInt(st.nextToken());

            moveWheel(num, wheel, right, left, way);
            tempR = right[0];
            tempL = left[0];
            tempWay = way;
            for(int k=num+1; k<=4 && wheel[k-1].charAt(right[0]) != wheel[k].charAt(6); k++){
                way = way==1 ? -1 : 1;
                moveWheel(k, wheel, right, left, way);
            }
            right[0] = tempR;
            left[0] = tempL;
            way = tempWay;
            for(int k=num-1; k>=1 && wheel[k+1].charAt(left[0]) != wheel[k].charAt(2); k--){
                way = way==1 ? -1 : 1;
                moveWheel(k, wheel, right, left, way);
            }
        }

        int answer = 0;
        for(int i=1; i<=4; i++){
            if(wheel[i].charAt(0) == '1')
                answer += (int)Math.pow(2, i-1);
        }

        System.out.println(answer);
    }
}
/*
11111111
11111111
11111111
11111111
3
1 1
2 1
3 1

10101111
01111101
11001110
00000010
2
3 -1
1 1

10101111
01111101
11001100
00000010
2
2 1
1 1

10001011
10000011
01011011
00111101
5
1 1
2 1
3 1
4 1
1 -1

10010011
01010011
11100011
01010101
8
1 1
2 1
3 1
4 1
1 -1
2 -1
3 -1
4 -1

*/