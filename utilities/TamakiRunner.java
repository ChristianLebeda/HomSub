import tw.exact.*;

import java.io.*;

public class TamakiRunner {
    public static void main(String[] args) {
        try {
            BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

            while(br.ready()) {
                String line = br.readLine();
                String s[] = line.split(" ");
                int n = Integer.parseInt(s[2]);
                int m = Integer.parseInt(s[3]);
                Graph g = new Graph(n);
        
                for (int i = 0; i < m; i++) {
                    line = br.readLine();
                    s = line.split(" ");
                    int u = Integer.parseInt(s[0]);
                    int v = Integer.parseInt(s[1]);
                    g.addEdge(u - 1, v - 1);
                }
                
                TreeDecomposition td = MainDecomposer.decompose(g);
                td.writeTo(System.out);
            }

            br.close();
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
