
public class Solution {
	public static int lengthOfLongestSubstring(String s) {
		if (s == null || s.length() == 0)
			return 0;
		int maxLength = 0;
		int start = 0;
		int[] hash = new int[256];

		for (int i = 0; i < hash.length; i++) {
			hash[i] = -1;
		}

		for (int i = 0; i < s.length(); i++) {
			if (hash[s.charAt(i)] == -1) {
				hash[s.charAt(i)] = i;
				continue;
			}
			int length = i - start;
			if (length > maxLength)
				maxLength = length;
			for (int j = start; j < hash[s.charAt(i)]; j++)
				hash[s.charAt(j)] = -1;
			start = hash[s.charAt(i)] + 1;
			hash[s.charAt(i)] = i;
		}
		if (s.length() - start > maxLength) {
			maxLength = s.length() - start;
		}
		return maxLength;
	}
}
