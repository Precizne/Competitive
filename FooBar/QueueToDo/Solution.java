public class Solution {
    public static int solution(int start, int length) {
        int res = 0;
        int idx = 0;
        int skip = 0;
        while(length > 0) {
            res ^= start;
            start++;
            idx++;
            if(idx == length) {
                start += skip;
                length--;
                idx = 0;
                skip++;
            }
        }
        return res;
    }
   public static void main(String[] args) {
      System.out.println(solution(17, 4));
   }
}
