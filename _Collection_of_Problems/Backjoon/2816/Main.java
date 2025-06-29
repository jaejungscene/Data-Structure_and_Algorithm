import java.io.*;
import java.util.ArrayList;
import java.util.List;

public class Main {
    public static void main(String[] args) throws IOException {
        try (BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
             BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out))) {

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
            bw.write(buttons.toString());
        }
    }
}
