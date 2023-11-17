/**
 * 다리 놓기
 * https://www.acmicpc.net/problem/1010
 */
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.*;

public class Main {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st;

        int T = Integer.parseInt(br.readLine());
        int[] N = new int[T];
        int[] M = new int[T];
        for(int i=0; i<T; i++){
            st = new StringTokenizer(br.readLine(), " ");
            N[i] = Integer.parseInt(st.nextToken());
            M[i] = Integer.parseInt(st.nextToken());
        }

        int MAX_VALUE_OF_N_M = 29;
        int[][] opt = new int[MAX_VALUE_OF_N_M+1][MAX_VALUE_OF_N_M+1];
        for(int i=0; i<MAX_VALUE_OF_N_M+1; i++){
            for(int j=0; j<MAX_VALUE_OF_N_M+1; j++){
                if(i==0 || j==0)    opt[i][j] = 0;
                else if(i==1)       opt[i][j] = j;
                else if(j<i)        opt[i][j] = 0;
                else if(i==j)       opt[i][j] = 1;
                else                opt[i][j] = opt[i-1][j-1] + opt[i][j-1];
            }
        }

        for(int i=0; i<T; i++)
            System.out.println(opt[N[i]][M[i]]);
    }
}