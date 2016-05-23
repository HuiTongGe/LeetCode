public class Solution {
    public String convert(String s, int numRows) {
		if (numRows == 1 || s.length() == 0) 
			return s;
		StringBuilder sb = new StringBuilder();
		for (int i = 0; i < s.length(); i += (2 * numRows - 2)) {
			sb.append(s.charAt(i));
		}
		for(int i = 1; i < numRows - 1; i++) {
			int step = 2 * i;
			for(int j = i; j < s.length(); j += step) {
				sb.append(s.charAt(j));
				step = 2 * numRows - 2 - step;
			}
		}
		for (int i = numRows - 1; i < s.length(); i += (2 * numRows - 2)) {
			sb.append(s.charAt(i));
		}
		return sb.toString();
	}
}