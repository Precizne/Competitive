public class Solution {
    public static String solution(long x, long y) {
        long n = x + y;
        return String.valueOf((n - 1) * n / 2  - y + 1);
    }

   public static void main(String[] args) {
      System.out.println(solution(3, 2));
   }
}
