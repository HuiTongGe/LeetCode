public class Solution {
    public String longestPalindrome(String s) {
		if (s == null || s.length() <= 1)
			return s;

		int length = s.length();
		boolean[][] dp = new boolean[length][length];
		int maxLength = 1, start = 0, end = 0;
		
		for (int l = 0; l < length; l++) {
			for(int i = 0; i < length - l; i++) {
				int j = i + l;
				if(s.charAt(i) == s.charAt(j) && (j - i <= 2 || dp[i + 1][j - 1])) {
					dp[i][j] = true;
					if (j - i + 1 > maxLength) {
						maxLength = j - i + 1;
						start = i;
						end = j;
					}
				}
			}
		}
		return s.substring(start, end + 1);
	}
}