public class Solution {
    public List<List<Integer>> threeSum(int[] nums) {
        List<List<Integer>> result = new ArrayList<List<Integer>>();
		Arrays.sort(nums);

		for (int i = 0; i < nums.length; i++) {
			if (i > 0 && nums[i] == nums[i - 1])
				continue;
			int begin = i + 1;
			int end = nums.length - 1;
			int sum = 0 - nums[i];
			while (begin < end) {
				if (nums[begin] + nums[end] < sum) {
					begin++;
				} else if (nums[begin] + nums[end] > sum) {
					end--;
				} else {
					List<Integer> triple = new ArrayList<Integer>();
					triple.add(nums[i]);
					triple.add(nums[begin]);
					triple.add(nums[end]);
					result.add(triple);
					begin++;
					end--;
					int tmpBegin = nums[begin - 1];
					int tmpEnd = nums[end + 1];
					while (begin < end && tmpBegin == nums[begin]) {
						begin++;
					}
					while (begin < end && tmpEnd == nums[end]) {
						end--;
					}
				}
			}
		}

		return result;
    }
}