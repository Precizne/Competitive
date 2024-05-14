import java.math.BigInteger;

public class Solution {
    public static int solution(String x) {
        BigInteger n = new BigInteger(x);
        int res = 0;
        while(!n.equals(BigInteger.ONE)) {
            res++;
            if(n.getLowestSetBit() != 0) {
                n = n.shiftRight(1);
            }
            else {
                BigInteger sum = n.add(BigInteger.valueOf(1));
                BigInteger dif = n.subtract(BigInteger.valueOf(1));
                if(dif.getLowestSetBit() > 1 || n.equals(BigInteger.valueOf(3))) {
                    n = dif;
                }
                else {
                    n = sum;
                }
            }
        }
        return res;
    }

   public static void main(String[] args) {
      System.out.println(solution("15"));
   }
}
