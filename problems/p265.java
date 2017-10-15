import java.util.Arrays;
import java.util.Collections;

public class p265 {

    static int count = 0;
    static int n = 5;
    static int stringSize = (int) Math.pow(2, n);

    static long S(int n, int r, String str) {
        String head = str.substring(0, str.length() - 1);
        String tail = str.substring(str.length() - n);
        if (head.contains(tail)) {
            return 0;
        } else if (r <= 0 ) {
            String t = str + str.substring(0, n);
            for (int i = 0; i < stringSize; i++) {
                head = t.substring(0, i + n - 1);
                tail = t.substring(i, i + n);
                if (head.contains(tail)) {
                    return 0;
                }
            }
            count += 1;
            return Integer.parseInt(str, 2);
        }
        return S(n, r - 1, str + "0") + S(n, r - 1, str + "1");
    }

    public static void main(String[] args) {
        long start = System.nanoTime();

        String baseString = String.join("", Collections.nCopies(n, "0"));
        long sol = S(n, stringSize - n, baseString);

        System.out.println("Solution: " + sol);
        System.out.println("Count: " + count);

        long end = System.nanoTime();
        System.out.println((end - start)/1000000000.0 + " seconds to run");
    }
}
