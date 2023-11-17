/**
 * 로봇 청소기
 * https://www.acmicpc.net/problem/14503
 */
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.IOException;
import java.util.StringTokenizer;

class Main{
    public void changeCord(int[] robot, int flag){
        if(flag == 0){ //forward
            if(robot[2]==0)    robot[0] -= 1;
            else if(robot[2]==1)    robot[1] += 1;
            else if(robot[2]==2)    robot[0] += 1;
            else if(robot[2]==3)    robot[1] -= 1;
        }
        else if(flag == 1){ //backward
            if(robot[2]==0)    robot[0] += 1;
            else if(robot[2]==1)    robot[1] -= 1;
            else if(robot[2]==2)    robot[0] -= 1;
            else if(robot[2]==3)    robot[1] += 1;
        }
    }

    public boolean checkAround(int[] robot, int[][] room){
        for(int i=0; i<4; i++){
            robot[2] = robot[2]==0 ? 3 : robot[2]-1;
            changeCord(robot, 0);
            if(room[ robot[0] ][ robot[1] ] == 0)
                return true;
            changeCord(robot, 1);
        }
        return false;
    }

    public void solution(int N, int M, int[] robot, int[][] room){
        int cnt = 0;
        while(true){
            if(room[robot[0]][robot[1]] == 0){
                room[robot[0]][robot[1]] = -1;
                cnt++;
            }
            if(checkAround(robot, room))
                continue;
            changeCord(robot, 1);
            if(room[ robot[0] ][ robot[1] ] == 1)
                break;
        }
        System.out.println(cnt);
    }

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st;

        st = new StringTokenizer(br.readLine(), " ");
        int N = Integer.parseInt(st.nextToken());
        int M = Integer.parseInt(st.nextToken());

        st = new StringTokenizer(br.readLine(), " ");
        int[] robot = new int[3];
        robot[0] = Integer.parseInt(st.nextToken()); //n
        robot[1] = Integer.parseInt(st.nextToken()); //m
        robot[2] = Integer.parseInt(st.nextToken()); //d

        int[][] room = new int[N][M];
        for(int i=0; i<N; i++){
            st = new StringTokenizer(br.readLine(), " ");
            for(int j=0; j<M; j++){
                room[i][j] = Integer.parseInt(st.nextToken());
            }
        }

        new Main().solution(N, M, robot, room);
    }
}

/*
11 10
7 4 0
1 1 1 1 1 1 1 1 1 1
1 0 0 0 0 0 0 0 0 1
1 0 0 0 1 1 1 1 0 1
1 0 0 1 1 0 0 0 0 1
1 0 1 1 0 0 0 0 0 1
1 0 0 0 0 0 0 0 0 1
1 0 0 0 0 0 0 1 0 1
1 0 0 0 0 0 1 1 0 1
1 0 0 0 0 0 1 1 0 1
1 0 0 0 0 0 0 0 0 1
1 1 1 1 1 1 1 1 1 1

57
 */
