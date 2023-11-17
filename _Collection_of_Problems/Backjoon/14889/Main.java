/**
 * 스타트와 링크
 * https://www.acmicpc.net/problem/14889
 */
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.List;
import java.util.StringTokenizer;

public class Main {
    int diffMin = 100000000;

    public void calcuDiffMin(boolean[] visited, int[][] S, int n){
        List<Integer> trueTeam = new ArrayList<>();
        List<Integer> falseTeam = new ArrayList<>();
        int trueTeamScore = 0;
        int falseTeamScore = 0;

        for(int i=0; i<n; i++){
            if(visited[i] == true){
                trueTeam.add(i);
            } else {
                falseTeam.add(i);
            }
        }

        for(int i=0; i<(n/2)-1; i++){
            for(int j=i+1; j<n/2; j++){
                trueTeamScore +=
                        S[trueTeam.get(i)][trueTeam.get(j)]
                                + S[trueTeam.get(j)][trueTeam.get(i)];
                falseTeamScore +=
                        S[falseTeam.get(i)][falseTeam.get(j)]
                                + S[falseTeam.get(j)][falseTeam.get(i)];
            }
        }

        diffMin = Math.min(
                diffMin,
                Math.abs(trueTeamScore-falseTeamScore)
        );
    }


    public void backtrackComb(boolean[] visited, int[][] S, int start, int n, int r) {
        if(r == 0) {
            calcuDiffMin(visited, S, n);
            return;
        }

        for(int i=start; i<n; i++) {
            visited[i] = true;
            backtrackComb(visited, S, i + 1, n, r - 1);
            visited[i] = false;
        }
    }

    public int solution(int N, int[][] S){
        boolean visited[] = new boolean[N];
        backtrackComb(visited, S, 0, N, N/2);
        return diffMin;
    }

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        int N = Integer.parseInt(br.readLine());

        StringTokenizer st;
        int[][] S = new int[N][N];
        for(int i=0; i<N; i++){
            st = new StringTokenizer(br.readLine(), " ");
            for(int j=0; j<N; j++){
                S[i][j] = Integer.parseInt(st.nextToken());
            }
        }

        System.out.println(new Main().solution(N, S));
    }
}
/*
8
0 5 4 5 4 5 4 5
4 0 5 1 2 3 4 5
9 8 0 1 2 3 1 2
9 9 9 0 9 9 9 9
1 1 1 1 0 1 1 1
8 7 6 5 4 0 3 2
9 1 9 1 9 1 0 9
6 5 4 3 2 1 9 0

1
 */