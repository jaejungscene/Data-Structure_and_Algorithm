import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

public class Main {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        
        int N = Integer.parseInt(br.readLine());
        
        List<String> channelList = new ArrayList<>();
        for (int i = 0; i < N; i++) {
            channelList.add(br.readLine());
        }

        StringBuilder buttons = new StringBuilder();

        int kbs1Idx = channelList.indexOf("KBS1");

        for (int i = 0; i < kbs1Idx; i++) {
            buttons.append("1");
        }
        
        for (int i = 0; i < kbs1Idx; i++) {
            buttons.append("4");
        }

        String kbs1 = channelList.remove(kbs1Idx);
        channelList.add(0, kbs1);

        if (!channelList.get(1).equals("KBS2")) {
            int kbs2Idx = channelList.indexOf("KBS2");

            for (int i = 0; i < kbs2Idx; i++) {
                buttons.append("1");
            }
            
            for (int i = 0; i < kbs2Idx - 1; i++) {
                buttons.append("4");
            }

            String kbs2 = channelList.remove(kbs2Idx);
            channelList.add(1, kbs2);
        }

        System.out.print(buttons.toString());
    }
}


// import java.io.IOException;
// import java.io.InputStreamReader;
// import java.util.Scanner;

// public class Main {
//     public static void main(String[] args) throws IOException {
//         System.out.println("--- InputStreamReader 예제 ---");
//         System.out.print("입력하세요: "); // 여기에 "hello"를 입력하고 엔터

//         // 1. InputStreamReader로 한 글자만 읽기
//         InputStreamReader isr = new InputStreamReader(System.in);
//         char firstChar = (char) isr.read(); // 'h'를 읽음
//         System.out.println("InputStreamReader가 읽은 글자: " + firstChar);

//         // 2. Scanner로 나머지 입력 읽기
//         // isr.read()가 'h'만 가져갔으므로, System.in 스트림에는 "ello"가 남아있음
//         Scanner sc = new Scanner(System.in);
//         String remainingStr = sc.nextLine();
//         System.out.println("Scanner가 읽은 나머지: " + remainingStr);
//     }
// }

// import java.io.BufferedReader;
// import java.io.IOException;
// import java.io.InputStreamReader;
// import java.util.Scanner;

// public class BR_Example {
//     public static void main(String[] args) throws IOException {
//         System.out.println("--- BufferedReader 예제 ---");
//         System.out.print("입력하세요: "); // 여기에 "hello"를 입력하고 엔터

//         // 1. BufferedReader로 한 글자만 읽기
//         BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
//         char firstChar = (char) br.read(); // 'h'를 읽음
//         System.out.println("BufferedReader가 읽은 글자: " + firstChar);

//         // 2. Scanner로 나머지 입력 읽기
//         // br.read()가 호출될 때, 버퍼를 채우기 위해 "hello" 전체를 버퍼로 가져감
//         // 따라서 System.in 스트림은 이제 비어있음
//         Scanner sc = new Scanner(System.in);
//         System.out.print("Scanner 입력 대기 중... 다시 입력하세요: ");
//         String remainingStr = sc.nextLine();
//         System.out.println("Scanner가 읽은 내용: " + remainingStr);
//     }
// }

